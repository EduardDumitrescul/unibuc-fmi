//
// Created by eduarddumitrescul on 4/5/23.
//

#include <fstream>
#include <unordered_set>
#include <iostream>
#include "LambdaNFA.h"

LambdaNFA::LambdaNFA(int startingState, int numberOfStates) {
    this->startingState = startingState;
    this->numberOfStates = numberOfStates;
}

void LambdaNFA::addTransition(int source, char letter, int destination) {
    this->transitions[letter][source].push_back(destination);
}

void LambdaNFA::readFromFile(const std::string& inputFilename) {
    std::ifstream fin(inputFilename);

    int states, transCount, finalStates;
    fin >> states >> this->startingState;
    this->numberOfStates = states;
    fin >> finalStates;
    while(finalStates --) {
        int fState;
        fin >> fState;
        this->isFinal[fState] = true;
    }
    fin >> transCount;
    while(transCount --) {
        char letter;
        int src, dest;
        fin >> src >> letter >> dest;
        this->addTransition(src, letter, dest);
    }
}

std::ostream& operator<<(std::ostream &out, const LambdaNFA& object) {
    out << "Number of States: " << object.numberOfStates << '\n';
    out << "Starting State: " << object.startingState << '\n';
    out << "Final States: ";
    for(auto it: object.isFinal) {
        if(it.second)
            out << it.first << ' ';
    }
    out << '\n';
    for(const auto& it: object.transitions[LambdaNFA::LAMBDA]) {
        for(int i: it.second) {
            out << it.first << ' ' << LambdaNFA::LAMBDA << ' ' << i << '\n';
        }
    }
    for(char letter='a'; letter <= 'z'; letter ++) {
        for(const auto& it: object.transitions[letter]) {
            for(int i: it.second) {
                out << it.first << ' ' << letter << ' ' << i << '\n';
            }
        }
    }
    return out;
}

bool LambdaNFA::checkWord(const std::string &word) {
    std::unordered_set <int> currentStates = {this->startingState};
    for(char letter: word) {
        bool wasUpdated = true;
        while(wasUpdated) {
            wasUpdated = false;
            for(int state: currentStates) {
                for(int next: transitions[LAMBDA][state]) {
                    if(currentStates.find(next) == currentStates.end()) {
                        wasUpdated = true;
                        currentStates.insert(next);
                    }
                }
            }
        }

        std::unordered_set <int> nextStates;
        for(int state: currentStates){
            for(int next: transitions[letter][state])
                nextStates.insert(next);
        }

        currentStates = nextStates;
    }

    bool wasUpdated = true;
    while(wasUpdated) {
        wasUpdated = false;
        for(int state: currentStates) {
            for(int next: transitions[LAMBDA][state]) {
                if(currentStates.find(next) == currentStates.end()) {
                    wasUpdated = true;
                    currentStates.insert(next);
                }
            }
        }
    }

    for(int state: currentStates) {
        if(isFinal[state]) {
            return true;
        }
    }
    return false;
}

LambdaNFA &LambdaNFA::operator=(const LambdaNFA &object) {
    if(this != &object) {
        this->numberOfStates = object.numberOfStates;
        this->startingState = object.startingState;
        for(int i = 0; i <= 255; i ++) {
            this->transitions[i] = object.transitions[i];
        }
        this->isFinal = object.isFinal;
    }
    return *this;
}

LambdaNFA::LambdaNFA(const LambdaNFA &object) {
    this->numberOfStates = object.numberOfStates;
    this->startingState = object.startingState;
    for(int i = 0; i <= 255; i ++) {
        this->transitions[i] = object.transitions[i];
    }
    this->isFinal = object.isFinal;
}

LambdaNFA LambdaNFA::concatenate(const LambdaNFA &object) const {
    LambdaNFA result(*this);

    for(const auto& it: object.transitions[LAMBDA]) {
        for(auto next: it.second) {
            result.transitions[LAMBDA][it.first + this->numberOfStates].push_back(next + this->numberOfStates);
        }
    }
    for(char letter = 'a'; letter <= 'z'; letter ++) {
        for(const auto& it: object.transitions[letter]) {
            for(auto next: it.second) {
                result.transitions[letter][it.first + this->numberOfStates].push_back(next + this->numberOfStates);
            }
        }
    }


    for(auto f: this->isFinal) {
        if(f.second) {
            result.transitions[LAMBDA][f.first].push_back(object.startingState + this->numberOfStates);
        }
    }

    result.isFinal.clear();
    for(auto f: object.isFinal) {
        if(f.second) {
            result.isFinal[f.first + this->numberOfStates] = true;
        }
    }
    result.numberOfStates += object.numberOfStates;

    //std::cout << "****** concatenate" << *this << "\n\n" << object << "\n\n" << result;
    return result;
}

int LambdaNFA::getLastStateIndex() {
    int max = 0;
    for(auto list: this->transitions[LAMBDA]){
        max = std::max(max, list.first);
        for(auto next: list.second) {
            max = std::max(max, next);
        }
    }
    for(char letter = 'a'; letter <= 'z'; letter ++) {
        for(const auto& list: this->transitions[letter]){
            max = std::max(max, list.first);
            for(auto next: list.second) {
                max = std::max(max, next);
            }
        }
    }
    return max;
}

LambdaNFA LambdaNFA::multiply() const {
    LambdaNFA result(*this);
    result.transitions[LAMBDA][result.numberOfStates].push_back(result.startingState);

    result.startingState = result.numberOfStates;
    result.numberOfStates ++;
    result.isFinal[result.startingState] = true;

    for(auto f: this->isFinal) {
        if(f.second) {
            result.transitions[LAMBDA][f.first].push_back(result.startingState);
        }
    }

    //std::cout << "****** multiply" << *this  << "\n\n" << result;
    return result;
}

LambdaNFA LambdaNFA::merge(const LambdaNFA &object) const {
    LambdaNFA result(*this);
    for(const auto& it: object.transitions[LAMBDA]) {
        for(auto next: it.second) {
            result.transitions[LAMBDA][it.first + this->numberOfStates].push_back(next + this->numberOfStates);
        }
    }
    for(char letter = 'a'; letter <= 'z'; letter ++) {
        for(const auto& it: object.transitions[letter]) {
            for(auto next: it.second) {
                result.transitions[letter][it.first + this->numberOfStates].push_back(next + this->numberOfStates);
            }
        }
    }

    for(auto f: object.isFinal) {
        if(f.second) {
            result.isFinal[f.first + this->numberOfStates] = true;
        }
    }
    result.numberOfStates += object.numberOfStates;

    result.transitions[LAMBDA][result.numberOfStates].push_back(this->startingState);
    result.transitions[LAMBDA][result.numberOfStates].push_back(object.startingState + this->numberOfStates);

    result.startingState = result.numberOfStates;
    result.numberOfStates ++;


    //std::cout << "****** merge" << *this << "\n\n" << object << "\n\n" << result;
    return result;
}

void LambdaNFA::setFinal(int state, bool final) {
    this->isFinal[state]  = final;
}
