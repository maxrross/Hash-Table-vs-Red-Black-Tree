cmake_minimum_required(VERSION 3.23)
project(HashTable)

set(CMAKE_CXX_STANDARD 14)

add_executable(HashTable src/main.cpp src/HashTable.cpp src/HashTable.h src/Person.cpp src/Person.h)
