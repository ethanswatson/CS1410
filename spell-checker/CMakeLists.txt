cmake_minimum_required(VERSION 3.6)
project(spell_checker)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp BinaryTreeNode.hpp BinarySearchTree.hpp)
add_executable(spell_checker ${SOURCE_FILES})