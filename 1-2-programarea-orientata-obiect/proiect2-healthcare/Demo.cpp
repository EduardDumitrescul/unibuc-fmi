//
// Created by eduarddumitrescul on 3/31/23.
//

#include <chrono>
#include <thread>
#include <utility>
#include "Demo.h"
#include "Data.h"

void Demo::run() {
    bool running = true;
    std::system("clear");
    while(running) {
        std::cout << "Welcome to Ethereal Health Center!\n\n";
        std::cout << "[0] - Exit\n";
        std::cout << "[1] - Sandbox\n";
        std::cout << "[2] - Start playing\n";

        int command;
        std::cin >> command;
        std::system("clear");
        switch(command) {
            case 0: {
                running = false;
                break;
            }
            case 1: {
                this->sandbox();
                break;
            }
            case 2: {
                this->play();
                break;
            }
            default: {
                break;
            }
        }
    }
}

void Demo::play() {
    std::system("clear");
    this->screen = new GameScreen(160, 24);
    bool running = true;
    this->doctors = this->database.getAllDoctors();
    this->screen->setDoctors(doctors);

    this->crashMessages.push_back(PredefinedData::getCrashMessage());
    this->injuryMessage.push_back(PredefinedData::getNote());

    while(running) {
        std::system("clear");

        std::vector <std::string> temp = this->crashMessages;
        temp.insert(temp.end(), this->injuryMessage.begin(), this->injuryMessage.end());

        if(temp.empty()) {
            this->printAllGameTreatments();
            running = false;
            std::cout << "[0] to exit play mode";
            int command;
            std::cin >> command;
            break;
        }

        this->screen->setEvents(temp);
        this->screen->setDoctors(doctors);

        screen->show(std::cout);

        std::cout << "[0] - exit\n";
        std::cout << "[1]->[" << temp.size() << "] - choose case\n";
        int command;
        std::cin >> command;

        if(command == 0) {
            running = false;
            continue;
        }
        if(1 <= command and command <= this->crashMessages.size()) {
            int count = PredefinedData::randomInt(1, 4);
            this->crashMessages.erase(this->crashMessages.begin() + command - 1);
            while(count--) {
                this->injuryMessage.push_back(PredefinedData::getNote());
            }
            continue;
        }

        if(this->crashMessages.size() < command and command <= this->crashMessages.size() + this->injuryMessage.size()) {
            int index = command - this->crashMessages.size();


            Patient patient = Demo::randomPatient();
            int patientId = this->database.addPatient(patient);
            auto *p = this->database.getPatient(patientId);

            int treatmentType = PredefinedData::randomInt(0, 3);

            if(treatmentType == 0) /*First Aid */ {
                this->solveFirstAidTreatment(p, index);
            }
            else if(treatmentType == 1) /* Surgery */ {
                this->solveSurgeryTreatment(p, index);
            }
            else if(treatmentType == 2) /* Crash */ {
                this->solveCrashTreatment(p, index);
            }
            this->injuryMessage.erase(this->injuryMessage.begin() + index - 1);

            continue;
        }

    }
}

void Demo::sandbox() {
    bool running = true;
    std::string path = "Sandbox";
    while(running) {
        std::system("clear");

        std::cout << "*** " + path + " ***\n";
        std::cout << "[0] - Back\n";
        std::cout << "[1] - Patient Screen \n";
        std::cout << "[2] - Doctor Screen \n";
        // TODO std::cout << "[3] - Treatment Screen \n";

        int command;
        std::cin >> command;

        switch (command) {
            case 0: {
                running = false;
                break;
            }
            case 1: {
                this->patientScreen(path);
                break;
            }
            case 2: {
                this->doctorScreen(path);
                break;
            }
            // TODO
//            case 3: {
//                this->treatmentScreen(path);
//            }
            default: {
                std::string s;
                std::getline(std::cin, s);
                std::cout << "Invalid Command!\n";
                break;
            }
        }
    }
}

