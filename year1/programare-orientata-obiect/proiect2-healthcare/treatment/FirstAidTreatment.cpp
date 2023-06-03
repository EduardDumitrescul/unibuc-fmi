//
// Created by eduarddumitrescul on 3/30/23.
//

#include "FirstAidTreatment.h"

FirstAidTreatment::FirstAidTreatment(Patient *patient, Doctor *doctor, Date startDate, Date endDate,
                                     std::string diagnosis, std::string notes, bool successful, long long int cost,
                                     std::string injury, std::string severity):
        Treatment(patient, doctor, startDate, endDate, diagnosis, notes, successful, cost){
    this->injury = injury;
    this->severity = severity;
}

std::istream &operator>>(std::istream & in, FirstAidTreatment & object) {
    in >> (Treatment&) object;
    object.readAttributes(in);
    return in;
}

std::ostream &operator<<(std::ostream & out, const FirstAidTreatment & object) {
    out << "*** FIRST AID TREATMENT ***\n";
    ((Treatment)object).printAttributes(out);
    object.printAttributes(out);
    return out;
}

void FirstAidTreatment::printAttributes(std::ostream & out) const {
    out << "Injury: " << this->injury << '\n';
    out << "Severity: " << this->severity << '\n';
}

void FirstAidTreatment::readAttributes(std::istream &in) {
    in.get();
    std::cout << "Insert injury: ";
    std::getline(in, this->injury);
    std::cout << "Insert severity: ";
    std::getline(in, this->severity);
}

TreatmentCard FirstAidTreatment::asCard() const {
    return TreatmentCard(
            this->getId(),
            "First Aid",
            (this->patient == nullptr) ? "not chosen" : this->getPatient()->getName(),
            (this->doctor == nullptr) ? "not chosen" : this->getDoctor()->getName(),
            this->getStartDate(),
            this->getEndDate(),
            this->getDiagnosis(),
            this->getSuccessful(),
            this->getCost()
    );
}
