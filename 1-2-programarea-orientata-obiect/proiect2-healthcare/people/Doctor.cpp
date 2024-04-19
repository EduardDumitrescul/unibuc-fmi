//
// Created by eduarddumitrescul on 3/30/23.
//

#include <iostream>
#include "Doctor.h"
#include "../DrawingUtil.h"

int Doctor::idCount = 1000;

Doctor::Doctor(std::string firstname, std::string lastname, int experience, int salary) : id(++idCount) {
    this->firstname = firstname;
    this->lastname = lastname;
    this->experience = experience;
    this->salary = salary;
}

Doctor::Doctor(const Doctor &object) : id(++idCount) {
    this->firstname = object.firstname;
    this->lastname = object.lastname;
    this->experience = object.experience;
    this->salary = object.salary;
}

Doctor &Doctor::operator=(const Doctor & object) {
    if(this != &object) {
        this->firstname = object.firstname;
        this->lastname = object.lastname;
        this->experience = object.experience;
        this->salary = object.salary;
    }
    return *this;
}

std::istream &operator>>(std::istream & in, Doctor & object) {
    return object.read(in);;
}

std::ostream &operator<<(std::ostream & out, const Doctor & object) {
    return     object.print(out);;
}

std::string Doctor::toString() const {
    return "DOCTOR ID: " + std::to_string(this->id) + " - " + this->firstname + " " + this->lastname;
}

int Doctor::getId() const {
    return this->id;
}

std::string Doctor::getName() const {
    return this->firstname + " " + this->lastname;
}

void Doctor::printCard(std::ostream & out) const {
    PersonCard card(this->id, "DOCTOR", this->getName(), this->experience, this->salary);
    for(auto& s: card.card) {
        out << s;
    }
}

void Doctor::setFirstname(std::string firstname) {
    this->firstname = firstname;
}

void Doctor::setLastname(std::string lastname) {
    this->lastname = lastname;
}

void Doctor::setExperience(int experience) {
    this->experience = experience;
}

void Doctor::setSalary(int salary) {
    this->salary = salary;
}

std::string Doctor::shortString() const {
    return this->firstname + " " + this->lastname + " - DOCTOR - exp" + std::to_string(this->experience);
}

Doctor::~Doctor() {

}

std::istream &Doctor::read(std::istream &in) {
    std::cout << "Insert firstname: ";
    in.get();
    std::getline(in, this->firstname);
    std::cout << "Insert lastname: ";
    std::getline(in, this->lastname);
    std::cout << "Insert years of experience [number]: ";
    in >> this->experience;
    std::cout << "Insert salary [number]: ";
    in >> this->salary;
    return in;
}

std::ostream &Doctor::print(std::ostream &out) const {
    std::cout << "DOCTOR  -  ID: " << this->id << '\n';
    std::cout << "Firstname: " << this->firstname << '\n';
    std::cout << "Lastname: " << this->lastname << '\n';
    std::cout << "Years of experience: " << this->experience << '\n';
    std::cout << "Salary: " << this->salary << '\n';
    return out;
}
