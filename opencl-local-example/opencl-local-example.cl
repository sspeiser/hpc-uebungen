__kernel void averages(const size_t n, __global const float *src, __global float *dst)
{
    size_t x = get_global_id(0);
    float avg = 0.0;
    for(int i=0; i<8; i++)
    {
        if(x + i < n)
            avg += src[x + i];
    }
    avg /= 8;
    dst[x] = avg;
}

__kernel void averages_local(const size_t n, __global const float *src, __global float *dst, __local float *buf)
{
    size_t x = get_global_id(0);
    size_t local_id = get_local_id(0);
    size_t group_id = get_group_id(0);
    size_t group_size = get_local_size(0);
    buf[local_id] = src[x];
    barrier(CLK_LOCAL_MEM_FENCE);
    float avg = 0.0;
    for(int i=0; i<8; i++)
    {
        if(i + local_id < group_size)
            avg += buf[local_id + i];
        else if(x + i < n)
            avg += src[x + i];
    }
    avg /= 8;
    dst[x] = avg;
}