void Demo::patientScreen(std::string path) {
    bool running = true;
    path = path + " -> Patient Screen";
    std::system("clear");
    while(running) {
        std::cout << "*** " + path + " ***\n";
        std::cout << "[0] - Back\n";
        std::cout << "[1] - See all Patients\n";
        std::cout << "[2] - Add Patient\n";
        std::cout << "[3] - Edit Patient\n";

        int command;
        std::cin >> command;
        std::system("clear");
        switch (command) {
            case 0: {
                running = false;
                break;
            }
            case 1: {
                this->printAllPatients();
                break;
            }
            case 2: {
                this->patientAddScreen(path);
                break;
            }
            case 3: {
                this->patientEditScreen(path);
                break;
            }
            default: {
                std::string s;
                std::getline(std::cin, s);
                std::cout << "Invalid Command!\n";
                break;
            }
        }
    }
    std::system("clear");
}

void Demo::patientAddScreen(std::string path) {
    path = path + " -> Add Patient";
    std::cout << "*** " + path + " ***\n";
    std::cout << "*** Please insert Patient info ***\n\n";
    Patient p;
    std::cin >> p;
    sandboxDatabase.addPatient(p);
    std::system("clear");
}

void Demo::patientEditScreen(std::string path) {
    path = path + " -> Edit Patient";
    system("clear");
    this->printAllPatients();

    bool running = true;
    std::cout << "ID: ";
    int id;
    std::cin >> id;

    Patient* p = const_cast<Patient *>(this->sandboxDatabase.getPatient(id));
    if(p == nullptr) {
        std::cout << "ID not found\n";
        Demo::sleep(1);
        return;
    }
    Patient current(*p);

    system("clear");
    while(running) {
        std::cout << "*** " + path + " ***\n";

        current.printCard(std::cout);

        int command;
        std::cout << "[0] - back\n";
        std::cout << "[1] - edit firstname\n";
        std::cout << "[2] - edit lastname\n";
        std::cout << "[3] - edit birthyear\n";
        std::cout << "[8] - cancel\n";
        std::cout << "[9] - save\n";

        std::cin >> command;
        switch(command) {
            case 0: {
                running = false;
                break;
            }
            case 1: {
                std::cin.get();
                std::string s;
                std::getline(std::cin, s);
                current.setFirstname(s);
                break;
            }
            case 2: {
                std::cin.get();
                std::string s;
                std::getline(std::cin, s);
                current.setLastname(s);
                break;
            }
            case 3: {
                int val;
                std::cin >> val;
                current.setBirthyear(val);
                break;
            }

            case 8: {
                running = false;
                break;
            }
            case 9: {
                this->sandboxDatabase.editPatient(id, current);
                running = false;
                break;
            }
            default: {
                std::string s;
                std::getline(std::cin, s);
                break;
            }
        }
    }
    std::system("clear");
}

void Demo::doctorScreen(std::string path) {
    std::system("clear");
    bool running = true;
    path = path + " -> Doctor Screen";
    while(running) {


        std::cout << "*** " + path + " ***\n";
        std::cout << "[0] - Back\n";
        std::cout << "[1] - See all Doctors\n";
        std::cout << "[2] - Add Doctor\n";
        std::cout << "[3] - Edit Doctor\n";

        int command;
        std::cin >> command;
        std::system("clear");
        switch (command) {
            case 0: {
                running = false;
                break;
            }
            case 1: {
                this->printAllDoctors();
                break;
            }
            case 2: {
                this->doctorAddScreen(path);
                break;
            }
            case 3: {
                doctorEditScreen(path);
                break;
            }
            default: {
                std::string s;
                std::getline(std::cin, s);
                std::cout << "Invalid Command!\n";
                break;
            }
        }
    }
    std::system("clear");
}

void Demo::doctorAddScreen(std::string path) {
    bool running = true;
    path = path + " -> Add Doctor";
    std::system("clear");
    while(running) {
        std::cout << "*** " + path + " ***\n";
        std::cout << "[0] - back\n";
        std::cout << "[1] - insert doctor\n";
        std::cout << "[2] - insert surgeon\n";

        int command;
        std::cin >> command;
        std::system("clear");
        switch(command) {
            case 0: {
                running = false;
                break;
            }
            case 1: {
                system("clear");
                std::cout << "*** Please insert Doctor info ***\n\n";
                Doctor d;
                std::cin >> d;
                sandboxDatabase.addDoctor(d);
                break;
            }
            case 2: {
                system("clear");
                std::cout << "*** Please insert Surgeon info ***\n\n";
                SurgeonDoctor s;
                std::cin >> s;
                sandboxDatabase.addSurgeon(s);
                break;
            }
            default: {
                std::string s;
                std::getline(std::cin, s);
                break;
            }
        }
    }
    std::system("clear");
}

