# MacOS
macos:
	clang -framework OpenCL -o opencl-local-example.out opencl-local-example.c
macos-soln:
	clang -framework OpenCL -o opencl-local-example-soln.out opencl-local-example-soln.c


# Windows
all:
	gcc -I"$(CUDA_PATH)/include" -L"$(CUDA_PATH)/lib/x64" -o opencl-local-example.exe opencl-local-example.c -lOpenCL 

soln:
	gcc -I"$(CUDA_PATH)/include" -L"$(CUDA_PATH)/lib/x64" -o opencl-local-example-soln.exe opencl-local-example-soln.c -lOpenCL 
