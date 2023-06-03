//
// Created by eduarddumitrescul on 4/5/23.
//

#ifndef LFA_FINITE_AUTO_LAMBDANFA_H
#define LFA_FINITE_AUTO_LAMBDANFA_H


#include <unordered_map>
#include <vector>
#include <ostream>

class LambdaNFA {
    int numberOfStates;
    int startingState;
    std::unordered_map <int, std::vector <int>> transitions[256];
    std::unordered_map <int, bool> isFinal;

public:
    LambdaNFA(int startingState = 0, int numberOfStates = 1);

    LambdaNFA(const LambdaNFA& object);

    void addTransition(int source, char letter, int destination);

    void readFromFile(const std::string& inputFilename);

    friend std::ostream& operator <<(std::ostream &out, const LambdaNFA& object);

    bool checkWord(const std::string& word);

    int getLastStateIndex();

    void setFinal(int, bool);

    LambdaNFA& operator =(const LambdaNFA& object);

    LambdaNFA concatenate(const LambdaNFA& object) const;

    LambdaNFA multiply() const;

    LambdaNFA merge(const LambdaNFA& object) const;

    const static char LAMBDA = '#';
};


#endif //LFA_FINITE_AUTO_LAMBDANFA_H
