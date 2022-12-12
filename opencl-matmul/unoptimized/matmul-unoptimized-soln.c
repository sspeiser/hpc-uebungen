#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

#define N 1024
#define MATRIX_SIZE (N * N)
#define MATRIX_MEM (N * N * sizeof(float))

#define CL_PROGRAM_FILE "matmul-unoptimized-soln.cl"
#define KERNEL_NAME "matmul_unoptimized"
//#define KERNEL_NAME "matmul_localvar"


#define MAX_PLATFORMS 10
#define MAX_DEVICES 10
#define MAX_NAME_LENGTH 128

struct benchmark_result
{
    double transfer_time;
    double calc_time;
    int errors;
};

int benchmark(cl_device_id device, char *program_text, char *kernel_name, struct benchmark_result *result)
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
    cl_command_queue commands = clCreateCommandQueue(context, device, CL_QUEUE_PROFILING_ENABLE, NULL);
    if (!commands)
    {
        fprintf(stderr, "Failed to create a command queue.\n");
        return -1;
    }

    int err;
    cl_program program = clCreateProgramWithSource(context, 1, (const char **)&program_text, NULL, &err);
    if (err < 0)
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
    cl_kernel kernel = clCreateKernel(program, kernel_name, &err);
    if (!kernel || err != CL_SUCCESS)
    {
        fprintf(stderr, "Failed to create compute kernel!\n");
        return -1;
    }

    // Daten auf dem Host vorbereiten
    float *h_a = malloc(MATRIX_MEM);
    float *h_b = malloc(MATRIX_MEM);
    float *h_c = malloc(MATRIX_MEM);
    for (size_t i = 0; i < MATRIX_SIZE; i++)
    {
        h_a[i] = 2.0;
        h_b[i] = 4.0;
    }

    // Create array in device memory
    cl_mem d_a = clCreateBuffer(context, CL_MEM_READ_ONLY, MATRIX_MEM, NULL, NULL);
    cl_mem d_b = clCreateBuffer(context, CL_MEM_READ_ONLY, MATRIX_MEM, NULL, NULL);
    cl_mem d_c = clCreateBuffer(context, CL_MEM_READ_WRITE, MATRIX_MEM, NULL, NULL);

    if (!d_a | !d_b | !d_c)
    {
        fprintf(stderr, "Failed to allocate memory on device\n");
        return -1;
    }

    // Copy data to device
    double transfer_sec = 0.0;
    cl_event prof_event;
    cl_ulong start_time, end_time;
    size_t return_bytes;

    err = clEnqueueWriteBuffer(commands, d_a, CL_TRUE, 0, MATRIX_MEM, h_a, 0, NULL, &prof_event);
    if (err != CL_SUCCESS)
    {
        fprintf(stderr, "Failed to write to device array\n");
        return -1;
    }
    // Wait for transfer to finish
    clFinish(commands);

    clGetEventProfilingInfo(prof_event, CL_PROFILING_COMMAND_START, sizeof(cl_ulong), &start_time, &return_bytes);
    clGetEventProfilingInfo(prof_event, CL_PROFILING_COMMAND_END, sizeof(cl_ulong), &end_time, &return_bytes);
    transfer_sec += (double)(end_time - start_time) / 1.0e9;

    err = clEnqueueWriteBuffer(commands, d_b, CL_TRUE, 0, MATRIX_MEM, h_b, 0, NULL, &prof_event);
    if (err != CL_SUCCESS)
    {
        fprintf(stderr, "Failed to write to device array\n");
        return -1;
    }
    // Wait for transfer to finish
    clFinish(commands);

    clGetEventProfilingInfo(prof_event, CL_PROFILING_COMMAND_START, sizeof(cl_ulong), &start_time, &return_bytes);
    clGetEventProfilingInfo(prof_event, CL_PROFILING_COMMAND_END, sizeof(cl_ulong), &end_time, &return_bytes);
    transfer_sec += (double)(end_time - start_time) / 1.0e9;

    // Set the arguments to our compute kernel
    int n = N;
    err = clSetKernelArg(kernel, 0, sizeof(int), &n);
    err |= clSetKernelArg(kernel, 1, sizeof(cl_mem), &d_a);
    err |= clSetKernelArg(kernel, 2, sizeof(cl_mem), &d_b);
    err |= clSetKernelArg(kernel, 3, sizeof(cl_mem), &d_c);
    if (err != CL_SUCCESS)
    {
        fprintf(stderr, "Failed to set kernel arguments!\n");
        return -1;
    }

    // Execute the kernel
    size_t global_size[] = {N, N};
    err = clEnqueueNDRangeKernel(commands, kernel, 2, NULL, global_size, NULL, 0, NULL, &prof_event);
    if (err)
    {
        fprintf(stderr, "Failed to execute kernel!\n");
        return -1;
    }

    // Wait for the commands to get serviced before reading back results
    clFinish(commands);

    clGetEventProfilingInfo(prof_event, CL_PROFILING_COMMAND_START, sizeof(cl_ulong), &start_time, &return_bytes);
    clGetEventProfilingInfo(prof_event, CL_PROFILING_COMMAND_END, sizeof(cl_ulong), &end_time, &return_bytes);
    double calc_time = (double)(end_time - start_time) / 1.0e9;

    // Copy Result Data Back
    err = clEnqueueReadBuffer(commands, d_c, CL_TRUE, 0, MATRIX_MEM, h_c, 0, NULL, &prof_event);
    if (err != CL_SUCCESS)
    {
        fprintf(stderr, "Failed to read from device array\n");
        return -1;
    }
    // Wait for transfer to finish
    clFinish(commands);

    clGetEventProfilingInfo(prof_event, CL_PROFILING_COMMAND_START, sizeof(cl_ulong), &start_time, &return_bytes);
    clGetEventProfilingInfo(prof_event, CL_PROFILING_COMMAND_END, sizeof(cl_ulong), &end_time, &return_bytes);
    transfer_sec += (double)(end_time - start_time) / 1.0e9;

    // Check Results
    int errors = 0;
    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        if (fabs(h_c[i] - N * 2.0 * 4.0) > 0.0001)
        {
            errors += 1;
        }
    }

    result->transfer_time = transfer_sec;
    result->calc_time = calc_time;
    result->errors = errors;

    clReleaseMemObject(d_a);
    clReleaseMemObject(d_b);
    clReleaseMemObject(d_c);
    clReleaseProgram(program);
    clReleaseKernel(kernel);
    clReleaseCommandQueue(commands);
    clReleaseContext(context);
    free(h_a);
    free(h_b);
    free(h_c);
    return 0;
}

