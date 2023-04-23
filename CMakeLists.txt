cmake_minimum_required(VERSION 3.23)
project(COP3530-Project-3)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-O3")

add_executable(COP3530-Project-3 src/main.cpp src/HashTable.cpp src/HashTable.h src/Person.cpp src/Person.h src/RedBlack.cpp src/RedBlack.h)
