cmake_minimum_required(VERSION 3.12)
project(FuturePromiseAndAsync)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
add_executable(FuturePromiseAndAsync main.cpp)