//
// Created by eduarddumitrescul on 3/30/23.
//

#ifndef OOP_HEALTHCARE_MEDICATIONTREATMENT_H
#define OOP_HEALTHCARE_MEDICATIONTREATMENT_H


#include <vector>
#include "Treatment.h"
#include "../Medication.h"

class MedicationTreatment: virtual public Treatment {
    std::vector <Medication> medicationList;

public:
    MedicationTreatment(
            Patient* patient = nullptr,
            Doctor* doctor = nullptr,
            Date startDate = {0, 0, 0},
            Date endDate = {0, 0, 0},
            std::string diagnosis = "base diagnosis",
            std::string notes = "no notes",
            bool successful = false,
            long long cost = 0,
            std::vector <Medication> medicationList = {}
    );

    friend std::istream& operator >>(std::istream&, MedicationTreatment&);
    friend std::ostream& operator <<(std::ostream&, const MedicationTreatment&);

    void printAttributes(std::ostream&) const;
};


#endif //OOP_HEALTHCARE_MEDICATIONTREATMENT_H
