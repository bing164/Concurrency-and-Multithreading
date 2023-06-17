cmake_minimum_required(VERSION 3.21)
project(ch2)

set(CMAKE_CXX_STANDARD 14)

add_executable(ch2 main.cpp)
target_link_libraries(ch2 pthread)