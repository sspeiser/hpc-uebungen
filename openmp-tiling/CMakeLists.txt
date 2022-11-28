cmake_minimum_required(VERSION 3.10)
project(OpenMPtiling)

add_executable(openmp-tiling openmp-tiling-soln.c)
add_executable(openmp-tiling-soln openmp-tiling-soln.c)

find_package(OpenMP REQUIRED)

target_link_libraries(openmp-tiling PUBLIC OpenMP::OpenMP_C)
set_property(TARGET openmp-tiling PROPERTY C_STANDARD 99)

target_link_libraries(openmp-tiling-soln PUBLIC OpenMP::OpenMP_C)
set_property(TARGET openmp-tiling-soln PROPERTY C_STANDARD 99)
