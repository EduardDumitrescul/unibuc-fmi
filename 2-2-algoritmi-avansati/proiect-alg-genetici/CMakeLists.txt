cmake_minimum_required(VERSION 3.27)
project(proiect_alg_genetici)

set(CMAKE_CXX_STANDARD 17)

add_executable(proiect_alg_genetici main.cpp
        InputReader.h
        QuadraticFunction.h
        Algorithm.h
        Population.h
        Chromosome.h
        FileWriter.h)
