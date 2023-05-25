cmake_minimum_required(VERSION 3.23)
project(OAIP_labs C)

set(CMAKE_C_STANDARD 99)

file(GLOB_RECURSE SOURCES src/*.c)
add_executable(monster ${SOURCES})
