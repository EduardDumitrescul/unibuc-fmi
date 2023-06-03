#include <iostream>
#include <fstream>
#include "DFA.h"
#include "NFA.h"
#include "LambdaNFA.h"
#include "Regex.h"
#include "Grammar.h"

void testDFA() {
    std::cout << "**************************\n";
    std::cout << "\n" << "TEST DFA\n\n";
    DFA dfa;
    dfa.readFromFile("../testfiles/dfa.in");
    std::cout << "Current DFA:\n" << dfa;
    std::ifstream fin("../testfiles/words.txt");
    int words;
    fin >> words;
    std::string temp;
    std::getline(fin, temp);
    while(words--) {
        std::string word;
        std::getline(fin, word);
        std::cout << word << ' ' << dfa.checkWord(word) << ": ";
        std::vector <int> path = dfa.checkWordPrintPath(word);
        for(int state: path)
            std::cout << state << ' ' ;
        std::cout << '\n';

    }
    fin.close();
}

void testNFA() {
    std::cout << "**************************\n";
    std::cout << "\n" << "TEST NFA\n\n";
    NFA nfa;
    nfa.readFromFile("../testfiles/nfa.in");
    std::cout << "Current NFA:\n" << nfa << '\n';
    std::ifstream fin("../testfiles/words.txt");
    DFA dfa = nfa.asDFA();
    std::cout << "NFA transformed to DFA\n" << dfa << '\n';
    int words;
    fin >> words;
    std::string temp;
    std::getline(fin, temp);
    while(words--) {
        std::string word;
        std::getline(fin, word);
        std::cout << "Current Word tested: " << word << '\n';
        std::cout << "DFA: " << dfa.checkWord(word) << '\n';
        auto dfaPath = dfa.checkWordPrintPath(word);
        std::cout << "DFA path: ";
        for(int i : dfaPath) {
            std::cout << i << ' ';
        }
        std::cout << '\n';
        std::cout << "NFA: " << nfa.checkWord(word) << '\n';
        auto paths = nfa.checkWordReturnPaths(word);
        std::cout << "Paths found: " << paths.size() << '\n';
        for(const auto& path: paths) {
            for(int i: path) {
                std::cout << i << ' ' ;
            }
            std::cout << '\n';
        }
        std::cout << "|-------------------------------\n";
    }
    fin.close();
}

void testLambdaNFA() {
    std::cout << "\n********************************\n\n";
    std::cout << "TEST Lambda NFA\n\n";
    LambdaNFA lambdaNfa;
    lambdaNfa.readFromFile("../testfiles/lambda_nfa.in");
    std::cout << "Current Lambda NFA:\n";

    std::ifstream fin("../testfiles/words.txt");
    std::cout << lambdaNfa;

    int words;
    fin >> words;
    std::string temp;
    std::getline(fin, temp);

    while(words--) {
        std::getline(fin, temp);
        std::cout << "Word: " << temp << ' ' << lambdaNfa.checkWord(temp) << '\n';
    }

}

void testLambdaNFAops() {
    LambdaNFA l1, l2, l3;
    l1.readFromFile("../testfiles/lambda_nfa.in");
    l2.readFromFile("../testfiles/lambda_nfa.in");

    l3 = l1.concatenate(l2);
    LambdaNFA l4 = l3.multiply();

    std::cout << l3 << '\n';
    std::cout << l4 << '\n';

    LambdaNFA l5 = l1.merge(l2);
    std::cout << l5 << '\n';
}

void testGrammar() {
    Grammar g;
    g.readFromFile("../testfiles/grammar.in");

    int n;
    std::cin >> n;
    while(n --) {
        std::string word;
        std::cin >> word;
        std::cout << word << " - " << g.checkWord(word) << '\n';
    }


}


int main() {
    //testDFA();
//    testNFA();
    //testLambdaNFAops();

////    Regex reg("a+b*(c+de)+(f+g*)i");
//    Regex reg("((aba)*+(cbc)*)((ac)+(ca))");
//    std::cout << reg.asLambdaNFA();

    testGrammar();
    return 0;
}
