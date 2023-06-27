cmake_minimum_required(VERSION 3.21)
project(ch5)

set(CMAKE_CXX_STANDARD 14)

add_executable(ch5 main.cpp)
target_link_libraries(ch5 pthread)