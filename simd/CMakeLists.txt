cmake_minimum_required(VERSION 3.10)
project(SIMD)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mavx")

add_executable(matrixadd-simd-soln matrixadd-simd-soln.c)
add_executable(matrixadd-simd matrixadd-simd.c)

