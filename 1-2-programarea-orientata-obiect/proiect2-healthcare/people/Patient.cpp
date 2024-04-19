//
// Created by eduarddumitrescul on 3/30/23.
//

#include <iostream>
#include "Patient.h"
#include "../DrawingUtil.h"

int Patient::idCount = 1000;

Patient::Patient(std::string firstname, std::string lastname, char gender, int birthYear): id(++idCount) {
    this->firstname = firstname;
    this->lastname = lastname;
    this->sex = gender;
    this->birthYear = birthYear;
}

Patient::Patient(const Patient & object): id(++idCount) {
    this->firstname = object.firstname;
    this->lastname = object.lastname;
    this->sex = object.sex;
    this->birthYear = object.birthYear;
}

Patient &Patient::operator=(const Patient & object) {
    if(this != &object) {
        this->firstname = object.firstname;
        this->lastname = object.lastname;
        this->sex = object.sex;
        this->birthYear = object.birthYear;
    }
    return *this;
}

std::istream &operator>>(std::istream & in, Patient & object) {
    in.get();
    std::cout << "Insert first name: ";
    std::getline(in, object.firstname);
    std::cout << "Insert last name: ";
    std::getline(in, object.lastname);
    std::cout << "Insert sex [M/F]: ";
    in >> object.sex;
    if(object.sex != 'M' and object.sex != 'F') {
        object.sex = 'X';
    }
    std::cout << "Insert birth year: ";
    in >> object.birthYear;
    return in;
}

std::ostream &operator<<(std::ostream & out, const Patient & object) {
    out << "PATIENT  -  ID:  " << object.id << '\n';
    out << "First name: " << object.firstname << '\n';
    out << "Last name: " << object.lastname << '\n';
    out << "Birth year: " << object.birthYear << '\n';
    out << "Sex: " << object.sex << '\n';
    return out;
}

std::string Patient::toString() const {
    return "patient - id: " + std::to_string(this->id) + " " + this->firstname + " " + this->lastname;
}

int Patient::getId() const {
    return this->id;
}

std::string Patient::getName() const {
    return this->firstname + " " + this->lastname;
}
void Patient::printCard(std::ostream & out) const {
    PersonCard card(this->id, "PATIENT", this->getName(), this->sex, this->birthYear);
    for(auto& s: card.card) {
        out << s;
    }
}

void Patient::setFirstname(std::string firstname) {
    this->firstname = firstname;
}

void Patient::setLastname(std::string lastname) {
    this->lastname = lastname;
}

void Patient::setBirthyear(int birthyear) {
    this->birthYear = birthyear;
}
