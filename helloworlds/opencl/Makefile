# MacOS
# all:
# gcc -framework OpenCL -o dumpcl.out dumpcl.c
# gcc -framework OpenCL -o helloopencl.out helloopencl.c
# 	...

# Windows
all:
	gcc -I$(CUDA_PATH)/include -L$(CUDA_PATH)/lib/x64 -lOpenCL -o helloopencl.exe helloopencl.c
	gcc -I$(CUDA_PATH)/include -L$(CUDA_PATH)/lib/x64 -lOpenCL -o dumpcl.exe dumpcl.c
