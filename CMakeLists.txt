cmake_minimum_required(VERSION 3.23)
project(labs)

file(GLOB LABS LIST_DIRECTORIES true "src/*")

foreach(LAB ${LABS})
  if(IS_DIRECTORY ${LAB})
    get_filename_component(TARGET ${LAB} NAME)
    string(REGEX REPLACE "[()]" "_" TARGET ${TARGET})
    file(GLOB_RECURSE SOURCES "${LAB}/*.c")
    add_executable(${TARGET} ${SOURCES})
  endif()
endforeach()
