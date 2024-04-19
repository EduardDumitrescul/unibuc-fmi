//
// Created by eduarddumitrescul on 3/31/23.
//

#ifndef OOP_HEALTHCARE_DEMO_H
#define OOP_HEALTHCARE_DEMO_H


#include "Database.h"
#include "GameScreen.h"

class Demo {
    Database sandboxDatabase;
    Database database;
    GameScreen* screen;
    std::vector <std::string> crashMessages;
    std::vector <std::string> injuryMessage;
    std::vector <const Doctor*> doctors;

    void printAllPatients() const;
    void printAllDoctors() const;
    void printGamePatients() const;
    void printGameDoctors() const;
    void printAllGameTreatments() const;
    void printAllTreatments() const;

    void solveFirstAidTreatment(const Patient *, int);
    void solveSurgeryTreatment(const Patient *, int);
    void solveCrashTreatment(const Patient *, int);

    static Doctor randomDoctor();
    static SurgeonDoctor randomSurgeon();
    static Patient randomPatient();
    static FirstAidTreatment randomFirstAidTreatment(Patient*, std::string);
    static SurgeryTreatment randomSurgeryTreatment(Patient*, std::string);
    static CrashTreatment randomCrashTreatment(Patient*, std::string);
    static void sleep(int);

public:

    Demo() {
        this->database.addDoctor(randomDoctor());
        this->database.addDoctor(randomDoctor());
        this->database.addDoctor(randomDoctor());
        this->database.addSurgeon(randomSurgeon());
        this->database.addSurgeon(randomSurgeon());
    }

    void run();
    void sandbox();
    void play();

    void patientScreen(std::string);
    void patientAddScreen(std::string);
    void patientEditScreen(std::string);

    void doctorScreen(std::string);
    void doctorAddScreen(std::string);
    void doctorEditScreen(std::string);

    void treatmentScreen(std::string);
    void treatmentAddScreen(std::string);
    void treatmentEditScreen(std::string);
};


#endif //OOP_HEALTHCARE_DEMO_H
