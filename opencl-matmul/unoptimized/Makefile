# MacOS
macos:
	clang -framework OpenCL -o matmul-unoptimized.out matmul-unoptimized.c
macos-soln:
	clang -framework OpenCL -o matmul-unoptimized-soln.out matmul-unoptimized-soln.c


# Windows
all:
	gcc -I"$(CUDA_PATH)/include" -L"$(CUDA_PATH)/lib/x64" -o matmul-unoptimized.exe matmul-unoptimized.c -lOpenCL 

soln:
	gcc -I"$(CUDA_PATH)/include" -L"$(CUDA_PATH)/lib/x64" -o matmul-unoptimized-soln.exe matmul-unoptimized-soln.c -lOpenCL 
