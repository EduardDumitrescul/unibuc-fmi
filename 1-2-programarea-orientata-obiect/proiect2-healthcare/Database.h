//
// Created by eduarddumitrescul on 3/31/23.
//

#ifndef OOP_HEALTHCARE_DATABASE_H
#define OOP_HEALTHCARE_DATABASE_H


#include <vector>
#include <deque>
#include "people/Patient.h"
#include "people/Doctor.h"
#include "people/SurgeonDoctor.h"
#include "treatment/Treatment.h"
#include "treatment/MedicationTreatment.h"
#include "treatment/FirstAidTreatment.h"
#include "treatment/SurgeryTreatment.h"
#include "treatment/CrashTreatment.h"

class Database {
    std::deque <Patient*> patients;
    std::deque <Doctor*> doctors;

    std::deque <Treatment*> treatmentList;

public:
    int addPatient(Patient object);
    const Patient* getPatient(int id) const;
    std::vector <const Patient*> getAllPatients() const;
    void editPatient(int id, const Patient& object);


    void addDoctor(Doctor object);
    void addSurgeon(SurgeonDoctor object);
    const Doctor* getDoctor(int id) const;
    std::vector <const Doctor*> getAllDoctors() const;
    void editDoctor(int id, const Doctor& object);
    void editDoctor(int id, const SurgeonDoctor& object) {
        for(auto& ent: this->doctors) {
            if(ent->getId() == id)
                *(dynamic_cast<SurgeonDoctor*>(ent)) = object;
        }
    }

    void addTreatment(Treatment object);
    void addMedicationTreatment(MedicationTreatment object);
    void addFirstAidTreatment(FirstAidTreatment object);
    void addSurgeryTreatment(SurgeryTreatment object);
    void addCrashTreatment(CrashTreatment object);

    std::vector <const Treatment*> getAllTreatments() const;
    const Treatment* getTreatment(int id) const;


    ~Database();

};


#endif //OOP_HEALTHCARE_DATABASE_H
