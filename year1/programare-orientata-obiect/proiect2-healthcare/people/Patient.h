//
// Created by eduarddumitrescul on 3/30/23.
//

#ifndef OOP_HEALTHCARE_PATIENT_H
#define OOP_HEALTHCARE_PATIENT_H


#include <string>

class Patient {
    static int idCount;
    const int id;

    std::string firstname;
    std::string lastname;
    char sex;
    int birthYear;

public:
    Patient(std::string firstname="Firstname", std::string lastname = "Lastname", char gender = 'X', int birthYear = 0);
    Patient(const Patient&);

    Patient& operator= (const Patient&);
    friend std::istream& operator >>(std::istream&, Patient&);
    friend std::ostream& operator <<(std::ostream&, const Patient&);

    std::string toString() const;
    void printCard(std::ostream&) const;

    int getId() const;
    std::string getName() const;

    void setFirstname(std::string);
    void setLastname(std::string);
    void setBirthyear(int );
};


#endif //OOP_HEALTHCARE_PATIENT_H
