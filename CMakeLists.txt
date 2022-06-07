cmake_minimum_required(VERSION 3.10)
project(wet2_new)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(wet2_new Company.cpp Company.h DynamicArray.cpp DynamicArray.h library2.h main2.cpp
        RankTree.cpp RankTree.h Employee.h Employee.cpp Hitechs.h Hitechs.cpp UnionFind.h)
