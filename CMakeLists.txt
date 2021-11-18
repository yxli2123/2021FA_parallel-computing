cmake_minimum_required(VERSION 3.10)
project(parallel_computing C)

set(CMAKE_C_STANDARD 11)

include_directories(open-mp)

add_executable(parallel_computing
        open-mp/main.c
        #open-mp/utils.c
        #open-mp/utils.h
        )

# openMP
FIND_PACKAGE(OpenMP REQUIRED)
if (OPENMP_FOUND)
    message("OPENMP FOUND")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif ()