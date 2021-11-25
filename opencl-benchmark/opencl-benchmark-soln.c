#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

#define N (1024*1024*32)

#define CL_PROGRAM_FILE "benchmark-soln.cl"

#define MAX_PLATFORMS 10
#define MAX_DEVICES 10
#define MAX_NAME_LENGTH 128


struct benchmark_result {
    double host_to_device;
    double global_mem_access;
    double only_flops;
};

int benchmark(cl_device_id device, char *program_text, struct benchmark_result *result) 
{
    // Create a compute context 
    cl_context context;
    context = clCreateContext(0, 1, &device, NULL, NULL, NULL);
    if (!context)
    {
        fprintf(stderr, "Failed to create a compute context.\n");
        return -1;
    }

    // Create a command queue
    cl_command_queue commands = clCreateCommandQueue(context, device, 0, NULL);
    if (!commands)
    {
        fprintf(stderr, "Failed to create a command queue.\n");
        return -1;
    }

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
    

    // Create Kernels
    cl_kernel global_mem_access = clCreateKernel(program, "global_mem_access", &err);
    if (!global_mem_access || err != CL_SUCCESS)
    {
        fprintf(stderr, "Failed to create compute kernel!\n");
        return -1;
    }

    cl_kernel only_flops = clCreateKernel(program, "only_flops", &err);
    if (!only_flops || err != CL_SUCCESS)
    {
        fprintf(stderr, "Failed to create compute kernel!\n");
        return -1;
    }

    // Daten auf dem Host vorbereiten
    float *h_data = malloc(N * sizeof(float));
    for(size_t i=0; i<N;i++) 
    {
        h_data[i] = 0.0;
    }

    // Create array in device memory
    cl_mem d_data = clCreateBuffer(context, CL_MEM_READ_WRITE, N * sizeof(float), NULL, NULL);
    
    if(!d_data)
    {
        fprintf(stderr, "Failed to allocate memory on device\n");
        return -1;
    }

    // Copy data to device
    struct timeval start;
    gettimeofday(&start, 0);

    err = clEnqueueWriteBuffer(commands, d_data, CL_TRUE, 0, N * sizeof(float), h_data, 0, NULL, NULL);
    if (err != CL_SUCCESS)
    {
        fprintf(stderr, "Failed to write to device array\n");
        return -1;
    }
    // Wait for transfer to finish
    clFinish(commands);
    struct timeval end;
    gettimeofday(&end, 0);
    long lsec = end.tv_sec - start.tv_sec;
    long lusec = end.tv_usec - start.tv_usec;
    double sec = (lsec + lusec / 1000000.0);
    result->host_to_device = sec;
    
    // Set the arguments to our compute kernel
    err = 0;
    err  = clSetKernelArg(global_mem_access, 0, sizeof(cl_mem), &d_data);
    if (err != CL_SUCCESS)
    {
        fprintf(stderr, "Failed to set kernel arguments!\n");
        return -1;
    }

    size_t local_size = 32;
    // Get the maximum work group size for executing the kernel on the device
    err = clGetKernelWorkGroupInfo(global_mem_access, device, CL_KERNEL_WORK_GROUP_SIZE, sizeof(local_size), &local_size, NULL);
    if (err != CL_SUCCESS)
    {
        fprintf(stderr, "Error: Failed to retrieve kernel work group info\n");
        return -1;
    }


    // Execute the kernel
    size_t global_size = N;
    gettimeofday(&start, 0);
    err = clEnqueueNDRangeKernel(commands, global_mem_access, 1, NULL, &global_size, &local_size, 0, NULL, NULL);
    if (err)
    {
        fprintf(stderr, "Failed to execute kernel!\n");
        return -1;
    }

    // Wait for the commands to get serviced before reading back results
    clFinish(commands);
    gettimeofday(&end, 0);
    lsec = end.tv_sec - start.tv_sec;
    lusec = end.tv_usec - start.tv_usec;
    sec = (lsec + lusec / 1000000.0);
    result->global_mem_access = sec;


    // Set the arguments to our compute kernel
    err = 0;
    err  = clSetKernelArg(only_flops, 0, sizeof(cl_mem), &d_data);
    if (err != CL_SUCCESS)
    {
        fprintf(stderr, "Failed to set kernel arguments!\n");
        return -1;
    }

    // Get the maximum work group size for executing the kernel on the device
    err = clGetKernelWorkGroupInfo(only_flops, device, CL_KERNEL_WORK_GROUP_SIZE, sizeof(local_size), &local_size, NULL);
    if (err != CL_SUCCESS)
    {
        fprintf(stderr, "Error: Failed to retrieve kernel work group info\n");
        return -1;
    }

    
    // Execute the kernel
    global_size = N;
    gettimeofday(&start, 0);
    err = clEnqueueNDRangeKernel(commands, only_flops, 1, NULL, &global_size, &local_size, 0, NULL, NULL);
    if (err)
    {
        fprintf(stderr, "Failed to execute kernel!\n");
        return -1;
    }

    // Wait for the commands to get serviced before reading back results
    clFinish(commands);
    gettimeofday(&end, 0);
    lsec = end.tv_sec - start.tv_sec;
    lusec = end.tv_usec - start.tv_usec;
    sec = (lsec + lusec / 1000000.0);
    result->only_flops = sec;

    
    clReleaseMemObject(d_data);
    clReleaseProgram(program);
    clReleaseKernel(global_mem_access);
    clReleaseKernel(only_flops);
    clReleaseCommandQueue(commands);
    clReleaseContext(context);
    return 0;
}


int main(int argc, char** argv)
{
    // Get all devices
    cl_device_id *devices;
    cl_uint n_devices;
    clGetDeviceIDs(NULL, CL_DEVICE_TYPE_ALL, MAX_DEVICES, NULL, &n_devices);
    devices = (cl_device_id *) malloc(n_devices * sizeof(cl_device_id));
    clGetDeviceIDs(NULL, CL_DEVICE_TYPE_ALL, n_devices, devices, NULL);
    if(n_devices == 0) {
        fprintf(stderr, "No devices found. Exiting.\n");
        return -1;
    }

    char name[MAX_NAME_LENGTH];
    printf("Devices:\n");
    for(int i=0;i<n_devices;i++) {
        clGetDeviceInfo(devices[i], CL_DEVICE_NAME, sizeof(name), name, NULL);
        printf("[%d]: %s\n", i, name);
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
    

    printf("Device                                        | Host to Device GB/s | Global Mem GB/s |       GFLOPS\n");
    printf("----------------------------------------------------------------------------------------------------\n");
    for(int i=0; i<n_devices;i++) {
        clGetDeviceInfo(devices[i], CL_DEVICE_NAME, sizeof(name), name, NULL);
        printf("[%d]: %40s | ", i, name);

        struct benchmark_result result;

        benchmark(devices[i], program_text, &result);

        double hostodev = N * sizeof(float) / 1e9 / result.host_to_device;
        double globalmem = 2.0 * N * sizeof(float) / 1e9 / result.global_mem_access;
        double onlyflops = 64.0 * 4 * N / 1e9 / result.only_flops;

        printf("         %10.2f |      %10.2f |   %10.2f\n", hostodev, globalmem, onlyflops);
    }
      
    
    free(program_text);
    free(devices);
    return 0;
}

