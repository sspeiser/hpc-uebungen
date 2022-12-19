cmake_minimum_required(VERSION 3.10)
project(cpublocked)

add_executable(blocked-soln blocked-soln.c)

find_package(OpenMP REQUIRED)

target_link_libraries(blocked-soln PUBLIC OpenMP::OpenMP_C)

