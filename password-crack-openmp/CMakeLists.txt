cmake_minimum_required(VERSION 3.10)
project(OpenMPpassword)

add_executable(password-crack-soln password-crack-soln.c sha-256.h sha-256.c)
add_executable(password-crack password-crack.c sha-256.h sha-256.c)

find_package(OpenMP REQUIRED)

target_link_libraries(password-crack-soln PUBLIC OpenMP::OpenMP_C)
target_link_libraries(password-crack PUBLIC OpenMP::OpenMP_C)
