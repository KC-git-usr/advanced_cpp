cmake_minimum_required(VERSION 3.28)
project(zoox)

set(CMAKE_CXX_STANDARD 20)

add_executable(zoox main.cpp)
add_executable(dijstra dijstra.cpp)
add_executable(dijstra_2 dijstra_2.cpp)
add_executable(a_star a_star.cpp)
add_executable(a_star_2 a_star_2.cpp)