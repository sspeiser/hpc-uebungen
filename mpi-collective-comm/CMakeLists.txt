cmake_minimum_required(VERSION 3.10)
project(mpicomm)

add_executable(mpi-coll-comm-soln mpi-coll-comm-soln.c)

find_package(MPI REQUIRED)
include_directories(${MPI_INCLUDE_PATH})
set(CMAKE_C_FLAGS "${CMAKE_FLAGS} ${MPI_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${MPI_EXE_LINKER_FLAGS}")

target_link_libraries(mpi-coll-comm-soln ${MPI_LIBRARIES})