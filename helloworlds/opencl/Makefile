# MacOS
macos:
	clang -framework OpenCL -o dumpcl.out dumpcl.c
	clang -framework OpenCL -o helloopencl.out helloopencl.c
	clang -framework OpenCL -o opencl-skeleton.out opencl-skeleton.c

# Windows
all:
	gcc -I"$(CUDA_PATH)/include" -L"$(CUDA_PATH)/lib/x64" -o helloopencl.exe helloopencl.c -lOpenCL 
	gcc -I"$(CUDA_PATH)/include" -L"$(CUDA_PATH)/lib/x64" -o dumpcl.exe dumpcl.c -lOpenCL 
	gcc -I"$(CUDA_PATH)/include" -L"$(CUDA_PATH)/lib/x64" -o opencl-skeleton.exe opencl-skeleton.c -lOpenCL 
