cmake_minimum_required(VERSION 3.17)
project(maze_generator C)

set(CMAKE_C_STANDARD 99)

add_executable(maze_generator main.c struct.h maze_stack.c maze_stack.h)