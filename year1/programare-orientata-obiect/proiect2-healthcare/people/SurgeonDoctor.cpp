//
// Created by eduarddumitrescul on 3/30/23.
//

#include <iostream>
#include "SurgeonDoctor.h"
#include "../DrawingUtil.h"


SurgeonDoctor::SurgeonDoctor(std::string firstname, std::string lastname, int experience, int salary,
                             std::string specialty, int successfulSurgeries, int failedSurgeires):
Doctor(firstname, lastname, experience, salary){
    this->specialty = specialty;
    this->successfulSurgeries = successfulSurgeries;
    this->failedSurgeries = failedSurgeires;
}
SurgeonDoctor::SurgeonDoctor(const SurgeonDoctor &object):
Doctor(object){
    this->specialty = object.specialty;
    this->successfulSurgeries = object.successfulSurgeries;
    this->failedSurgeries = object.failedSurgeries;
}

SurgeonDoctor &SurgeonDoctor::operator=(const SurgeonDoctor & object) {
    if(this != &object) {
        ((Doctor&)*this) = ((Doctor&)object);
        this->specialty = object.specialty;
        this->successfulSurgeries = object.successfulSurgeries;
        this->failedSurgeries = object.failedSurgeries;
    }
    return *this;
}

std::istream &operator>>(std::istream & in, SurgeonDoctor & object) {
    in >> (Doctor&) object;
    std::cout << "Insert specialty: ";
    in >> object.specialty;
    std::cout << "Insert number of successful surgeries: ";
    in >> object.successfulSurgeries;
    std::cout << "Insert number of failed surgeries: ";
    in >> object.failedSurgeries;
    return in;
}

std::ostream &operator<<(std::ostream & out, const SurgeonDoctor & object) {
    out << (Doctor&) object;
    out << "Specialty: " << object.specialty << '\n';
    out << "Number of successful surgeries: " << object.successfulSurgeries << '\n';
    out << "Number of failed surgeries: " << object.failedSurgeries << '\n';
    return out;
}

void SurgeonDoctor::printCard(std::ostream & out) const{
    PersonCard card(this->id, "Surgeon", this->getName(), this->experience, this->salary, this->specialty, this->successfulSurgeries, this->failedSurgeries);
    for(auto& s: card.card) {
        out << s;
    }
}

void SurgeonDoctor::setSpecialty(std::string specialty) {
    this->specialty = specialty;
}

void SurgeonDoctor::setSuccessfulSurgeries(int successful) {
    this->successfulSurgeries = successful;
}

void SurgeonDoctor::setFailedSurgeries(int failed) {
    this->failedSurgeries = failed;
}

std::string SurgeonDoctor::shortString() const {
    return this->firstname + " " + this->lastname + "- SURGEON - exp " + std::to_string(this->experience)
    + " " + std::to_string(this->successfulSurgeries) + "/" + std::to_string(this->failedSurgeries);
}

void SurgeonDoctor::success() {
    this->successfulSurgeries ++;
}
void SurgeonDoctor::fail() {
    this->failedSurgeries ++;
}
