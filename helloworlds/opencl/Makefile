# MacOS
# all:
# gcc -framework OpenCL -o dumpcl.out dumpcl.c
# gcc -framework OpenCL -o helloopencl.out helloopencl.c
# 	...

# Windows
all:
	gcc -I"$(CUDA_PATH)/include" -L"$(CUDA_PATH)/lib/x64" -o helloopencl.exe helloopencl.c -lOpenCL 
	gcc -I"$(CUDA_PATH)/include" -L"$(CUDA_PATH)/lib/x64" -o dumpcl.exe dumpcl.c -lOpenCL 
