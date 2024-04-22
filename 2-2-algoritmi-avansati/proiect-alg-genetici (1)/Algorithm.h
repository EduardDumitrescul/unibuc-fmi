//
// Created by eduard on 4/5/24.
//

#ifndef PROIECT_ALG_GENETICI_ALGORITHM_H
#define PROIECT_ALG_GENETICI_ALGORITHM_H

#include <iostream>
#include <cmath>
#include <bitset>
#include <cfloat>
#include "InputReader.h"
#include "Population.h"
#include "FileWriter.h"



class Algorithm {
private:
    AlgorithmData data;
    int chromosomeLength;
    FileWriter writer;


    void computeChromosomeLength() {
        long double temp = data.precision * log2(10) + log2(data.f.getRangeLength());
        chromosomeLength = temp;
        if(chromosomeLength < temp) {
            chromosomeLength += 1;
        }
    }

    std::vector <long double> computeIntervals(std::vector <ChromosomeWithData> chromosomes) {
        long double current = 0;
        std::vector <long double> intervals (1, 0);
        for(auto c: chromosomes) {
            current += c.selectionProbability;
            intervals.push_back(current);
        }
        return intervals;
    }

    std::vector <std::pair <long double, int>> selectChromosomes(std::vector <long double> intervals) {
        std::vector <std::pair <long double, int>> selected;
        for(int i = 0; i < data.populatinCount - 1; i ++) {
            long double u = 1.0 * rand() / RAND_MAX;

            int left = 0, right = intervals.size() - 1;
            while(left <= right) {
                int middle = (left + right) / 2;
                if(intervals[middle] < u) {
                    left = middle + 1;
                }
                else {
                   right = middle - 1;
                }
            }

            selected.push_back({u, right});
        }
        return selected;
    }

    Population getSelectedPopulation (Population currentPopulation, std::vector <std::pair <long double, int>> selected) {
        Population population = Population(0, 0);
        std::vector <Chromosome> chromosomes = currentPopulation.getChromosomes();
        for(auto it: selected) {
            population.addChromosome(chromosomes[it.second]);
        }
        return population;
    }

    void computeCrossingParticipants(std::vector <ChromosomeWithData>& chromosomes) {
        for(auto& c: chromosomes) {
            long double u = (long double)rand() / RAND_MAX;
            c.randomValue = u;
        }
    }

    std::vector <CrossoverDetails> crossoverPopulation(std::vector <ChromosomeWithData>& chromosomes) {
        int last = -1;
        std::vector <CrossoverDetails> crossovers;
        for(int i = 0; i < chromosomes.size(); i ++) {
            if(chromosomes[i].randomValue > data.crossoverProbability) {
                continue;
            }
            if(last == -1) {
                last = i;
                continue;
            }
            CrossoverDetails crossoverDetails;
            crossoverDetails.index1 = last;
            crossoverDetails.index2 = i;
            crossoverDetails.init1 = chromosomes[last].chromosome;
            crossoverDetails.init2 = chromosomes[i].chromosome;
            int pos = chromosomes[last].chromosome.crossover(chromosomes[i].chromosome);

            crossoverDetails.pos = pos;
            crossoverDetails.fin1 = chromosomes[last].chromosome;
            crossoverDetails.fin2 = chromosomes[i].chromosome;
            crossovers.push_back(crossoverDetails);

            last = -1;

        }
        return crossovers;
    }

    std::vector <int> mutatePopulation(std::vector <ChromosomeWithData>& chromosomes) {
        std::vector<int> mutated;
        for (int i = 0; i < chromosomes.size(); i++) {
            if (chromosomes[i].chromosome.mutate(data.mutationProbability)) {
                mutated.push_back(i);
            }
        }
        return mutated;
    }


public:
    Algorithm(AlgorithmData data, std::string path): data(data), writer(FileWriter(path)) {
        computeChromosomeLength();

    }

    void run() {
        std::vector <long double> maxs;
        Population population = Population::randomPopulation(data.populatinCount, chromosomeLength);
        maxs.push_back(population.findMax(data.f));
        for(int i = 0; i < data.stageCount; i ++) {
            population = runStage(population, i==0);
            maxs.push_back(population.findMax(data.f));
        }

        writer.printMaximums(maxs);
    }

    Population runStage(Population population, bool print = false) {




        std::vector <ChromosomeWithData> chromosomesWithData = population.computeFitness(data.f);
        if(print) {
            writer.printPopulationWithFitness(chromosomesWithData, "Populatia initiala");
            writer.printSelectionProbability(chromosomesWithData);
        }

        Chromosome best = population.extractBestChromosome(data.f);
        chromosomesWithData = population.computeFitness(data.f);


        std::vector <long double> intervals = computeIntervals(chromosomesWithData);

        if(print) {
            writer.printSelectionProbabilityIntervals(intervals);
        }


        std::vector <std::pair <long double, int>> selected = selectChromosomes(intervals);
        if(print) {
            writer.printSelectedChromosomes(selected);
        }

        Population selectedPopulation = getSelectedPopulation(population, selected);
        chromosomesWithData = selectedPopulation.computeFitness(data.f);
        if(print) {
            writer.printPopulationWithFitness(chromosomesWithData, "Dupa selectie");
        }

        computeCrossingParticipants(chromosomesWithData);
        if(print) {
            writer.printChromosomesCrossingProbability(chromosomesWithData, data.crossoverProbability);
        }

        std::vector <CrossoverDetails> crossovers = crossoverPopulation(chromosomesWithData);
        if(print) {
            writer.printCrossovers(crossovers);
            writer.printPopulationWithFitness(chromosomesWithData, "Dupa recombinare: ");
        }

        std::vector <int> mutated = mutatePopulation(chromosomesWithData);
        if(print) {
            writer.printMutations(mutated, data.mutationProbability);
            writer.printPopulationWithFitness(chromosomesWithData, "Dupa mutatie: ");
        }

        Population newPopulation = Population(0, 0);
        for(auto c: chromosomesWithData){
            newPopulation.addChromosome(c.chromosome);
        }
        newPopulation.addChromosome(best);
        //std::cout << population.getBestChromosome(data.f).getFitness(data.f) << '\n';

        return newPopulation;
    }


};


#endif //PROIECT_ALG_GENETICI_ALGORITHM_H
