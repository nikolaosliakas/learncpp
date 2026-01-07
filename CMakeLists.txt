cmake_minimum_required(VERSION 3.20)
project(learncpp)

set(CMAKE_CXX_STANDARD 20)

# 1. Find all .cpp files in the current directory
file(GLOB files *.cpp)

# 2. Loop through each file and create an executable for it
foreach(file ${files})
    get_filename_component(name ${file} NAME_WE)
    add_executable(${name} ${file}
            io.cpp
            introIfQuestion2And3.cpp)
endforeach()