void Demo::doctorEditScreen(std::string path) {

    system("clear");
    this->printAllDoctors();

    bool running = true;
    std::cout << "ID: ";
    int id;
    std::cin >> id;

    const Doctor* p = this->sandboxDatabase.getDoctor(id);

    if(p == nullptr) {
        std::cout << "ID not found!\n";
        Demo::sleep(2);
        return;
    }

    Doctor *current;
    bool isSurgeon = false;
    if(dynamic_cast <const SurgeonDoctor *> (p) != nullptr) {
        current = new SurgeonDoctor(*dynamic_cast <const SurgeonDoctor *> (p));
        isSurgeon = true;
    }
    else {
        current = new Doctor(*p);
    }
    path = path + " -> Edit Doctor";
    while(running) {
        std::cout << "*** " + path + " ***\n";

        p->printCard(std::cout);

        int command;
        std::cout << "[0] - back\n";
        std::cout << "[1] - edit firstname\n";
        std::cout << "[2] - edit lastname\n";
        std::cout << "[3] - edit experience\n";
        std::cout << "[4] - edit salary\n";

        if(dynamic_cast <const SurgeonDoctor *> (p) != nullptr) {
            std::cout << "[5] - edit specialty\n";
            std::cout << "[6] - edit successful surgeries\n";
            std::cout << "[7] - edit failed surgeries\n";
        }
        std::cout << "[8] - cancel\n";
        std::cout << "[9] - save\n";

        std::cin >> command;
        switch(command) {
            case 0: {
                running = false;
                break;
            }
            case 1: {
                std::cin.get();
                std::string s;
                std::getline(std::cin, s);
                current->setFirstname(s);
                break;
            }
            case 2: {
                std::cin.get();
                std::string s;
                std::getline(std::cin, s);
                current->setLastname(s);
                break;
            }
            case 3: {
                int val;
                std::cin >> val;
                current->setExperience(val);
                break;
            }
            case 4: {
                int val;
                std::cin >> val;
                current->setSalary(val);
                break;
            }
            case 5: {
                if(isSurgeon) {
                    std::cin.get();
                    std::string s;
                    std::getline(std::cin, s);
                    (dynamic_cast <SurgeonDoctor *> (current))->setSpecialty(s);
                }
                break;
            }
            case 6: {
                if(isSurgeon) {
                    int val;
                    std::cin >> val;
                    (dynamic_cast <SurgeonDoctor *> (current))->setSuccessfulSurgeries(val);
                }
                break;
            }
            case 7: {
                if(isSurgeon) {
                    int val;
                    std::cin >> val;
                    (dynamic_cast <SurgeonDoctor *> (current))->setFailedSurgeries(val);
                }
                break;
            }
            case 8: {
                running = false;
                break;
            }
            case 9: {
                if(isSurgeon) {
                    this->sandboxDatabase.editDoctor(id, *dynamic_cast <SurgeonDoctor *> (current));
                }
                else {
                    this->sandboxDatabase.editDoctor(id, *current);
                }
                running = false;
                break;
            }
            default: {
                std::string s;
                std::getline(std::cin, s);
                break;
            }
        }
    }

    if(current != nullptr) {
        delete current;
        current = nullptr;
    }
    std::system("clear");
}

void Demo::treatmentScreen(std::string path) {
    path = path + " -> Treatment Screen";
    bool running = true;
    while(running) {
        std::system("clear");
        std::cout << "*** " + path + " ***\n";
        std::cout << "[0] - Back\n";

        int command;
        std::cin >> command;

        switch (command) {
            case 0: {
                running = false;
                break;
            }
            default: {
                std::string s;
                std::getline(std::cin, s);
                std::cout << "Invalid Command!";
                break;
            }
        }
    }
}

void Demo::printAllPatients() const {
    for(auto& ent: this->sandboxDatabase.getAllPatients()) {
        ent->printCard(std::cout);
    }
}

void Demo::printAllDoctors() const {
    for(auto& ent: this->sandboxDatabase.getAllDoctors()) {
        ent->printCard(std::cout);
    }
}

void Demo::printGamePatients() const {
    for(auto& ent: this->database.getAllPatients()) {
        ent->printCard(std::cout);
    }
}

