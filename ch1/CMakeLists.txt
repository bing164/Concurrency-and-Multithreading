cmake_minimum_required(VERSION 3.21)
project(ch1)

set(CMAKE_CXX_STANDARD 14)

add_executable(ch1 main.cpp)
target_link_libraries(ch1 pthread)