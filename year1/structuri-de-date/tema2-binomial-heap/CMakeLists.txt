cmake_minimum_required(VERSION 3.24)
project(sd_binomial_heap)

set(CMAKE_CXX_STANDARD 17)

add_executable(sd_binomial_heap main.cpp BinomialHeap.cpp BinomialHeap.h)