void Demo::printGameDoctors() const {
    for(auto& ent: this->database.getAllDoctors()) {
        ent->printCard(std::cout);
    }
}

Doctor Demo::randomDoctor() {
    std::string lastname = PredefinedData::getLastname();
    std::pair < std::string, char> firstnameSex = PredefinedData::getFirstname();
    Doctor doctor(
            firstnameSex.first,
            PredefinedData::getLastname(),
            PredefinedData::randomInt(5, 32),
            PredefinedData::randomInt(100, 200) * 100
    );
    return doctor;
}

SurgeonDoctor Demo::randomSurgeon() {
    std::string lastname = PredefinedData::getLastname();
    std::pair < std::string, char> firstnameSex = PredefinedData::getFirstname();
    SurgeonDoctor surgeon(
            firstnameSex.first,
            PredefinedData::getLastname(),
            PredefinedData::randomInt(5, 32),
            PredefinedData::randomInt(100, 200) * 100,
            PredefinedData::getSpecialty(),
            0,
            0
    );
    return surgeon;
}

FirstAidTreatment Demo::randomFirstAidTreatment(Patient* patient, std::string notes) {
    FirstAidTreatment treatment(
            patient,
            nullptr,
            {PredefinedData::randomInt(2015, 2023), PredefinedData::randomInt(1, 13), PredefinedData::randomInt(1, 29)},
            {0, 0, 0},
            PredefinedData::getTreatment(PredefinedData::FIRST_AID),
            std::move(notes),
            false,
            PredefinedData::randomInt(5, 101) * 100,
            "injury",
            "severity"
            );
    return treatment;
}

Patient Demo::randomPatient() {
    std::pair <std::string, char> fsex = PredefinedData::getFirstname();
    return Patient(
            fsex.first,
            PredefinedData::getLastname(),
            fsex.second,
            PredefinedData::randomInt(1960, 2004)
            );
}

