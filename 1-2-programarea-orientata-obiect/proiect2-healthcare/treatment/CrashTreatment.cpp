//
// Created by eduarddumitrescul on 3/30/23.
//

#include "CrashTreatment.h"

CrashTreatment::CrashTreatment(Patient *patient, Doctor *doctor, Date startDate, Date endDate, std::string diagnosis,
                               std::string notes, bool successful, long long int firstAidCost,
                               long long int surgeryCost, std::string injury,
                               std::string severity, SurgeonDoctor *surgeon, std::string surgeryName,
                               std::string anesthesiaType, std::string location):
        FirstAidTreatment(patient, doctor, startDate, endDate, diagnosis, notes, successful, firstAidCost, injury, severity),
        SurgeryTreatment(patient, nullptr, startDate, endDate, diagnosis, notes, successful, surgeryCost, surgeon, surgeryName, anesthesiaType),
        Treatment(patient, doctor, startDate, endDate, diagnosis, notes, successful, firstAidCost + surgeryCost) {
    this->location = location;
}

std::istream &operator>>(std::istream & in, CrashTreatment & object) {
    in >> (Treatment&)object;
    ((FirstAidTreatment)object).readAttributes(in);
    ((SurgeryTreatment)object).readAttributes(in);
    object.readAttributes(in);
    return in;
}

std::ostream &operator<<(std::ostream & out, const CrashTreatment & object) {
    out << "*** CRASH TREATMENT ***\n";
    ((Treatment)object).printAttributes(out);
    ((FirstAidTreatment)object).printAttributes(out);
    ((SurgeryTreatment)object).printAttributes(out);
    object.printAttributes(out);
    return out;
}

void CrashTreatment::printAttributes(std::ostream & out) const {
    out << this->location << '\n';
}

void CrashTreatment::readAttributes(std::istream & in) {
    std::cout << "Insert Crash location: ";
    std::getline(in, this->location);
}

TreatmentCard CrashTreatment::asCard() const {
    return TreatmentCard(
            this->id,
            "Crash Treatment",
            (this->patient == nullptr) ? "not chosen" : this->patient->getName(),
            (this->doctor == nullptr) ? "not chosen" : this->doctor->getName(),
            (this->surgeon == nullptr) ? "not chosen" : this->surgeon->getName(),
            this->startDate,
            this->endDate,
            this->diagnosis,
            this->surgeryName,
            this->successful,
            FirstAidTreatment::cost + SurgeryTreatment::cost
            );
}
