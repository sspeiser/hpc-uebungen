cmake_minimum_required(VERSION 3.20)
project(graustufen C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(graustufen
        graustufen-loop.c
        stb_image.h
        stb_image_write.h)

add_executable(graustufen-soln
        graustufen-loop-soln.c
        stb_image.h
        stb_image_write.h)
