//
// Created by eduarddumitrescul on 4/1/23.
//

#ifndef OOP_HEALTHCARE_DATA_H
#define OOP_HEALTHCARE_DATA_H

#include <string>
#include <vector>
#include <random>

class PredefinedData{

    static std::vector <std::string> lastnames;
    static std::vector <std::pair <std::string, char>> firstnames;
    static std::vector <std::string> specialties;
    static std::vector <std::string> treatments[3];
    static std::vector <std::string> notes;
    static std::vector <std::string> addresses;
    static std::vector <std::string> crashMessage;

public:
    static std::string getLastname();
    static std::pair <std::string, char> getFirstname();
    static std::string getSpecialty();
    static std::string getTreatment(int);
    static std::string getNote();
    static std::string getAddress();
    static std::string getCrashMessage();

    static int randomIndex(int);
    static int randomInt(int, int);

    static const int FIRST_AID = 0;
    static const int MEDICATION = 1;
    static const int SURGERY = 2;
};



std::string PredefinedData::getLastname() {
    return lastnames[randomIndex(lastnames.size())];
}

std::pair <std::string, char> PredefinedData::getFirstname() {
    return firstnames[randomIndex(firstnames.size())];
}

std::string PredefinedData::getSpecialty() {
    return specialties[randomIndex(specialties.size())];
}

std::string PredefinedData::getTreatment(int type) {
    return treatments[type][randomIndex(treatments->size())];
}

std::string PredefinedData::getNote() {
    return notes[randomIndex(notes.size())];
}

std::string PredefinedData::getAddress() {
    return addresses[randomIndex(addresses.size())];
}

std::string PredefinedData::getCrashMessage() {
    return crashMessage[randomIndex(crashMessage.size())];
}

int PredefinedData::randomIndex(int max) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, max - 1);
    return dist(mt);
}


int PredefinedData::randomInt(int min, int max) {
    return min + randomIndex(max - min);
}


std::vector <std::string> PredefinedData::lastnames = {
        "Smith", "Johnson", "Williams", "Jones", "Brown",
        "Garcia", "Miller", "Davis", "Rodriguez", "Martinez",
        "Hernandez", "Lopez", "Gonzalez", "Perez", "Taylor",
        "Anderson", "Wilson", "Moore", "Jackson", "Martin"
};

std::vector <std::pair <std::string, char>> PredefinedData::firstnames = {
        {"William", 'M'}, {"James", 'M'}, {"John", 'M'}, {"Robert", 'M'}, {"David", 'M'},
        {"Joseph", 'M'}, {"Richard", 'M'}, {"Charles", 'M'}, {"Michael", 'M'}, {"Thomas", 'M'},
        {"Mary", 'F'}, {"Elizabeth", 'F'}, {"Jennifer", 'F'}, {"Linda", 'F'}, {"Barbara", 'F'},
        {"Margaret", 'F'}, {"Susan", 'F'}, {"Dorothy", 'F'}, {"Sarah", 'F'}, {"Karen", 'F'}
};

std::vector <std::string> PredefinedData::specialties = {
        "Cardiac Surgery", "Neurosurgery", "Orthopedic Surgery", "Plastic Surgery", "General Surgery",
        "Oncologic Surgery", "Trauma Surgery", "Vascular Surgery", "Pediatric Surgery", "Transplant Surgery"
};

std::vector <std::string> PredefinedData::treatments[3] = {
        {"Cuts and scrapes", "Burns", "Sprains and strains", "Broken bones", "Choking",
         "Heat exhaustion", "Hypothermia", "Seizures", "Allergic reactions", "Poisoning"},
        {"Hypertension", "Diabetes", "High cholesterol", "Asthma", "Allergies",
         "Depression", "Anxiety", "Insomnia", "Rheumatoid arthritis", "Chronic pain"},
        {"Appendicitis", "Gallstones", "Hernia", "Cataracts", "Arthritis",
         "Heart disease", "Lung cancer", "Brain tumor", "Kidney stones", "Prostate cancer"}
};

std::vector <std::string> PredefinedData::notes = {
        "Patient complains of headache. Prescribed a good night's sleep and a large glass of wine.",
        "Patient claims to be allergic to exercise. Diagnosis: lazyitis.",
        "Patient needs more Vitamin Sea. Advised a beach vacation.",
        "Patient reports having difficulty sleeping. Prescribed one boring meeting.",
        "Patient says they're always tired. Suggested they try living in a retirement home.",
        "Patient claims to have lost their appetite. Suggested they start watching cooking shows on TV.",
        "Patient presents with a broken heart. Prescribed a tub of ice cream and a sad movie marathon.",
        "Patient reports feeling stressed. Advised them to try playing with puppies or kittens.",
        "Patient has a history of fainting. Suggested they try standing up more slowly.",
        "Patient complains of muscle pain. Diagnosis: too much Netflix and chill.",
        "Patient reports being stressed at work. Prescribed a beach day with a 'sick' note.",
        "Patient presents with a sore throat. Suggested they try singing along to their favorite songs.",
        "Patient says they're feeling down. Prescribed a day of self-care and Netflix.",
        "Patient has trouble sleeping at night. Diagnosis: too much screen time.",
        "Patient complains of stomach pains. Advised them to cut back on their mother-in-law's cooking.",
        "Patient reports feeling anxious. Prescribed a day of playing with puppies and kittens.",
        "Patient has a history of falls. Advised them to stop trying to be a ninja.",
        "Patient complains of neck pain. Diagnosis: too much phone scrolling.",
        "Patient says they're feeling forgetful. Advised them to try using post-it notes.",
        "Patient reports feeling burnt out. Prescribed a day of doing absolutely nothing.",
};

std::vector <std::string> PredefinedData::addresses = {
        "1234 Maple Street, Anytown, USA",
        "56 Ocean View Road, Seaside Heights, USA",
        "789 Pine Street, Mountain View, USA",
        "1010 Broad Street, Metropolis, USA",
        "555 Elm Avenue, Riverdale, USA",
        "90210 Beverly Hills Drive, Los Angeles, USA",
        "777 Park Lane, Central Park, USA",
        "2468 Main Street, Smallville, USA",
        "1111 Lincoln Road, Miami Beach, USA",
        "4321 Cherry Lane, Springfield, USA"
};

std::vector <std::string> PredefinedData::crashMessage = {
        "Looks like the Hot Wheels just got a little too hot to handle!",
        "Well, that's one way to make a Barbie car convertible.",
        "Looks like the police are going to need a tow truck for this one!",
        "I guess that race didn't go as planned.",
        "That car crash was more epic than any Fast and Furious movie."
};

#endif //OOP_HEALTHCARE_DATA_H
