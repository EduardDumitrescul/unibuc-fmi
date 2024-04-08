//
// Created by eduard on 4/5/24.
//

#ifndef PROIECT_ALG_GENETICI_POPULATION_H
#define PROIECT_ALG_GENETICI_POPULATION_H

#include <vector>
#include <cstdlib>
#include <ctime>

#include "Chromosome.h"

class Population{
private:
    std::vector <Chromosome> chromosomes;

public:
    Population(int size, int length) {
        chromosomes = std::vector<Chromosome>();
        for(int i = 0; i < size; i ++) {
            chromosomes.emplace_back(length);
        }
    }

    static Population randomPopulation(int size, int length) {
        Population population(size, length);
        for(int i = 0; i < size; i ++) {
            population.chromosomes[i] = Chromosome::randomChromosome(length);
        }
        return population;
    }

    std::vector<ChromosomeWithData> computeFitness(QuadraticFunction f) {
        long double totalFitness = 0;
        std::vector<ChromosomeWithData> result;
        for(auto c: chromosomes) {
            long double x = c.getValue(f.getRange());
            long double fitness = c.getFitness(f);
            result.push_back(ChromosomeWithData(c, x, fitness));
            totalFitness += fitness;
        }

        for(auto& c: result) {
            c.selectionProbability = c.fitness / totalFitness;
        }
        return result;
    }

    long double findMax(QuadraticFunction f) {
        long double max = DBL_MIN;
        for(auto c: chromosomes) {
            max = std::max(max, c.getFitness(f));
        }
        return max;
    }

    void addChromosome(Chromosome chromosome) {
        chromosomes.push_back(chromosome);
    }

    int getSize() {
        return chromosomes.size();
    }

    std::vector <Chromosome> getChromosomes() {
        return chromosomes;
    }

    Chromosome getBestChromosome(QuadraticFunction f) {
        long double max = DBL_MIN;
        int index = -1;
        for(int i = 0; i < chromosomes.size(); i ++) {
            long double fit = chromosomes[i].getFitness(f);
            if(max < fit) {
                max = fit;
                index = i;
            }
        }
        return chromosomes[index];
    }


    Chromosome extractBestChromosome(QuadraticFunction f ) {
        long double max = chromosomes[0].getFitness(f);
        int index = 0;
        for(int i = 1; i < chromosomes.size(); i ++) {
            long double fit = chromosomes[i].getFitness(f);
            if(max < fit) {
                max = fit;
                index = i;
            }
        }
        Chromosome best = chromosomes[index];
        chromosomes.erase(chromosomes.begin() + index);
        return best;
    }
};

#endif //PROIECT_ALG_GENETICI_POPULATION_H
