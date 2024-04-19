//
// Created by eduarddumitrescul on 3/31/23.
//

#ifndef OOP_HEALTHCARE_DRAWINGUTIL_H
#define OOP_HEALTHCARE_DRAWINGUTIL_H

#include <string>
#include <vector>
#include "Date.h"

struct PersonCard {
    int titlePos = 24;
    int imgPos = 18;
    int idPos = 7;
    std::vector <std::string> card = {
            "******************************************************\n",
            "*      /. .\\                                         *\n",
            "*      \\ - /                                         *\n",
            "*   ____| |____                                      *\n",
            "*  /           \\                                     *\n",
            "* / /|_______|\\ \\                                    *\n",
            "******************************************************\n",
    };

    PersonCard(int id, std::string title, std::string name, char sex, int birthyear) {
        title = " " + title + " ";
        name = "Name: " + name;
        card[0].replace(titlePos, title.size(), title);
        card[1].replace(imgPos, name.size(), name);
        std::string s = "Sex: ";
        s += sex;
        card[2].replace(imgPos, s.size(), s);
        std::string birth = "Birthyear: " + std::to_string(birthyear);
        card[3].replace(imgPos, birth.size(), birth);
        std::string ids = std::to_string(id);
        card[4].replace(idPos, ids.size(), ids);
    }

    PersonCard(int id = 0, std::string title="", std::string name = "Firstname Lastname", int experience = 0, int salary = 0) {
        title = " " + title + " ";
        name = "Name: " + name;
        std::string exp = "Experience: " + std::to_string(experience) + " year(s)";
        std::string sal = "Salary: " + std::to_string(salary) + "$";
        card[0].replace(titlePos, title.size(), title);
        card[1].replace(imgPos, name.size(), name);
        card[2].replace(imgPos, exp.size(), exp);
        card[3].replace(imgPos, sal.size(), sal);
        std::string ids = std::to_string(id);
        card[4].replace(idPos, ids.size(), ids);
    }

    PersonCard(int id, std::string title, std::string name, int experience, int salary, std::string specialty, int successes, int fails) {
        title = " " + title + " ";
        card[0].replace(titlePos, title.size(), title);
        name = "Name: " + name;
        card[1].replace(imgPos, name.size(), name);
        std::string spec = "Specialty: " + specialty;
        card[2].replace(imgPos, spec.size(), spec);
        std::string exp = "Experience: " + std::to_string(experience) + " year(s)";
        card[3].replace(imgPos, exp.size(), exp);
        std::string sal = "Salary: " + std::to_string(salary) + "$";
        card[4].replace(imgPos, sal.size(), sal);
        std::string ids = std::to_string(id);
        card[4].replace(idPos, ids.size(), ids);
        std::string rate = "Surgeries: " + std::to_string(successes) + " Succeeded / " + std::to_string(fails) + " Failed";
        card[5].replace(imgPos, rate.size(), rate);
    }
};

struct TreatmentCard {
    int titlePos = 20;
    int imgPos = 18;
    int idPos = 7;
    std::vector <std::string> card = {
            "*******************************************************",
            "*                                                     *",
            "*     / /   / /                                       *",
            "*    / /_ _/ /                                        *",
            "*   /  _ _  /                                         *",
            "*  / /   / /                                          *",
            "* /_/   /_/                                           *",
            "*                                                     *",
            "*                                                     *",
            "*******************************************************",
    };

    TreatmentCard(int id, std::string title, std::string patientName, std::string doctorName,
                  Date startDate, Date endDate, std::string diagnosis, bool successful, long long cost) {
        title = " " + title + "-" + std::to_string(id) + " ";
        card[0].replace(titlePos, title.size(), title);
        patientName = "Patient: " + patientName;
        card[1].replace(imgPos, patientName.size(), patientName);
        doctorName = "Doctor: " + doctorName;
        card[2].replace(imgPos, doctorName.size(), doctorName);
        std::string date = "Date: " + startDate.asString() + " -> " + endDate.asString();
        card[3].replace(imgPos, date.size(), date);
        diagnosis = "Diagnosis: " + diagnosis;
        card[4].replace(imgPos, diagnosis.size(), diagnosis);
        std::string success = "Successful: ";
        (successful ? success += "YES" : success += "NO");
        card[5].replace(imgPos, success.size(), success);
        std::string price = "Cost: " + std::to_string(cost);
        card[6].replace(imgPos, price.size(), price);
    }

    TreatmentCard(int id, std::string title, std::string patientName, std::string surgeonName,
                  Date startDate, Date endDate, std::string diagnosis, std::string surgeryName, std::string anesthesiaType, bool successful, long long cost) {
        title = " " + title + "-" + std::to_string(id) + " ";
        card[0].replace(titlePos, title.size(), title);
        patientName = "Patient: " + patientName;
        card[1].replace(imgPos, patientName.size(), patientName);
        surgeonName = "Surgeon: " + surgeonName;
        card[2].replace(imgPos, surgeonName.size(), surgeonName);
        std::string date = "Date: " + startDate.asString() + " -> " + endDate.asString();
        card[3].replace(imgPos, date.size(), date);
        diagnosis = "Diagnosis: " + diagnosis;
        card[4].replace(imgPos, diagnosis.size(), diagnosis);
        std::string success = "Successful: ";
        surgeryName = "Surgery: " + surgeryName;
        card[5].replace(imgPos, surgeryName.size(), surgeryName);
        anesthesiaType = "Anesthesia Type: " + anesthesiaType;
        card[6].replace(imgPos, anesthesiaType.size(), anesthesiaType);
        (successful ? success += "YES" : success += "NO");
        card[7].replace(imgPos, success.size(), success);
        std::string price = "Cost: " + std::to_string(cost);
        card[8].replace(imgPos, price.size(), price);
    }

    TreatmentCard(int id, std::string title, std::string patientName, std::string doctorName, std::string surgeonName,
                  Date startDate, Date endDate, std::string diagnosis, std::string surgery, bool successful, long long cost) {
        title = " " + title + "-" + std::to_string(id) + " ";
        card[0].replace(titlePos, title.size(), title);
        patientName = "Patient: " + patientName;
        card[1].replace(imgPos, patientName.size(), patientName);
        doctorName = "Doctor: " + doctorName;
        card[2].replace(imgPos, doctorName.size(), doctorName);
        surgeonName = "Surgeon: " + surgeonName;
        card[3].replace(imgPos, surgeonName.size(), surgeonName);
        std::string date = "Date: " + startDate.asString() + " -> " + endDate.asString();
        card[4].replace(imgPos, date.size(), date);
        surgery = "Surgery: " + surgery;
        card[5].replace(imgPos, surgery.size(), surgery);
        diagnosis = "Diagnosis: " + diagnosis;
        card[6].replace(imgPos, diagnosis.size(), diagnosis);
        std::string success = "Successful: ";
        (successful ? success += "YES" : success += "NO");
        card[7].replace(imgPos, success.size(), success);
        std::string price = "Cost: " + std::to_string(cost);
        card[8].replace(imgPos, price.size(), price);
    }
};

#endif //OOP_HEALTHCARE_DRAWINGUTIL_H
