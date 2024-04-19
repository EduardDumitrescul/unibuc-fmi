//
// Created by eduarddumitrescul on 3/30/23.
//

#ifndef OOP_HEALTHCARE_CRASHTREATMENT_H
#define OOP_HEALTHCARE_CRASHTREATMENT_H


#include "FirstAidTreatment.h"
#include "SurgeryTreatment.h"

class CrashTreatment: public FirstAidTreatment, public SurgeryTreatment{
    std::string location;

public:
    CrashTreatment(
            Patient* patient = nullptr,
            Doctor* doctor = nullptr,
            Date startDate = {0, 0, 0},
            Date endDate = {0, 0, 0},
            std::string diagnosis = "base diagnosis",
            std::string notes = "no notes",
            bool successful = false,
            long long firstAidCost = 0,
            long long surgeryCost = 0,
            std::string injury = "base injury",
            std::string severity = "normal",
            SurgeonDoctor* surgeon = nullptr,
            std::string surgeryName = "base surgery",
            std::string anesthesiaType = "local",
            std::string location = "Bucharest"
    );

    friend std::istream& operator >>(std::istream&, CrashTreatment&);
    friend std::ostream& operator <<(std::ostream&, const CrashTreatment&);

    TreatmentCard asCard() const;

    void printAttributes(std::ostream&) const;
    void readAttributes (std::istream&);
};


#endif //OOP_HEALTHCARE_CRASHTREATMENT_H
