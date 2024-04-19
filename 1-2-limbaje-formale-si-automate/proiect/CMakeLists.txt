cmake_minimum_required(VERSION 3.24)
project(lfa_finite_auto)

set(CMAKE_CXX_STANDARD 17)

add_executable(lfa_finite_auto main.cpp DFA.cpp DFA.h NFA.cpp NFA.h Regex.cpp Regex.h LambdaNFA.cpp LambdaNFA.h Grammar.cpp Grammar.h)
