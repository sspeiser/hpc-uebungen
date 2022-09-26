cmake_minimum_required(VERSION 3.10)
project(OpenCLHellos)

add_executable(dumpcl dumpcl.c)
add_executable(helloopencl helloopencl.c)
add_executable(opencl-skeleton opencl-skeleton.c)

# file(GLOB kernels RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.cl")
set(kernels "opencl-program.cl")
foreach(kernel ${kernels})
  configure_file(${kernel} ${kernel} COPYONLY)
  message(${kernel})
endforeach()

find_package(OpenCL REQUIRED)

INCLUDE_DIRECTORIES(${OpenCL_INCLUDE_DIRS}) 

target_link_libraries(opencl-skeleton ${OpenCL_LIBRARY})
target_link_libraries(helloopencl ${OpenCL_LIBRARY})
target_link_libraries(dumpcl ${OpenCL_LIBRARY})