cmake_minimum_required(VERSION 3.10)
project(Caches C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra")

add_executable(matrixadd matrixadd.c)
add_executable(matrixadd-soln matrixadd-soln.c)
