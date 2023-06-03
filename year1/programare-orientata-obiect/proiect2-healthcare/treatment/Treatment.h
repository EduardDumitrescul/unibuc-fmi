//
// Created by eduarddumitrescul on 3/30/23.
//

#ifndef OOP_HEALTHCARE_TREATMENT_H
#define OOP_HEALTHCARE_TREATMENT_H


#include <string>
#include "../people/Patient.h"
#include "../people/Doctor.h"
#include "../Date.h"
#include "../DrawingUtil.h"

class Treatment {
protected:
    static int idCount;
    const int id;

    Patient* patient;
    Doctor* doctor;

    Date startDate;
    Date endDate;

    std::string diagnosis;
    std::string notes;

    bool successful;
    long long cost;

public:
    Treatment(
            Patient* patient = nullptr,
            Doctor* doctor = nullptr,
            Date startDate = {0, 0, 0},
            Date endDate = {0, 0, 0},
            std::string diagnosis = "base diagnosis",
            std::string notes = "no notes",
            bool successful = false,
            long long cost = 0
        );
    Treatment(const Treatment&);

    Treatment& operator=(const Treatment&);

    friend std::istream& operator >> (std::istream&, Treatment&);
    friend std::ostream& operator << (std::ostream&, const Treatment&);

    std::string toString() const;
    virtual TreatmentCard asCard() const;
    void printCard(std::ostream&) const;


    virtual void printAttributes(std::ostream&) const;

    void setDoctor(Doctor* doctor);
    void setSuccessful(bool successful);

    int getId() const;
    Patient* getPatient() const;
    Doctor* getDoctor() const;
    Date getStartDate() const;
    Date getEndDate() const;
    std::string getDiagnosis() const;
    std::string getNotes() const;
    bool getSuccessful() const;
    long long getCost() const;

    virtual ~Treatment();
};


#endif //OOP_HEALTHCARE_TREATMENT_H
