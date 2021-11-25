# MacOS
macos:
	clang -framework OpenCL -o opencl-benchmark.out opencl-benchmark.c
macos-soln:
	clang -framework OpenCL -o opencl-benchmark-soln.out opencl-benchmark-soln.c


# Windows
all:
	gcc -I"$(CUDA_PATH)/include" -L"$(CUDA_PATH)/lib/x64" -o opencl-benchmark.exe opencl-benchmark.c -lOpenCL 

soln:
	gcc -I"$(CUDA_PATH)/include" -L"$(CUDA_PATH)/lib/x64" -o opencl-benchmark-soln.exe opencl-benchmark-soln.c -lOpenCL 
