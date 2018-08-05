cmake_minimum_required(VERSION 3.12)
project(Unique_Lock)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_executable(Unique_Lock main.cpp)