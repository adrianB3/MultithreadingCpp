cmake_minimum_required(VERSION 3.10)
project(Intro)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")
find_package( Threads REQUIRED)
add_executable(Intro main.cpp)