//
// Created by eduard on 4/5/24.
//

#ifndef PROIECT_ALG_GENETICI_INPUTREADER_H
#define PROIECT_ALG_GENETICI_INPUTREADER_H


#include <fstream>
#include "QuadraticFunction.h"

struct AlgorithmData {
//    AlgorithmData(
//            int populationCount,
//            QuadraticFunction fitness,
//            long double precision,
//            long double crossoverProbability,
//            long double mutationProbability,
//            int stageCount
//            ) :  fitness(fitness) {
//        this->populatinCount = populationCount;
//        this->precision = precision;
//        this->crossoverProbability = crossoverProbability;
//        this->mutationProbability = mutationProbability;
//        this->stageCount = stageCount;
//    }

    int populatinCount{};
    QuadraticFunction f = QuadraticFunction (0, 0, 0, {0, 0});
    long double precision{};
    long double crossoverProbability{};
    long double mutationProbability{};
    int stageCount{};
};

class InputReader {
private:
    std::ifstream fin;
public:

    InputReader(std::string path) {
        fin.open(path);

    }

    AlgorithmData read() {
        AlgorithmData data;
        fin >> data.populatinCount;

        int a, b, c;
        std::pair <int, int> range;
        fin >> range.first >> range.second;
        fin >> a >> b >> c;
        data.f = QuadraticFunction(a, b, c, range);

        fin >> data.precision;
        fin >> data.crossoverProbability;
        fin >> data.mutationProbability;
        fin >> data.stageCount;

        return data;
    }
};




#endif //PROIECT_ALG_GENETICI_INPUTREADER_H
