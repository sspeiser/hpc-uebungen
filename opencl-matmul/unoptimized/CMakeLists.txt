cmake_minimum_required(VERSION 3.10)
project(MatMulUnopt)

add_executable(matmul-unoptimized-soln matmul-unoptimized-soln.c)
add_executable(matmul-unoptimized matmul-unoptimized.c)

# file(GLOB kernels RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.cl")
set(kernels "matmul-unoptimized-soln.cl" "matmul-unoptimized.cl")
foreach(kernel ${kernels})
  configure_file(${kernel} ${kernel} COPYONLY)
  message(${kernel})
endforeach()

find_package(OpenCL REQUIRED)

INCLUDE_DIRECTORIES(${OpenCL_INCLUDE_DIRS}) 

target_link_libraries(matmul-unoptimized-soln ${OpenCL_LIBRARY})
target_link_libraries(matmul-unoptimized ${OpenCL_LIBRARY})
