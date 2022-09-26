cmake_minimum_required(VERSION 3.10)
project(OpenCLLocalExample)

add_executable(opencl-local-example opencl-local-example.c)

# file(GLOB kernels RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.cl")
set(kernels "opencl-local-example.cl")
foreach(kernel ${kernels})
  configure_file(${kernel} ${kernel} COPYONLY)
  message(${kernel})
endforeach()

find_package(OpenCL REQUIRED)

INCLUDE_DIRECTORIES(${OpenCL_INCLUDE_DIRS}) 

target_link_libraries(opencl-local-example ${OpenCL_LIBRARY})
