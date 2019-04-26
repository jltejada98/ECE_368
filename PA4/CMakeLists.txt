cmake_minimum_required(VERSION 3.13)
project(PA4 C)

set(CMAKE_C_STANDARD 99)

add_executable(PA4 pa4.c pa4.h build.c utility.c evaluate.c)