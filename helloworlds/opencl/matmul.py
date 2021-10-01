import pyopencl as cl
import numpy as np
from time import time


repetitions = 4
n = np.int32(1024)
size = n * n

a = np.ones(size).astype(np.float32)
b = np.ones(size).astype(np.float32)
c = np.ones(size).astype(np.float32)

results = {}

# Sequential multiply

def seq_mult(n, a, b, c):
    for i in range(n):
        for j in range(n):
            c[i*n+j] = 0.0
            for k in range(n):
                c[i*n+j] += a[i*n+k] * b[k*n+j]

results['seq'] = []
for i in range(repetitions):
    start = time()
    # seq_mult(n, a, b, c)
    duration = time() - start
    results['seq'].append(duration)

# NumPy
results['numpy'] = []
for i in range(repetitions):
    start = time()
    c = np.matmul(a, b)
    duration = time() - start 
    results['numpy'].append(duration)





# OpenCL

context = cl.create_some_context()
queue = cl.CommandQueue(context)

buf_a = cl.Buffer(context, cl.mem_flags.READ_ONLY | cl.mem_flags.COPY_HOST_PTR, hostbuf=a)
buf_b = cl.Buffer(context, cl.mem_flags.READ_ONLY | cl.mem_flags.COPY_HOST_PTR, hostbuf=b)
buf_c = cl.Buffer(context, cl.mem_flags.WRITE_ONLY, c.nbytes)

matmul = """
__kernel void matmul(
    const int N,
    __global float* A,
    __global float* B,
    __global float* C)
{
    int k;
    int i = get_global_id(0);
    int j = get_global_id(1);
    float tmp;
    if ((i < N) && (j < N))
    {
        tmp = 0.0f;
        for (k = 0; k < N; k++)
            tmp += A[i*N+k] * B[k*N+j];
        C[i*N+j] = tmp;
    }
}
"""

program = cl.Program(context, matmul).build()
program.matmul.set_scalar_arg_dtypes([np.int32, None, None, None])

results['opencl'] = []
for i in range(repetitions):
    start = time()
    program.matmul(queue, (n, n), None, n, buf_a, buf_b, buf_c)
    queue.finish()
    duration = time() - start 
    results['opencl'].append(duration)
   
    # cl.enqueue_copy(queue, c, buf_c)


## Print results

for algo, durations in results.items():
    total = 0.0
    for duration in durations:
        total += duration
    total /= len(durations)
    print(f'Duration: {total:.2f} for {algo}')


# OpenCL Image Load/Save: https://gist.github.com/pointhi/801a3c19498728801e909b623c1e15a1