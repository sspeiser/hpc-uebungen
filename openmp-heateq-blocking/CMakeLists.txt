cmake_minimum_required(VERSION 3.10)
project(OpenMPheateq)

add_executable(heateq heateq.c    
	    	      stb_image.h
        	      stb_image_write.h)

find_package(OpenMP REQUIRED)

target_link_libraries(heateq PUBLIC OpenMP::OpenMP_C)
