cmake_minimum_required(VERSION 3.10)
project(ProjetV2_0)

set(CMAKE_CXX_STANDARD 11)

add_executable(ProjetV2_0 main.cpp src/linkedList.cpp src/linkedList.h src/CNF.cpp src/CNF.h src/cnfExecutionTree.cpp src/cnfExecutionTree.h src/generator.cpp src/generator.h)