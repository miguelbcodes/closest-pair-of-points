cmake_minimum_required(VERSION 3.10)
project(ClosestPairOfPoints)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(closest_pair closest_pair.cpp)

target_compile_options(closest_pair PRIVATE -O3 -Wall -Wextra)
