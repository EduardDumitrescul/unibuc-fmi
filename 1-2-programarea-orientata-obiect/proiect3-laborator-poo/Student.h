//
// Created by eduarddumitrescul on 5/17/23.
//

#ifndef POO3_STUDENT_H
#define POO3_STUDENT_H

#include <string>

class Student {
    static int idCount;
    const int id;

    std::string name;
    int idProject1;
    int idProject2;
    int idProject3;

public:
    Student();
    Student(std::string name, int idProject1, int idProject2, int idProject3);
    Student(const Student& object);
    Student& operator = (const Student& object);

    friend std::istream& operator >> (std::istream& in, Student& object);
    friend std::ostream& operator << (std::ostream& out, const Student& object);

    int getId() const;
    std::string getName() const;
    int getProject1() const;
    int getProject2() const;
    int getProject3() const;

    ~Student();
};

int Student::idCount = 100;

Student::~Student() {

}

std::ostream &operator<<(std::ostream &out, const Student &object) {
    out << "Nume: " << object.name << '\n';
    //out << "Proiecte: " << ((object.idProject1 != -1) + (object.idProject2 != -1) + (object.idProject3 != -1)) << "/3" << '\n';
    return out;
}

std::istream &operator>>(std::istream &in, Student &object) {
    std::cout << "Nume: ";
    in.get();
    std::getline(in, object.name);
    return in;
}

Student &Student::operator=(const Student &object) {
    if(this != &object) {
        this->name = object.name;
        this->idProject1 = object.idProject1;
        this->idProject2 = object.idProject2;
        this->idProject3 = object.idProject3;
    }
    return *this;
}

Student::Student(const Student &object): id(++idCount) {
    this->name = object.name;
    this->idProject1 = object.idProject1;
    this->idProject2 = object.idProject2;
    this->idProject3 = object.idProject3;
}

Student::Student(std::string name, int idProject1, int idProject2, int idProject3): id(++idCount) {
    this->name = name;
    this->idProject1 = idProject1;
    this->idProject2 = idProject2;
    this->idProject3 = idProject3;
}

Student::Student(): id(++idCount) {
    this->name = "anonim";
    this->idProject1 = -1;
    this->idProject2 = -1;
    this->idProject3 = -1;
}

int Student::getId() const {
    return this->id;
}

std::string Student::getName() const {
    return this->name;
}

int Student::getProject1() const {
    return this->idProject1;
}
int Student::getProject2() const {
    return this->idProject2;
}
int Student::getProject3() const {
    return this->idProject3;
}
#endif //POO3_STUDENT_H
