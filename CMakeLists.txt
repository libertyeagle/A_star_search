cmake_minimum_required(VERSION 3.12)
project(maze)

set(CMAKE_CXX_STANDARD 11)

add_executable(a_star main_a_star.cpp maze.hpp maze.cpp a_star.cpp id_a_star.cpp search.cpp)
add_executable(ida_star main_id_a_star.cpp maze.hpp maze.cpp a_star.cpp id_a_star.cpp search.cpp)