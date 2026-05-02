cmake_minimum_required(VERSION 3.21)
project(concurrency_in_action)

set(CMAKE_CXX_STANDARD 17)

add_executable(HelloWorld HelloWorld.cpp)
add_executable(Chapter_2 Chapter_2.cpp)
add_executable(learn_std_optional learn_std_optional.cpp)

# https://stackoverflow.com/questions/63947874/how-do-i-include-the-eigen-library-in-a-cmakelist-txt-on-windows
set(EIGEN3_INCLUDE_DIR "$ENV{EIGEN3_INCLUDE_DIR}")
set(CMAKE_MODULE_PATH "$ENV{EIGEN3_DIR}")
message("We have: ${EIGEN3_INCLUDE_DIR}")
#append(CMAKE_MODULE_PATH "$ENV{EIGEN3_DIR}")
find_package (Eigen3 3.4.0 REQUIRED NO_MODULE)
include_directories(${EIGEN3_INCLUDE_DIR})
add_executable(Optimizing_Calculations Optimizing_Calculations.cpp)
target_link_libraries (Optimizing_Calculations Eigen3::Eigen)
