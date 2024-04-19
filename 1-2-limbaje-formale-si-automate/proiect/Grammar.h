//
// Created by eduarddumitrescul on 5/9/23.
//

#ifndef LFA_FINITE_AUTO_GRAMMAR_H
#define LFA_FINITE_AUTO_GRAMMAR_H


#include <utility>
#include <vector>
#include <fstream>

class Grammar {
    const static char LAMBDA = '#';
    int numberOfRules = 0;
    std::vector <std::pair <char, char>> v[256];

    bool check(char undetermined, std::string&, int);

    bool isDetermined(char);


public:
    Grammar();

    void addRule(char, char, char chr2 = ' ');

    void readFromFile(std::string);

    bool checkWord(std::string);
};


#endif //LFA_FINITE_AUTO_GRAMMAR_H
