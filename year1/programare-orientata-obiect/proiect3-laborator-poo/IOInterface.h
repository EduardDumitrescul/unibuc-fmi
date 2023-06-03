//
// Created by eduarddumitrescul on 5/16/23.
//

#ifndef POO3_IOINTERFACE_H
#define POO3_IOINTERFACE_H

#include <istream>

class IOInterface{
public:
    virtual void read(std::istream& in) = 0;

    virtual void print(std::ostream& out) const = 0;
};

#endif //POO3_IOINTERFACE_H
