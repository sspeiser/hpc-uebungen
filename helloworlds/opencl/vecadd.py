import pyopencl as cl
import numpy as np
from time import time


repetitions = 4
n = 1024*1024*32


a = np.ones(n).astype(np.float32)
b = np.ones(n).astype(np.float32)
c = np.ones(n).astype(np.float32)

results = {}

# Sequential multiply

def seq_add(n, a, b, c):
    for i in range(n):
        c[i] = a[i] + b[i]
            
results['seq'] = []
for i in range(repetitions):
    start = time()
    # seq_add(n, a, b, c)
    duration = time() - start
    results['seq'].append(duration)

# NumPy
results['numpy'] = []
for i in range(repetitions):
    start = time()
    c = a + b
    duration = time() - start 
    results['numpy'].append(duration)





# OpenCL

context = cl.create_some_context()
queue = cl.CommandQueue(context)

buf_a = cl.Buffer(context, cl.mem_flags.READ_ONLY | cl.mem_flags.COPY_HOST_PTR, hostbuf=a)
buf_b = cl.Buffer(context, cl.mem_flags.READ_ONLY | cl.mem_flags.COPY_HOST_PTR, hostbuf=b)
buf_c = cl.Buffer(context, cl.mem_flags.READ_WRITE, c.nbytes)

vecadd = """
__kernel void vecadd(
    __global const float *A,
    __global const float *B,
    __global float *C)
{
    int i = get_global_id(0);
    C[i] = A[i] + B[i];
}
"""

program = cl.Program(context, vecadd).build()
program.vecadd.set_scalar_arg_dtypes([None, None, None])

results['opencl'] = []
for i in range(repetitions):
    start = time()
    program.vecadd(queue, (n,), None, buf_a, buf_b, buf_c)
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

for algo, durations in results.items():
    arr = np.array(durations)
    print(f'{algo}:\t{arr.mean()}, {arr.min()}, {arr.max()}, {np.median(arr)} {arr}')


# OpenCL Image Load/Save: https://gist.github.com/pointhi/801a3c19498728801e909b623c1e15a1