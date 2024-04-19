//
// Created by eduarddumitrescul on 3/30/23.
//

#ifndef OOP_HEALTHCARE_DOCTOR_H
#define OOP_HEALTHCARE_DOCTOR_H


#include <string>
#include "../IOInterface.h"

class Doctor: public IOInterface {
protected:
    static int idCount;
    const int id;

    std::string firstname;
    std::string lastname;

    int experience;
    int salary;

public:
    Doctor(std::string firstname = "Firstname", std::string lastname = "Lastname", int experience = 0, int salary = 0);
    Doctor(const Doctor&);

    Doctor& operator=(const Doctor&);
    friend std::istream& operator>>(std::istream&, Doctor&);
    friend std::ostream& operator<<(std::ostream&, const Doctor&);

    std::istream& read(std::istream&);
    std::ostream& print(std::ostream&) const;

    virtual std::string toString() const;
    virtual void printCard(std::ostream&) const;

    virtual std::string shortString() const;

    int getId() const;
    std::string getName() const;

    void setFirstname(std::string);
    void setLastname(std::string);
    void setExperience(int);
    void setSalary(int);

    virtual ~Doctor();
};


#endif //OOP_HEALTHCARE_DOCTOR_H
