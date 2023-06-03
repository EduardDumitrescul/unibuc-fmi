//
// Created by eduarddumitrescul on 5/9/23.
//

#include "Grammar.h"

Grammar::Grammar() {
    numberOfRules = 0;
}

void Grammar::addRule(char start, char chr1, char chr2) {
    this->v[start].push_back({chr1, chr2});
}

void Grammar::readFromFile(std::string filename) {
    std::ifstream fin(filename);
    fin >> this->numberOfRules;
    std::string temp;
    std::getline(fin, temp);
    for(int i = 0; i < this->numberOfRules; i ++) {
        char c1, c2, c3;
        std::string s;
        std::getline(fin, s);
        c1 = s[0];
        c2 = s[2];
        if(s.size() >= 4)
            c3 = s[4];
        else
            c3 = ' ';
        this->addRule(c1, c2, c3);
    }
}

bool Grammar::checkWord(std::string word) {
    return check('S', word, 0);
}

bool Grammar::check(char undetermined, std::string& word, int pos) {
    if(pos == word.size())
    for(auto it: v[undetermined]) {
        if(Grammar::LAMBDA == it.first)
            return true;
    }
    if(pos > word.size())
        return false;
    if(pos == word.size() and (undetermined == ' ' or undetermined == Grammar::LAMBDA))
        return true;
    else if(pos == word.size())
        return false;
    if(undetermined == Grammar::LAMBDA or undetermined == ' ')
        return false;
    bool ok = false;
    for(auto it: v[undetermined]) {
        if(word[pos] == it.first)
            ok = ok | this->check(it.second, word, pos + 1);

    }
    return ok;
}

bool Grammar::isDetermined(char chr) {
    return ('a' <= chr and chr <= 'z') or chr == Grammar::LAMBDA;
}
