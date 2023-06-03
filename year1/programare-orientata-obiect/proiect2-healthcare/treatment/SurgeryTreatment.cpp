//
// Created by eduarddumitrescul on 3/30/23.
//

#include "SurgeryTreatment.h"

SurgeryTreatment::SurgeryTreatment(Patient *patient, Doctor *doctor, Date startDate, Date endDate,
                                   std::string diagnosis, std::string notes, bool successful, long long int cost,
                                   SurgeonDoctor *surgeon,
                                   std::string surgeryName, std::string anesthesiaType):
        Treatment(patient, doctor, startDate, endDate, diagnosis, notes, successful, cost){
    this->surgeon = surgeon;
    this->surgeryName = surgeryName;
    this->anesthesiaType = anesthesiaType;
}

std::istream &operator>>(std::istream & in, SurgeryTreatment & object) {
    in >> (Treatment&) object;
    in.get();
    object.readAttributes(in);
    return in;
}

std::ostream &operator<<(std::ostream & out, const SurgeryTreatment & object) {
    out << "*** SURGERY TREATMENT ***\n";
    ((Treatment)object).printAttributes(out);
    object.printAttributes(out);
    return out;
}

void SurgeryTreatment::printAttributes(std::ostream & out) const {
    out << "Surgeon: " << (this->surgeon == nullptr ? "unkown" : this->surgeon->getName()) << '\n';
    out << "Surgery performed: " << this->surgeryName << '\n';
    out << "Anesthesia type: " << this->anesthesiaType << '\n';
}

void SurgeryTreatment::readAttributes(std::istream & in) {
    std::cout << "Insert surgery name: ";
    std::getline(in, this->surgeryName);
    std::cout << "Insert anesthesia type: ";
    std::getline(in, this->anesthesiaType);
}

std::string SurgeryTreatment::getSurgeryName() const {
    return this->surgeryName;
}

void SurgeryTreatment::setSurgeonDoctor(SurgeonDoctor *surgeon) {
    this->surgeon = surgeon;
}

SurgeonDoctor *SurgeryTreatment::getSurgeonDoctor() const {
    return this->surgeon;
}

std::string SurgeryTreatment::getAnesthesiaType() const {
    return this->anesthesiaType;
}

TreatmentCard SurgeryTreatment::asCard() const {
    return TreatmentCard(
            this->getId(),
            "Surgery",
            (this->patient == nullptr) ? "not chosen" : this->getPatient()->getName(),
            (this->surgeon == nullptr) ? "not chosen" : this->surgeon->getName(),
            this->getStartDate(),
            this->getEndDate(),
            this->getDiagnosis(),
            this->getSurgeryName(),
            this->getAnesthesiaType(),
            this->getSuccessful(),
            this->getCost()
    );
}
