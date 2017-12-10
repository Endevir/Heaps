cmake_minimum_required(VERSION 3.9)
project(Heaps)

set(CMAKE_CXX_STANDARD 14)

add_executable(Heaps main.cpp IHeap.h PrimitiveHeap.cpp PrimitiveHeap.h)