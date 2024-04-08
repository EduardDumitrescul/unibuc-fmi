//
// Created by eduard on 4/5/24.
//

#ifndef PROIECT_ALG_GENETICI_CHROMOSOME_H
#define PROIECT_ALG_GENETICI_CHROMOSOME_H

#include <vector>
#include <cstdlib>
#include <ctime>

class Chromosome {
private:
    std::vector <bool> x;
public:
    Chromosome(int length) {
        x = std::vector<bool>(length, 0);
    }

    static Chromosome randomChromosome(int length) {
        Chromosome chromsome(length);
        for(int i = 0; i < length; i ++) {
            chromsome.x[i] = std::rand() % 2;
        }
        return chromsome;
    }

    std::string toString() {
        std::string s;
        for(auto b: x) {
            s.push_back('0' + b);
        }
        return s;
    }

    long double getValue(std::pair <int, int> range) {
        long double temp = 0;
        long double high = std::pow(2, x.size()) - 1;
        for(int i = 0; i < x.size(); i ++) {
            temp = 2*temp + x[i];
        }
        return (1.0 * range.second - range.first) * temp / high + range.first;
    }

    long double getFitness(QuadraticFunction f) {
        long double value = getValue(f.getRange());
        return f.getValue(value);
    }

    int crossover(Chromosome& other) {
        int pos = rand() % (x.size() + 1);
        for(int i = pos; i < x.size(); i ++) {
            std::vector<bool, std::allocator<bool>>::swap(x[i], other.x[i]);
        }
        return pos;
    }

    bool mutate(long double mutationProbability) {
        bool mutated = false;
        for(int i = 0; i < x.size(); i ++) {
            long double h = (long double)rand() / RAND_MAX;
            if(h < mutationProbability) {
                x[i] = !x[i];
                mutated = true;
            }
        }
        return mutated;
    }
};

struct ChromosomeWithData {
    Chromosome chromosome;
    long double value;
    long double fitness;
    long double selectionProbability;
    long double randomValue = 0;

    ChromosomeWithData(
            Chromosome chromosome,
            long double x=0,
            long double f=0,
            long double s=0
                    ): chromosome(chromosome) {
        this->value = x;
        this->fitness = f;
        this->selectionProbability = s;
    }
};

struct CrossoverDetails {
    CrossoverDetails(): init1(0), init2(0), fin1(0), fin2(0) {

    }

    int pos{};
    int index1{}, index2{};
    Chromosome init1, init2, fin1, fin2;
};

#endif //PROIECT_ALG_GENETICI_CHROMOSOME_H
