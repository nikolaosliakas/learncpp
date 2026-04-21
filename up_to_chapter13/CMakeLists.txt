cmake_minimum_required(VERSION 3.20)
project(learncpp)

# Force C++20 and make it mandatory
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find all .cpp files
file(GLOB files *.cpp)

foreach(file ${files})
    get_filename_component(name ${file} NAME_WE)
    add_executable(${name} ${file})
endforeach()