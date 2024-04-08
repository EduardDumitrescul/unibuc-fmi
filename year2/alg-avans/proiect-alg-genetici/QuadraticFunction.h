//
// Created by eduard on 4/5/24.
//

#ifndef PROIECT_ALG_GENETICI_QUADRATICFUNCTION_H
#define PROIECT_ALG_GENETICI_QUADRATICFUNCTION_H


#include <utility>

class QuadraticFunction {
private:
    int a, b, c;
    std::pair <int, int> range;

public:
    QuadraticFunction(int a, int b, int c, std::pair <int, int> range) {
        this->a = a;
        this->b = b;
        this->c = c;
        this->range = range;
    }

    long double getValue(long double x) {
        if(not (range.first <= x and x <= range.second)) {
            throw "Valoarea se afla in afara domeniului functiei";
        }
        return a*x*x+b*x+c;
    }

    std::pair <int, int> getRange() {
        return range;
    }

    int getRangeLength() {
        return range.second - range.first;
    }
};


#endif //PROIECT_ALG_GENETICI_QUADRATICFUNCTION_H
