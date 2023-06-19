cmake_minimum_required(VERSION 3.21)
project(ch4)

set(CMAKE_CXX_STANDARD 14)

add_executable(ch4 main.cpp)
target_link_libraries(ch4 pthread)