cmake_minimum_required(VERSION 3.10)
project(CPUvsMEM)

add_executable(cpu-vs-mem-soln cpu-vs-mem-soln.c)
add_executable(cpu-vs-mem cpu-vs-mem.c)

find_package(OpenMP REQUIRED)

target_link_libraries(cpu-vs-mem-soln PUBLIC OpenMP::OpenMP_C)
target_link_libraries(cpu-vs-mem PUBLIC OpenMP::OpenMP_C)

