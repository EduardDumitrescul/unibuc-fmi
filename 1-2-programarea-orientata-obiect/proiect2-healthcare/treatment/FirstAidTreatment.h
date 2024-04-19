//
// Created by eduarddumitrescul on 3/30/23.
//

#ifndef OOP_HEALTHCARE_FIRSTAIDTREATMENT_H
#define OOP_HEALTHCARE_FIRSTAIDTREATMENT_H


#include "Treatment.h"

class FirstAidTreatment: virtual public Treatment{
protected:
    std::string injury;
    std::string severity;

public:
    FirstAidTreatment(
            Patient* patient = nullptr,
            Doctor* doctor = nullptr,
            Date startDate = {0, 0, 0},
            Date endDate = {0, 0, 0},
            std::string diagnosis = "base diagnosis",
            std::string notes = "no notes",
            bool successful = false,
            long long cost = 0,
            std::string injury = "base injury",
            std::string severity = "medium"
    );

    virtual TreatmentCard asCard() const;

    friend std::istream& operator >>(std::istream&, FirstAidTreatment&);
    friend std::ostream& operator <<(std::ostream&, const FirstAidTreatment&);

    void printAttributes(std::ostream&) const;
    void readAttributes(std::istream&);
};


#endif //OOP_HEALTHCARE_FIRSTAIDTREATMENT_H
