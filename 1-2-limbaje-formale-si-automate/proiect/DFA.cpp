//
// Created by eduarddumitrescul on 3/10/23.
//

#include <fstream>
#include "DFA.h"

DFA::DFA(int startingState) {
    this->startingState = startingState;
}

void DFA::addTransition(int source, char letter, int destination) {
    transitions[letter][source] = destination;
}

bool DFA::checkWord(const std::string &word) {
    int currentState = this->startingState;
    for(char letter: word) {
        if(transitions[letter].find(currentState) == transitions[letter].end()) {
            return false;
        }
        currentState = transitions[letter][currentState];
    }
    return this->isFinal[currentState];
}

std::vector<int> DFA::checkWordPrintPath(const std::string &word) {
    std::vector <int> path = {this->startingState};
    int currentState = this->startingState;
    for(char letter: word) {
        if(transitions[letter].find(currentState) == transitions[letter].end()) {
            path.clear();
            return path;
        }
        currentState = transitions[letter][currentState];
        path.push_back(currentState);
    }
    if(!this->isFinal[currentState])
        path.clear();
    return path;
}

void DFA::readFromFile(const std::string& inputFilename) {
    int states, transCount, wordsCount, finalStates;
    std::ifstream fin(inputFilename);
    fin >> states >> this->startingState;
    fin >> finalStates;
    while(finalStates --) {
        int fState;
        fin >> fState;
        this->isFinal[fState] = true;
    }
    fin >> transCount;
    while(transCount--) {
        char letter;
        int src, dest;
        fin >> src >> letter >> dest;
        this->addTransition(src, letter, dest);
    }
}

void DFA::setFinalState(int state, bool final) {
    this->isFinal[state] = final;
}

DFA &DFA::operator=(const DFA &object) {
    if(this != &object) {
        this->startingState = object.startingState;
        for(char letter = 'a'; letter <= 'z'; letter ++)
            this->transitions[letter] = object.transitions[letter];
        this->isFinal = object.isFinal;
    }
    return *this;
}

std::ostream &operator<<(std::ostream &out, const DFA &object) {
    out << "Starting State: " << object.startingState << '\n';
    out << "Final States: ";
    for(auto it: object.isFinal) {
        if(it.second)
            out << it.first << ' ';
    }
    out << '\n';
    for(char letter='a'; letter <= 'z'; letter ++) {
        for(const auto& it: object.transitions[letter]) {
            out << it.first << ' ' << letter << ' ' << it.second << '\n';
        }
    }
    return out;
}
