cmake_minimum_required(VERSION 3.10)
project(OpenCLBenchmark)

add_executable(opencl-benchmark opencl-benchmark-soln.c)

# file(GLOB kernels RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.cl")
set(kernels "benchmark-soln.cl")
foreach(kernel ${kernels})
  configure_file(${kernel} ${kernel} COPYONLY)
  message(${kernel})
endforeach()

find_package(OpenCL REQUIRED)

INCLUDE_DIRECTORIES(${OpenCL_INCLUDE_DIRS}) 

target_link_libraries(opencl-benchmark ${OpenCL_LIBRARY})