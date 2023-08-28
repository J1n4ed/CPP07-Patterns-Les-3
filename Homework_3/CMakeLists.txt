cmake_minimum_required(VERSION 3.26)

project(exec LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR})
add_executable( exec main.cpp chain.cpp )