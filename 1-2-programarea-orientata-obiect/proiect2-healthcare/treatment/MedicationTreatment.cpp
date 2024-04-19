//
// Created by eduarddumitrescul on 3/30/23.
//

#include "MedicationTreatment.h"

MedicationTreatment::MedicationTreatment(Patient *patient, Doctor *doctor, Date startDate, Date endDate,
                                         std::string diagnosis, std::string notes, bool successful, long long int cost,
                                         std::vector<Medication> medicationList):
Treatment(patient, doctor, startDate, endDate, diagnosis, notes, successful, cost){
    this->medicationList = medicationList;
}

std::istream &operator>>(std::istream & in, MedicationTreatment & object) {
    in >> (Treatment&) object;
    std::cout << "Insert number of Medications: ";
    int nr;
    in >> nr;
    object.medicationList.resize(nr);
    for(int i = 0; i < nr; i ++) {
        in >> object.medicationList[i];
    }
    return in;
}

std::ostream &operator<<(std::ostream & out, const MedicationTreatment & object) {
    out << "*** MEDICATION TREATMENT ***" << '\n';
    ((Treatment)object).printAttributes(out);
    object.printAttributes(out);
    return out;
}

void MedicationTreatment::printAttributes(std::ostream & out) const {
    out << "Number of Medications = " << this->medicationList.size() << '\n';
    for(auto med: this->medicationList) {
        out << med.asString() << '\n';
    }
}
