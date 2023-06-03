//
// Created by eduarddumitrescul on 3/30/23.
//

#include <iostream>
#include "Treatment.h"

int Treatment::idCount = 1000;

Treatment::Treatment(Patient *patient, Doctor *doctor, Date startDate, Date endDate, std::string diagnosis,
                     std::string notes, bool successful, long long int cost) : id(++idCount) {
    this->patient = patient;
    this->doctor = doctor;
    this->startDate = startDate;
    this->endDate = endDate;
    this->diagnosis = diagnosis;
    this->notes = notes;
    this->successful = successful;
    this->cost = cost;
}

Treatment::Treatment(const Treatment &object ) : id(++idCount) {
    this->patient = object.patient;
    this->doctor = object.doctor;
    this->startDate = object.startDate;
    this->endDate = object.endDate;
    this->diagnosis = object.diagnosis;
    this->notes = object.notes;
    this->successful = object.successful;
    this->cost = object.cost;
}

Treatment &Treatment::operator=(const Treatment & object) {
    if(this != &object) {
        this->patient = object.patient;
        this->doctor = object.doctor;
        this->startDate = object.startDate;
        this->endDate = object.endDate;
        this->diagnosis = object.diagnosis;
        this->notes = object.notes;
        this->successful = object.successful;
        this->cost = object.cost;
    }
    return *this;
}

std::istream &operator>>(std::istream & in, Treatment & object) {
    std::cout << "Insert start date: " << '\n';
    in >> object.startDate;
    std::cout << "Insert end date: " << '\n';
    in >> object.endDate;
    std::cout << "Insert diagnosis: " << '\n';
    in.get();
    std::getline(in, object.diagnosis);
    std::cout << "Insert notes: " << '\n';
    std::getline(in, object.notes);
    std::cout << "Was is successful? [0/1] " << '\n';
    in >> object.successful;
    std::cout << "Insert cost:  " << '\n';
    in >> object.cost;
    return in;
}

std::ostream &operator<<(std::ostream & out, const Treatment & object) {
    out << "*** TREATMENT ***\n";
    object.printAttributes(out);
    return out;
}

std::string Treatment::toString() const {
    return "TREATMENT ID: " + std::to_string(this->id) + "\n" +
    "{DOCTOR ID: " + (this->doctor != nullptr ? std::to_string(this->doctor->getId()) : "0") + "\n" +
    "PATIENT ID: " + (this->patient != nullptr ? std::to_string(this->patient->getId()) : "0") + "}" + "\n" +
    this->diagnosis + " " + std::to_string(this->successful) + " " + std::to_string(this->cost);

}

void Treatment::printAttributes(std::ostream & out) const{
    out << " ID: " << this->id << '\n';
    out << "Patient: " << (this->patient == nullptr ? "unknown" : this->patient->getName()) << '\n';
    out << "Doctor: " << (this->doctor == nullptr ? "unknown" : this->doctor->getName()) << '\n';
    out << "Start date: " << this->startDate << '\n';
    out << "End date: " << this->endDate << '\n';
    out << "Diagnosis: " << this->diagnosis << '\n';
    out << "Notes: " << this->notes << '\n';
    out << "Successful: " << (this->successful ? "Yes" : "No") << '\n';
    out << "Cost:  " << this->cost << '\n';
}

int Treatment::getId() const {
    return this->id;
}

Patient *Treatment::getPatient() const {
    return this->patient;
}

Doctor *Treatment::getDoctor() const {
    return this->doctor;
}

Date Treatment::getStartDate() const {
    return this->startDate;
}

Date Treatment::getEndDate() const {
    return this->endDate;
}

std::string Treatment::getDiagnosis() const {
    return this->diagnosis;
}

std::string Treatment::getNotes() const {
    return this->notes;
}

bool Treatment::getSuccessful() const {
    return this->successful;
}

long long Treatment::getCost() const {
    return this->cost;
}

void Treatment::setDoctor(Doctor *doctor) {
    this->doctor = doctor;
}

void Treatment::setSuccessful(bool successful) {
    this->successful = successful;
}

void Treatment::printCard(std::ostream &out) const{
    auto card = this->asCard();
    for(const auto& line: card.card) {
        out << line << '\n';
    }
}

TreatmentCard Treatment::asCard() const {
    return TreatmentCard(
            this->id,
            "Treatment",
            this->patient->getName(),
            this->doctor->getName(),
            this->startDate,
             this->endDate,
             this->diagnosis,
             this->successful,
             this->cost
            );
}

Treatment::~Treatment() {

}
