#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

#define N (1024*1024*64)

#define CL_PROGRAM_FILE "opencl-program.cl"

#define MAX_PLATFORMS 10
#define MAX_DEVICES 10
#define MAX_NAME_LENGTH 128


int main(int argc, char** argv)
{
    // First get available platforms
    cl_platform_id *platforms;
    cl_uint n_platforms;
    clGetPlatformIDs(MAX_PLATFORMS, NULL, &n_platforms);
    platforms = (cl_platform_id *) malloc(n_platforms * sizeof(cl_platform_id));
    clGetPlatformIDs(n_platforms, platforms, NULL);

    if(n_platforms == 0) {
        fprintf(stderr, "No platforms found. Exiting.");
        return -1;
    }

    char name[MAX_NAME_LENGTH];
    printf("Platforms:\n");
    for(int i=0;i<n_platforms;i++) 
    {
        clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, sizeof(name), name, NULL);
        printf("[%d]: %s\n", i, name);
    }
    printf("Choose platform (Default 0): ");
    int choice = 0;
    scanf("%d", &choice);
    if(choice < 0 || choice >= n_platforms) {
        printf("Invalid choice, using platform 0");
        choice = 0;
    }
    cl_platform_id platform;
    memcpy(&platform, &platforms[choice], sizeof(cl_platform_id));
    free(platforms);

    // Get Devices for chosen platform
    cl_device_id *devices;
    cl_uint n_devices;
    clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, MAX_DEVICES, NULL, &n_devices);
    devices = (cl_device_id *) malloc(n_devices * sizeof(cl_device_id));
    clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, n_devices, devices, NULL);
    if(n_devices == 0) {
        fprintf(stderr, "No devices found for platform. Exiting.\n");
        return -1;
    }

    printf("Devices:\n");
    for(int i=0;i<n_devices;i++) {
        clGetDeviceInfo(devices[i], CL_DEVICE_NAME, sizeof(name), name, NULL);
        printf("[%d]: %s\n", i, name);
    }
    printf("Choose device (Default 0): ");
    choice = 0;
    scanf("%d", &choice);
    if(choice < 0 || choice >= n_devices) {
        printf("Invalid choice, using device 0");
        choice = 0;
    }
    cl_device_id device;
    memcpy(&device, &devices[choice], sizeof(cl_device_id));
    free(devices);
      
    // Create a compute context 
    cl_context context;
    context = clCreateContext(0, 1, &device, NULL, NULL, NULL);
    if (!context)
    {
        fprintf(stderr, "Failed to create a compute context.\n");
        return -1;
    }

    // Create a command queue
    cl_command_queue commands = clCreateCommandQueue(context, device, CL_QUEUE_PROFILING_ENABLE, NULL);
    if (!commands)
    {
        fprintf(stderr, "Failed to create a command queue.\n");
        return -1;
    }


    // Load program from file
    FILE *program_file = fopen(CL_PROGRAM_FILE, "r");
    if(program_file == NULL) {
        fprintf(stderr, "Failed to open OpenCL program file\n");
        return -1;
    }
    fseek(program_file, 0, SEEK_END);
    size_t program_size = ftell(program_file);
    rewind(program_file);
    char *program_text = (char *) malloc((program_size + 1) * sizeof(char));
    program_text[program_size] = '\0';
    fread(program_text, sizeof(char), program_size, program_file);
    fclose(program_file);

    int err;                
    cl_program program = clCreateProgramWithSource(context, 1, (const char **) &program_text, NULL, &err);
    if(err < 0)
    {
        fprintf(stderr, "Failed to create program.\n");
        return -1;
    }

    err = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
    if (err != CL_SUCCESS)
    {
        size_t len;
        char buffer[2048];

        fprintf(stderr, "Failed to build program executable!\n");
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &len);
        fprintf(stderr, "%s\n", buffer);
        return -1;
    }
    free(program_text);

    // Create Kernel ... has to be adapted to program
    cl_kernel vector_add = clCreateKernel(program, "vector_add", &err);
    if (!vector_add || err != CL_SUCCESS)
    {
        fprintf(stderr, "Failed to create compute kernel!\n");
        return -1;
    }

    // Daten auf dem Host vorbereiten
    float *a = malloc(N * sizeof(float));
    float *b = malloc(N * sizeof(float));
    float *c = malloc(N * sizeof(float));

    for(size_t i=0; i<N;i++) 
    {
        a[i] = 1.0;
        b[i] = 2.0;
    }

    // Create arrays in device memory
    cl_mem d_a = clCreateBuffer(context, CL_MEM_READ_ONLY, N * sizeof(float), NULL, NULL);
    cl_mem d_b = clCreateBuffer(context, CL_MEM_READ_ONLY, N * sizeof(float), NULL, NULL);
    cl_mem d_c = clCreateBuffer(context, CL_MEM_WRITE_ONLY, N * sizeof(float), NULL, NULL);
    
    if(!d_a || !d_b || !d_c)
    {
        fprintf(stderr, "Failed to allocate memory on device\n");
        return -1;
    }

    // Copy data of a and b to device
    err = clEnqueueWriteBuffer(commands, d_a, CL_TRUE, 0, N * sizeof(float), a, 0, NULL, NULL);
    if (err != CL_SUCCESS)
    {
        fprintf(stderr, "Failed to write to device array\n");
        return -1;
    }

    err = clEnqueueWriteBuffer(commands, d_b, CL_TRUE, 0, N * sizeof(float), b, 0, NULL, NULL);
    if (err != CL_SUCCESS)
    {
        fprintf(stderr, "Failed to write to device array\n");
        return -1;
    }

    // Set the arguments to our compute kernel
    err = 0;
    err  = clSetKernelArg(vector_add, 0, sizeof(cl_mem), &d_a);
    err |= clSetKernelArg(vector_add, 1, sizeof(cl_mem), &d_b);
    err |= clSetKernelArg(vector_add, 2, sizeof(cl_mem), &d_c);
    if (err != CL_SUCCESS)
    {
        fprintf(stderr, "Failed to set kernel arguments!\n");
        return -1;
    }

    // Time measurements
    cl_event prof_event;
    cl_ulong start_time, end_time;
    size_t return_bytes;

    // Execute the kernel
    size_t global_size = N;
    size_t local_size = 128;
    err = clEnqueueNDRangeKernel(commands, vector_add, 1, NULL, &global_size, &local_size, 0, NULL, &prof_event);
    if (err)
    {
        fprintf(stderr, "Failed to execute kernel!\n");
        return -1;
    }

    // Wait for the commands to get serviced before reading back results
    clFinish(commands);

    clGetEventProfilingInfo(prof_event, CL_PROFILING_COMMAND_START, sizeof(cl_ulong), &start_time, &return_bytes);
    clGetEventProfilingInfo(prof_event, CL_PROFILING_COMMAND_END, sizeof(cl_ulong), &end_time, &return_bytes);
    double time = (double) (end_time - start_time) / 1.0e9;
    printf("Zeit: %.4f sec (nur Berechnung ohne Memory-Transfer)\nLeistung %.2f GFLOP/s\n", time, N / time / 1e9);

    // Read back the results from the device to verify the output
    err = clEnqueueReadBuffer( commands, d_c, CL_TRUE, 0, N * sizeof(float), c, 0, NULL, NULL );  
    if (err != CL_SUCCESS)
    {
        fprintf(stderr, "Failed to read output array\n");
        return -1;
    }
    
    // Validate results
    int correct = 0;
    int incorrect = 0;
    for(int i = 0; i < N; i++)
    {
        if(fabs(c[i] - a[i] - b[i]) > 0.00001)
        {
            fprintf(stderr, "Error at position %d: c[%d] = %f, a[%d] = %f, b[%d] = %f\n", i, i, c[i], i, a[i], i, b[i]);
            incorrect++;
        }
        else
        {
            correct++;
        }
    }
    
    printf("Correct: %d\nIncorrect: %d\n", correct, incorrect);
    
    // Shutdown and cleanup
    clReleaseMemObject(d_a);
    clReleaseMemObject(d_b);
    clReleaseMemObject(d_c);
    clReleaseProgram(program);
    clReleaseKernel(vector_add);
    clReleaseCommandQueue(commands);
    clReleaseContext(context);

    free(a);
    free(b);
    free(c);

    return 0;
}

