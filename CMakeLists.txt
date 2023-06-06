cmake_minimum_required(VERSION 3.25)
project(Tarea2Log)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

add_executable(Tarea2Log src/main.cpp src/Permutations.cpp src/headers/Permutations.h src/SplayTree.cpp src/headers/SplayTree.h src/headers/AbstractTree.h src/RBTree.cpp src/headers/RBTree.h src/lib/progressbar.h)
