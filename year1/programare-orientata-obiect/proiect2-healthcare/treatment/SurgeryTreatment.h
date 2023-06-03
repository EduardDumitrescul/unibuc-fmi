//
// Created by eduarddumitrescul on 3/30/23.
//

#ifndef OOP_HEALTHCARE_SURGERYTREATMENT_H
#define OOP_HEALTHCARE_SURGERYTREATMENT_H


#include "Treatment.h"
#include "../people/SurgeonDoctor.h"

class SurgeryTreatment: virtual public Treatment {
protected:
    SurgeonDoctor* surgeon;
    std::string surgeryName;
    std::string anesthesiaType;

public:
    SurgeryTreatment(
            Patient* patient = nullptr,
            Doctor* doctor = nullptr,
            Date startDate = {0, 0, 0},
            Date endDate = {0, 0, 0},
            std::string diagnosis = "base diagnosis",
            std::string notes = "no notes",
            bool successful = false,
            long long cost = 0,
            SurgeonDoctor* surgeon = nullptr,
            std::string surgeryName = "base surgery",
            std::string anesthesiaType = "local"
    );

    friend std::istream& operator >>(std::istream&, SurgeryTreatment&);
    friend std::ostream& operator <<(std::ostream&, const SurgeryTreatment&);

    virtual TreatmentCard asCard() const;
    void printAttributes(std::ostream&) const;

    std::string getSurgeryName() const;
    void setSurgeonDoctor(SurgeonDoctor* surgeon);

    SurgeonDoctor* getSurgeonDoctor() const;

    std::string getAnesthesiaType() const;

    virtual void readAttributes(std::istream&);
};


#endif //OOP_HEALTHCARE_SURGERYTREATMENT_H
