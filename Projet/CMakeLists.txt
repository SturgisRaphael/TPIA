cmake_minimum_required(VERSION 3.9)
project(Projet)

set(CMAKE_CXX_STANDARD 11)

add_executable(Projet main.cpp src/CNF.cpp src/cnfExecutionTree.cpp src/cnfExecutionTree.h src/clauseList.cpp src/clauseList.h src/literalList.cpp src/literalList.h)