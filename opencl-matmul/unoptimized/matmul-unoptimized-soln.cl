__kernel void matmul_unoptimized(const int N, __global const float *a,
                                              __global const float *b,
                                              __global float *c)
{
    int y = get_global_id(0);
    int x = get_global_id(1);
    if((y < N) && (x < N))
    {
        c[y * N + x] = 0.0; 
        for(int k = 0; k < N; k++) 
        {
            c[y * N + x] += a[y * N + k] * b[k * N + x];
        }
    }
}


__kernel void matmul_localvar(const int N, __global const float *a,
                                           __global const float *b,
                                           __global float *c)
{
    int y = get_global_id(0);
    int x = get_global_id(1);
    if((y < N) && (x < N))
    {
        float sum = 0.0;
        for(int k = 0; k < N; k++) 
        {
            sum += a[y * N + k] * b[k * N + x];
        }
        c[y * N + x] = sum; 
    }
}