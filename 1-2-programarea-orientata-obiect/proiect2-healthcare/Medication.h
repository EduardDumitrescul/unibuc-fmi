//
// Created by eduarddumitrescul on 3/30/23.
//

#ifndef OOP_HEALTHCARE_MEDICATION_H
#define OOP_HEALTHCARE_MEDICATION_H


#include <string>
#include "Date.h"

struct Medication {
    std::string name;
    float dosage;
    std::string frequency;
    Date duration;

    Medication(std::string name = "dubious medication", float dosage = 3, std::string frequency = "daily", Date duration = {0, 3, 0})  {
        this->name = name;
        this->dosage = dosage;
        this->frequency = frequency;
        this->duration = duration;
    }

    std::string asString() {
        return name + " - " + std::to_string(dosage) + " " + frequency + "," + duration.asString();
    }

    friend std::istream& operator >>(std::istream& in, Medication& object) {
        std::cout << "Insert name: ";
        in.get();
        std::getline(in, object.name);
        std::cout << "Insert dosage [float]: ";
        in >> object.dosage;
        std::cout << "Insert frequency [string]: ";
        in.get();
        std::getline(in, object.frequency);
        std::cout << "Insert duration: ";
        in >> object.duration;
        return in;
    }
};


#endif //OOP_HEALTHCARE_MEDICATION_H
