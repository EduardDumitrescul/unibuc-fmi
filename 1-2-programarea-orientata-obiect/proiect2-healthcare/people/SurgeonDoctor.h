//
// Created by eduarddumitrescul on 3/30/23.
//

#ifndef OOP_HEALTHCARE_SURGEONDOCTOR_H
#define OOP_HEALTHCARE_SURGEONDOCTOR_H


#include "Doctor.h"

class SurgeonDoctor: public Doctor {
protected:
    std::string specialty;
    int successfulSurgeries;
    int failedSurgeries;

public:
    SurgeonDoctor(
            std::string firstname = "Firstname",
            std::string lastname = "Lastname",
            int experience = 0,
            int salary = 0,
            std::string specialty = "general surgery",
            int successfulSurgeries = 0,
            int failedSurgeires = 0);
    SurgeonDoctor(const SurgeonDoctor& object);
    SurgeonDoctor& operator =(const SurgeonDoctor&);

    friend std::istream& operator >>(std::istream&, SurgeonDoctor&);
    friend std::ostream& operator <<(std::ostream&, const SurgeonDoctor&);

    void printCard(std::ostream& out) const;
    std::string shortString() const override;

    void setSpecialty(std::string);
    void setSuccessfulSurgeries(int);
    void setFailedSurgeries(int);

    void success();
    void fail();
};


#endif //OOP_HEALTHCARE_SURGEONDOCTOR_H
