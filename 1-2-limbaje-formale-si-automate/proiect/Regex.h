//
// Created by eduarddumitrescul on 4/5/23.
//

#ifndef LFA_FINITE_AUTO_REGEX_H
#define LFA_FINITE_AUTO_REGEX_H


#include <string>
#include "LambdaNFA.h"

class Regex {
    std::string exp;

    std::string toPostfix(std::string);
public:
    Regex(std::string exp = "");

    LambdaNFA asLambdaNFA();
};


#endif //LFA_FINITE_AUTO_REGEX_H
