//
// Created by eduarddumitrescul on 3/31/23.
//

#include "Database.h"

int Database::addPatient(Patient object) {
    auto* p = new Patient(object);
    this->patients.push_back(p);
    return p->getId();
}

std::vector<const Patient *> Database::getAllPatients() const {
    std::vector <const Patient*> result;
    for(auto& obj: patients) {
        result.push_back(obj);
    }
    return result;
}

const Patient *Database::getPatient(int id) const {
    for(auto &obj: this->patients) {
        if(obj->getId() == id) {
            return obj;
        }
    }
    return nullptr;
}

void Database::editPatient(int id, const Patient& object) {
    for(auto &ent: this->patients) {
        if(ent->getId() == id)
            *ent = object;
    }
}

void Database::addDoctor(Doctor object) {
    auto* p = new Doctor(object);
    this->doctors.push_back(p);
}

std::vector<const Doctor *> Database::getAllDoctors() const {
    std::vector <const Doctor*> result;
    for(auto obj: doctors) {
        result.push_back(obj);
    }
    return result;
}

const Doctor *Database::getDoctor(int id) const {
    for(auto &obj: this->doctors) {
        if(obj->getId() == id) {
            return obj;
        }
    }
    return nullptr;
}

void Database::editDoctor(int id, const Doctor& object) {
    for(auto &ent: this->doctors) {
        if(ent->getId() == id)
            *ent = object;
    }
}

void Database::addSurgeon(SurgeonDoctor object) {
    auto* p = new SurgeonDoctor(object);
    this->doctors.push_back(p);
}

void Database::addTreatment(Treatment object) {
    auto* p = new Treatment(object);
    this->treatmentList.push_back(p);
}

void Database::addMedicationTreatment(MedicationTreatment object) {
    auto* p = new MedicationTreatment(object);
    this->treatmentList.push_back(p);
}

void Database::addFirstAidTreatment(FirstAidTreatment object) {
    auto* p = new FirstAidTreatment(object);
    this->treatmentList.push_back(p);
}

void Database::addSurgeryTreatment(SurgeryTreatment object) {
    auto* p = new SurgeryTreatment(object);
    this->treatmentList.push_back(p);
}

void Database::addCrashTreatment(CrashTreatment object) {
    auto* p = new CrashTreatment(object);
    this->treatmentList.push_back(p);
}

std::vector<const Treatment *> Database::getAllTreatments() const {
    std::vector <const Treatment*> temp;
    for(auto& p: this->treatmentList) {
        temp.push_back(p);
    }
    return temp;
}

const Treatment *Database::getTreatment(int id) const {
    for(auto &p: this->treatmentList) {
        if(p->getId() == id) {
            return p;
        }
    }
    return nullptr;
}

Database::~Database() {
    for(auto& it: this->treatmentList) {
        if(it != nullptr) {
            delete it;
            it = nullptr;
        }

    }
    for(auto& it: this->doctors) {
        if(it != nullptr) {
            delete it;
            it = nullptr;
        }
    }
    for(auto& it: this->patients) {
        if (it != nullptr) {
            delete it;
            it = nullptr;
        }
    }
}
