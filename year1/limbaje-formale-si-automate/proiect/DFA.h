//
// Created by eduarddumitrescul on 3/10/23.
//

#ifndef LFA_FINITE_AUTO_DFA_H
#define LFA_FINITE_AUTO_DFA_H


#include <vector>
#include <unordered_map>
#include <string>

class DFA {
    int startingState;
    /** transitions[alpha][source][destination] -> there is a transition marked with letter alpha from state 'source' to state 'destination' **/
    std::unordered_map <int, int> transitions[256];
    std::unordered_map <int, bool> isFinal;

public:
    DFA(int startingState=0);

    DFA& operator=(const DFA& object);

    void addTransition(int source, char letter, int destination) ;

    void readFromFile(const std::string& inputFilename);

    bool checkWord(const std::string &word);
    std::vector <int> checkWordPrintPath(const std::string &word);

    void setFinalState(int state, bool final = true);

    friend std::ostream& operator <<(std::ostream &out, const DFA& dfa);
};


#endif //LFA_FINITE_AUTO_DFA_H
