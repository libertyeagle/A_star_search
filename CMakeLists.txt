cmake_minimum_required(VERSION 3.12)
project(maze)

set(CMAKE_CXX_STANDARD 11)

add_executable(main main.cpp maze.h maze.cpp a_star.cpp id_a_star.cpp)