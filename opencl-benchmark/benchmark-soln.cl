__kernel void vector_add(__global const float *a, __global const float *b, __global float *c)
{
    int i = get_global_id(0);
    c[i] = a[i] + b[i];
}


__kernel void global_mem_access(__global float *data)
{
    int i = get_global_id(0);
    float a = data[i];
    data[i] = a + 1.0;
}

__kernel void only_flops(__global  float *data)
{
    int i = get_global_id(0);
    float a = data[i];
    #pragma unroll
    for(int j=0;j<64;j++)
    {
        a = a + 3.0;
        a = a * 8.0;
        a = a + 1.0;
        a = a * 4.0;
    }
    data[i] = a;
}
