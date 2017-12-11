cmake_minimum_required(VERSION 3.9)
project(Heaps)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -O3")
add_subdirectory(googletest)
include_directories(googletest/googletest/include)
include_directories(googletest/googlemock/include)

add_executable(runUnitTests TESTS/test.cpp IHeap.h PrimitiveHeap.cpp PrimitiveHeap.h BinomialHeap.cpp BinomialHeap.h TESTS/gtests.cpp)
target_link_libraries(runUnitTests gtest gmock)