# MacOS
macos:
	clang -framework OpenCL -o matmul-blocked.out matmul-blocked.c
macos-soln:
	clang -framework OpenCL -o matmul-blocked-soln.out matmul-blocked-soln.c


# Windows
all:
	gcc -I"$(CUDA_PATH)/include" -L"$(CUDA_PATH)/lib/x64" -o matmul-blocked.exe matmul-blocked.c -lOpenCL 

soln:
	gcc -I"$(CUDA_PATH)/include" -L"$(CUDA_PATH)/lib/x64" -o matmul-blocked-soln.exe matmul-blocked-soln.c -lOpenCL 
