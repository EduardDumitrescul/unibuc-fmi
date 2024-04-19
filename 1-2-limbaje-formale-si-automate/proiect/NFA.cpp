//
// Created by eduarddumitrescul on 3/11/23.
//

#include <string>
#include <fstream>
#include <unordered_set>
#include "NFA.h"
#include <bitset>
#include <deque>

NFA::NFA(int startingState) {
    this->startingState = startingState;
}

void NFA::addTransition(int source, char letter, int destination) {
    this->transitions[letter][source].push_back(destination);
}

void NFA::readFromFile(const std::string &inputFilename) {
    std::ifstream fin(inputFilename);

    int states, transCount, finalStates;
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

bool NFA::checkWord(const std::string &word) {
    std::unordered_set <int> currentStates = {this->startingState};
    for(char letter: word) {
        std::unordered_set <int> nextStates;
        for(int state: currentStates){
            for(int next: transitions[letter][state])
                nextStates.insert(next);
        }
        currentStates = nextStates;
    }
    for(int state: currentStates) {
        if(isFinal[state]) {
            return true;
        }
    }
    return false;
}

void NFA::nfaDfs(int state, const std::string& word, int pos, std::vector <std::vector <int>>& paths, std::vector <int> &currentPath) {
    if(pos == word.size()) {
        if(this->isFinal[state]) {
            paths.push_back(currentPath);
        }

        return;
    }
    char currentLetter = word[pos];
    for(int nextState: this->transitions[currentLetter][state]) {
        currentPath.push_back(nextState);
        nfaDfs(nextState, word, pos+1, paths, currentPath);
        currentPath.pop_back();
    }
}

std::vector <std::vector <int>> NFA::checkWordReturnPaths(const std::string& word) {
    std::vector <std::vector <int>> paths;
    std::vector <int> currentPath{this->startingState};
    this->nfaDfs(this->startingState, word, 0, paths, currentPath);
    return paths;
}

DFA NFA::asDFA() {
    DFA dfa(this->startingState);

    const int bitset_size = 32;

    std::unordered_map<std::bitset<bitset_size>, int> map;

    std::bitset <bitset_size> currentState;
    currentState[this->startingState] = true;
    int countState = 0;
    std::unordered_map <int, bool> visited;
    visited[map[currentState]] = true;
    map[currentState] = countState++;


    std::deque <std::bitset <bitset_size>> dq;
    dq.emplace_back(currentState);

    while(!dq.empty()) {
        currentState = dq.front();
        dq.pop_front();
        for(int i = 0; i < bitset_size; i ++) {
            if(currentState[i] and this->isFinal[i]) {
                dfa.setFinalState(map[currentState], true);
            }
        }

        for(char letter = 'a'; letter <= 'z'; letter ++) {
            std::bitset<bitset_size> nextState;
            for(int i = 0; i < bitset_size; i ++) {
                if(currentState[i]) {
                    for(int next: transitions[letter][i]) {
                        nextState[next] = true;
                    }
                }
            }
            if(nextState.count() == 0) {
                continue;
            }

            if(map.find(nextState) == map.end()) {
                map[nextState] = countState ++;
            }
            dfa.addTransition(map[currentState], letter, map[nextState]);
            if(visited[map[nextState]]) {
                continue;
            }
            visited[map[nextState]] = true;
            dq.push_back(nextState);
        }
    }
    return dfa;
}

std::ostream &operator<<(std::ostream &out, const NFA &object) {
    out << "Starting State: " << object.startingState << '\n';
    out << "Final States: ";
    for(auto it: object.isFinal) {
        if(it.second)
            out << it.first << ' ';
    }
    out << '\n';
    for(char letter='a'; letter <= 'z'; letter ++) {
        for(const auto& it: object.transitions[letter]) {
            for(int i: it.second) {
                out << it.first << ' ' << letter << ' ' << i << '\n';
            }
        }
    }
    return out;
}