void Demo::sleep(int seconds) {
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

SurgeryTreatment Demo::randomSurgeryTreatment(Patient *patient, std::string notes) {
    SurgeryTreatment treatment(
            patient,
            nullptr,
            {PredefinedData::randomInt(2015, 2023), PredefinedData::randomInt(1, 13), PredefinedData::randomInt(1, 29)},
            {0, 0, 0},
            PredefinedData::getTreatment(PredefinedData::FIRST_AID),
            std::move(notes),
            false,
            PredefinedData::randomInt(50, 1001) * 100,
            nullptr
    );
    return treatment;
}

CrashTreatment Demo::randomCrashTreatment(Patient *patient, std::string notes) {
    return CrashTreatment(
            patient,
            nullptr,
            {PredefinedData::randomInt(2015, 2023), PredefinedData::randomInt(1, 13), PredefinedData::randomInt(1, 29)},
            {0, 0, 0},
            PredefinedData::getTreatment(PredefinedData::SURGERY),
            notes,
            false,
            PredefinedData::randomInt(5, 101) * 100,
            PredefinedData::randomInt(50, 1001) * 100,
            "injury",
            "severity",
            nullptr,
            "surgery",
            "general",
            "location"
            );
}

void Demo::solveFirstAidTreatment(const Patient *p, int index) {
    FirstAidTreatment treatment = Demo::randomFirstAidTreatment(const_cast<Patient *>(p), injuryMessage[index - 1]);

    this->screen->setTreatmentCard(treatment.asCard());

    std::system("clear");
    this->screen->show(std::cout);
    std::cout << "Choose Doctor to take care of the Patient (1 -> " << this->doctors.size() << "): ";
    int doctorIndex;
    std::cin >> doctorIndex;
    if(1 <= doctorIndex and doctorIndex <= this->doctors.size()) {
        treatment.setDoctor(const_cast<Doctor *>(this->doctors[doctorIndex - 1]));
        treatment.setSuccessful(true);

        this->screen->setTreatmentCard(treatment.asCard());
    }
    else {
        std::cout << "Nooo! Your patient died because you chose a doctor who doesn't exist.\n";
        treatment.setSuccessful(false);
        Demo::sleep(1);

    }
    this->database.addFirstAidTreatment(treatment);
}

void Demo::solveSurgeryTreatment(const Patient *p, int index) {
    SurgeryTreatment treatment = Demo::randomSurgeryTreatment(const_cast<Patient *>(p), injuryMessage[index - 1]);

    this->screen->setTreatmentCard(treatment.asCard());

    std::system("clear");
    this->screen->show(std::cout);
    std::cout << "Choose Surgeon to take care of the Patient (1 -> " << this->doctors.size() << "): ";
    int doctorIndex;
    std::cin >> doctorIndex;
    if(1 <= doctorIndex and doctorIndex <= this->doctors.size()) {
        if (dynamic_cast<const SurgeonDoctor *>(this->doctors[doctorIndex - 1]) == nullptr) {
            std::cout << "Nooo! Your patient died because the doctor you choose can't perform surgeries.\n";
            treatment.setSuccessful(false);
            Demo::sleep(1);
        } else {
            treatment.setSurgeonDoctor(
                    const_cast<SurgeonDoctor *>(dynamic_cast<const SurgeonDoctor *>(doctors[doctorIndex -
                                                                                            1])));
            treatment.setSuccessful(true);

            this->screen->setTreatmentCard(treatment.asCard());
            treatment.getSurgeonDoctor()->success();
        }
    }
    else {
        std::cout << "Nooo! Your patient died because you chose a doctor who doesn't exist.\n";
        treatment.setSuccessful(false);
        Demo::sleep(1);

    }
    this->database.addSurgeryTreatment(treatment);
}

void Demo::solveCrashTreatment(const Patient *p, int index) {
    CrashTreatment treatment = Demo::randomCrashTreatment(const_cast<Patient *>(p), injuryMessage[index - 1]);

    bool ok = true;

    this->screen->setTreatmentCard(((FirstAidTreatment)treatment).asCard());

    std::system("clear");
    this->screen->show(std::cout);
    std::cout << "Choose Doctor to take care of the Patient (1 -> " << this->doctors.size() << "): ";
    int doctorIndex;
    std::cin >> doctorIndex;
    if(1 <= doctorIndex and doctorIndex <= this->doctors.size()) {
        treatment.setDoctor(const_cast<Doctor *>(this->doctors[doctorIndex - 1]));

        this->screen->setTreatmentCard(((FirstAidTreatment)treatment).asCard());
    }
    else {
        std::cout << "Nooo! Your patient died because you chose a doctor who doesn't exist.\n";
        treatment.setSuccessful(false);
        Demo::sleep(1);
        ok = false;
        this->database.addCrashTreatment(treatment);
        return;
    }


    this->screen->setTreatmentCard(((SurgeryTreatment)treatment).asCard());

    std::system("clear");
    this->screen->show(std::cout);
    std::cout << "Choose Surgeon to take care of the Patient (1 -> " << this->doctors.size() << "): ";
    std::cin >> doctorIndex;
    if(1 <= doctorIndex and doctorIndex <= this->doctors.size()) {
        if (dynamic_cast<const SurgeonDoctor *>(this->doctors[doctorIndex - 1]) == nullptr) {
            std::cout << "Nooo! Your patient died because the doctor you choose can't perform surgeries.\n";
            treatment.setSuccessful(false);
            Demo::sleep(1);
            ok = false;
        } else {
            treatment.setSurgeonDoctor(
                    const_cast<SurgeonDoctor *>(dynamic_cast<const SurgeonDoctor *>(doctors[doctorIndex -
                                                                                            1])));
            treatment.setSuccessful(true);

            this->screen->setTreatmentCard(((SurgeryTreatment)treatment).asCard());
            treatment.getSurgeonDoctor()->success();
        }
    }
    else {
        std::cout << "Nooo! Your patient died because you chose a doctor who doesn't exist.\n";
        treatment.setSuccessful(false);
        Demo::sleep(1);
        ok = false;

    }
    treatment.setSuccessful(ok);
    this->database.addCrashTreatment(treatment);
}

void Demo::printAllGameTreatments() const {
    for(auto& it: this->database.getAllTreatments()) {
        it->printCard(std::cout);
    }
}

void Demo::printAllTreatments() const {
    for(const auto& it: this->sandboxDatabase.getAllTreatments()) {
        it->printCard(std::cout);
    }
}

void Demo::treatmentAddScreen(std::string) {
    system("clear");
    std::cout << "*** Please insert Treatment info ***\n\n";
    Doctor d;
    std::cin >> d;
    sandboxDatabase.addDoctor(d);
}

void Demo::treatmentEditScreen(std::string) {

}

