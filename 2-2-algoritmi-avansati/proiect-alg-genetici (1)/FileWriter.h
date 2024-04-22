//
// Created by eduard on 4/5/24.
//

#ifndef PROIECT_ALG_GENETICI_FILEWRITER_H
#define PROIECT_ALG_GENETICI_FILEWRITER_H

#include <fstream>
#include <iomanip>
#include "Population.h"
#include "QuadraticFunction.h"

class FileWriter {
private:
    std::ofstream fout;

public:
    FileWriter(std::string path) {
        fout.open(path);
        fout << std::setprecision(10) << std::fixed;
    }

    void printPopulationWithFitness(std::vector <ChromosomeWithData> chromosomes, std::string title) {
        fout << title << "\n";
        for(int i = 0; i < chromosomes.size(); i ++) {
            fout << i+1  << ": " << chromosomes[i].chromosome.toString() << " ";
            fout << "value= "<< chromosomes[i].value << ' ';
            fout << "fitness= " << chromosomes[i].fitness << '\n';
        }
        fout << '\n';
    }

    void printSelectionProbability(std::vector <ChromosomeWithData> chromosomes) {
        fout << "Probabilitati selectie\n";
        for(int i = 0; i < chromosomes.size(); i ++) {
            fout << i+1  << ": probabilitate ";
            fout << chromosomes[i].selectionProbability << "\n";
        }
        fout << '\n';
    }

    void printSelectionProbabilityIntervals(std::vector <long double> intervals) {
        fout << "Intervale probabilitati de selectie\n";
        fout << intervals[0];
        for(int i = 1; i < intervals.size(); i++) {
            fout << " - " << intervals[i] + 1;
        }
        fout << "\n\n";
    }


    void printSelectedChromosomes(std::vector<std::pair <long double, int>> selected) {
        for(auto it: selected) {
            fout << "u=" << it.first << " selectam cromozomul " << it.second + 1 << '\n';
        }
        fout << '\n';
    }

    void printChromosomesCrossingProbability(std::vector <ChromosomeWithData> chromosomes, long double crossingProbability) {
        fout << "Probabilitatea de incrucisare " << crossingProbability << '\n';
        for(int i = 0; i < chromosomes.size(); i ++) {
            fout << i + 1 << ": " << chromosomes[i].chromosome.toString();
            fout << " u=" << chromosomes[i].randomValue;

            if(chromosomes[i].randomValue < crossingProbability) {
                fout << "<" << crossingProbability << " participa";
            }
            fout << '\n';
        }
    }

    void printCrossovers(std::vector <CrossoverDetails> crossovers) {
        for(auto it: crossovers) {
            fout << "Recombinare dintre cromozomul " << it.index1+1 << " cu cromozomul " << it.index2+1 << '\n';
            fout << it.init1.toString() << " - " << it.init2.toString() << " (punct " << it.pos << ")\n";
            fout << "Rezultat: " << it.fin1.toString() << " - " << it.fin2.toString() << '\n';
        }
        fout << '\n';
    }

    void printMutations(std::vector <int> mutated, long double mutationProbability) {
        fout << "Probabilitate de mutatie pentru fiecare gena " << mutationProbability << '\n';
        fout << "Au fost modificati cromozomii: \n";
        for(auto it: mutated) {
            fout << it << '\n';
        }
        fout << '\n';
    }

    void printMaximums(std::vector <long double> maxs) {
        fout << "Evolutia maximului: " << '\n';
        for(auto i: maxs) {
            fout << i << '\n';
        }
    }

};

#endif //PROIECT_ALG_GENETICI_FILEWRITER_H