int main(int argc, char **argv)
{
    int err;
    // Get all platforms
    cl_platform_id *platforms;
    cl_uint n_platforms;

    err = clGetPlatformIDs(16, NULL, &n_platforms);
    if (err != CL_SUCCESS)
    {
        fprintf(stderr, "Error getting number of platforms\n");
        return -1;
    }
    if (n_platforms == 0)
    {
        fprintf(stderr, "No platforms found\n");
        return -1;
    }
    platforms = (cl_platform_id *)malloc(n_platforms * sizeof(cl_platform_id));
    err = clGetPlatformIDs(n_platforms, platforms, NULL);
    if (err != CL_SUCCESS)
    {
        fprintf(stderr, "Error getting platforms\n");
        return -1;
    }
    char platform_name[MAX_NAME_LENGTH];
    printf("Platforms:\n");
    for (int i = 0; i < n_platforms; i++)
    {
        clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, sizeof(platform_name), platform_name, NULL);
        printf("[%d]: %s\n", i, platform_name);
    }

    for (int j = 0; j < n_platforms; j++)
    {

        // Get all devices
        cl_device_id *devices;
        cl_uint n_devices;
        clGetDeviceIDs(platforms[j], CL_DEVICE_TYPE_ALL, MAX_DEVICES, NULL, &n_devices);
        devices = (cl_device_id *)malloc(n_devices * sizeof(cl_device_id));
        clGetDeviceIDs(platforms[j], CL_DEVICE_TYPE_ALL, n_devices, devices, NULL);
        if (n_devices == 0)
        {
            fprintf(stderr, "No devices found. Exiting.\n");
            return -1;
        }

        char name[MAX_NAME_LENGTH];
        printf("Devices:\n");
        for (int i = 0; i < n_devices; i++)
        {
            clGetDeviceInfo(devices[i], CL_DEVICE_NAME, sizeof(name), name, NULL);
            printf("[%d]: %s\n", i, name);
        }

        // Load program from file
        FILE *program_file = fopen(CL_PROGRAM_FILE, "rb");
        if (program_file == NULL)
        {
            fprintf(stderr, "Failed to open OpenCL program file\n");
            return -1;
        }
        fseek(program_file, 0, SEEK_END);
        size_t program_size = ftell(program_file);
        rewind(program_file);
        char *program_text = (char *)malloc((program_size + 1) * sizeof(char));
        program_text[program_size] = '\0';
        fread(program_text, sizeof(char), program_size, program_file);
        fclose(program_file);

        printf("Device                                        | GFLOP/s w/o transfer | GFLOP/s w/ transfer |      Errors\n");
        printf("--------------------------------------------------------------------------------------------------------\n");
        for (int i = 0; i < n_devices; i++)
        {
            clGetDeviceInfo(devices[i], CL_DEVICE_NAME, sizeof(name), name, NULL);
            printf("[%d]: %40s | ", i, name);

            struct benchmark_result result;

            benchmark(devices[i], program_text, KERNEL_NAME, &result);

            double gflops_calc = 2.0 * N * N * N / 1e9 / result.calc_time;
            double gflops_transfer = 2.0 * N * N * N / 1e9 / (result.transfer_time + result.calc_time);

            printf("          %10.2f |          %10.2f |   %9d\n", gflops_calc, gflops_transfer, result.errors);
        }

        free(program_text);
        free(devices);
    }
    return 0;
}
