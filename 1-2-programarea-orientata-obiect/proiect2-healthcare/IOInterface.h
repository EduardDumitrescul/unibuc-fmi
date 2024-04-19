//
// Created by eduarddumitrescul on 4/23/23.
//

#ifndef OOP_HEALTHCARE_IOINTERFACE_H
#define OOP_HEALTHCARE_IOINTERFACE_H


#include <istream>

class IOInterface{
public:
    virtual std::istream& read(std::istream&) = 0;
    virtual std::ostream& print(std::ostream&) const= 0;
};


#endif //OOP_HEALTHCARE_IOINTERFACE_H
