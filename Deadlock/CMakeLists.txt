cmake_minimum_required(VERSION 3.12)
project(Deadlock)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-pthread")
add_executable(Deadlock main.cpp)