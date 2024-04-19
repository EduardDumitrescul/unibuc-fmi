//
// Created by eduarddumitrescul on 5/16/23.
//

#ifndef POO3_PROJECT1_H
#define POO3_PROJECT1_H

#include <iostream>
#include "Grade.h"
#include "IOInterface.h"
#include "Data.h"

template <class GradeType>
class Project1: public IOInterface {
public:
    const static int MIN;
    const static int MAX;

protected:
    static int idCount;
    const int id;
    Grade<GradeType> grade;
    std::string name;
    int numberOfClasses; /// requirement: minimum 4
    int dataVariety; /// 40 - 100
    int constructors; /// 40 - 100
    int operators; /// 40 - 100
    int complexity; /// 40 - 100
    int creativity; /// 40 - 100
    bool gui;

public:
    // Project1();
    Project1(Grade<GradeType> grade = Grade<GradeType>(), std::string nume = "", int numberOfClasses = 0, int dataVariety = MIN, int constructors = MIN,
             int operators = MIN, int complexity = MIN, int creativity = MIN, bool gui = false);
    Project1(const Project1& object);
    Project1 &operator = (const Project1& object);

    virtual void read(std::istream& in);
    virtual void print(std::ostream& out) const;

    template <class Type>
    friend std::istream& operator>> (std::istream& in, Project1<Type>& object);

    template <class Type>
    friend std::ostream& operator<< (std::ostream& out, const Project1<Type>& object);

    int getId() const;
    std::string getName() const;
    Grade<GradeType> getGrade() const;

    void setGrade(Grade<GradeType> grade);
    void setName(std::string name);

    virtual void randomStats();
    virtual std::vector <std::pair<std::string, bool>> getBoolStats() const;
    virtual std::vector <std::tuple<std::string, int, int, int>> getRangeStats() const;

    virtual ~Project1();

};

template<class GradeType>
void Project1<GradeType>::setName(std::string name) {
    this->name = name;
}

template<class GradeType>
Grade<GradeType> Project1<GradeType>::getGrade() const {
    return this->grade;
}

template<class GradeType>
void Project1<GradeType>::setGrade(Grade<GradeType> grade) {
    this->grade = grade;
}

template <class GradeType>
const int Project1<GradeType>::MIN = 40;
template <class GradeType>
const int Project1<GradeType>::MAX = 100;

template<class GradeType>
std::vector<std::tuple<std::string, int, int, int>> Project1<GradeType>::getRangeStats() const {
    std::vector <std::tuple <std::string, int, int, int>> stats;
    stats.push_back({"Numar de Clase", this->numberOfClasses, 0, 4});
    stats.push_back({"Diversitatea Tipurilor de Date", this->dataVariety, MIN, MAX});
    stats.push_back({"Corectitudinea Constructorilor", this->constructors, MIN, MAX});
    stats.push_back({"Implementarea Operatorilor", this->operators, MIN, MAX});
    stats.push_back({"Complexitatea Proiectului", this->complexity, MIN, MAX});
    stats.push_back({"Creativitate", this->creativity, MIN, MAX});
    return stats;
}

template<class GradeType>
std::vector<std::pair<std::string, bool>> Project1<GradeType>::getBoolStats() const {
    std::vector <std::pair<std::string, bool>> stats;
    stats.push_back({"Interfata Grafica", true});
    return stats;
}

template<class GradeType>
std::string Project1<GradeType>::getName() const{
    return this->name;
}

template<class GradeType>
void Project1<GradeType>::randomStats() {
    this->numberOfClasses = Data::randomInt(2, 10);
    this->dataVariety = Data::randomInt(MIN, MAX);
    this->constructors = Data::randomInt(MIN, MAX);
    this->operators = Data::randomInt(MIN, MAX);
    this->complexity = Data::randomInt(MIN, MAX);
    this->creativity = Data::randomInt(MIN, MAX);
    this->gui = (rand() % 100 >= 80);
}

template<class GradeType>
int Project1<GradeType>::getId() const{
    return this->id;
}
//
//template<class GradeType>
//Project1<GradeType>::Project1() {
//    this->grade = Grade<GradeType>();
//    this->numberOfClasses = 0;
//    this->dataVariety = MIN;
//    this->constructors = MIN;
//    this->operators = MIN;
//    this->complexity = MIN;
//    this->creativity = MIN;
//    this->gui = false;
//}

template<class GradeType> int Project1<GradeType>::idCount = 100;

template<class GradeType>
Project1<GradeType>::Project1(Grade<GradeType> grade, std::string nume, int numberOfClasses, int dataVariety, int constructors,
                              int operators, int complexity, int creativity, bool gui): id(++idCount) {
    this->grade = grade;
    this->name = nume;
    this->numberOfClasses = numberOfClasses;
    this->dataVariety = dataVariety;
    this->constructors = constructors;
    this->operators = operators;
    this->complexity = complexity;
    this->creativity = creativity;
    this->gui = gui;
}

template<class GradeType>
Project1<GradeType>::Project1(const Project1 &object): id(++idCount)  {
    this->grade = object.grade;
    this->name = object.name;
    this->numberOfClasses = object.numberOfClasses;
    this->dataVariety = object.dataVariety;
    this->constructors = object.constructors;
    this->operators = object.operators;
    this->complexity = object.complexity;
    this->creativity = object.creativity;
    this->gui = object.gui;
}

template<class GradeType>
Project1<GradeType> &Project1<GradeType>::operator=(const Project1<GradeType> &object) {
    if(this != &object) {
        this->grade = object.grade;
        this->name = object.name;
        this->numberOfClasses = object.numberOfClasses;
        this->dataVariety = object.dataVariety;
        this->constructors = object.constructors;
        this->operators = object.operators;
        this->complexity = object.complexity;
        this->creativity = object.creativity;
        this->gui = object.gui;
    }
    return *this;
}

template<class GradeType>
void Project1<GradeType>::read(std::istream &in) {
    //in >> this->grade;
    std::cout << "Tema Proiect: ";
    std::getline(std::cin, this->name);
    std::cout << "Numar de Clase: ";
    in >> this->numberOfClasses;
    std::cout << "Varietate Tipuri de Date (" << MIN << "-" << MAX << "): ";
    in >> this->dataVariety;
    std::cout << "Corectitudinea Constructorilor (" << MIN << "-" << MAX << "): ";
    in >> this->constructors;
    std::cout << "Corectitudinea Operatorilor (" << MIN << "-" << MAX << "): ";
    in >> this->operators;
    std::cout << "Complexitate (" << MIN << "-" << MAX << "): ";
    in >> this->complexity;
    std::cout << "Creativitate (" << MIN << "-" << MAX << "): ";
    in >> this->creativity;
    std::cout << "GUI: (0/1): ";
    in >> this->gui;

}

template<class GradeType>
void Project1<GradeType>::print(std::ostream &out) const{
    out << this->grade;
    std::cout << "Tema Proiectului: ";
    out << this->name;
    std::cout << "Numar de Clase: ";
    out << this->numberOfClasses << '\n';
    std::cout << "Varietate Tipuri de Date: ";
    out << this->dataVariety << '\n';
    std::cout << "Corectitudinea Constructorilor: ";
    out << this->constructors << '\n';
    std::cout << "Corectitudinea Operatorilor: ";
    out << this->operators << '\n';
    std::cout << "Complexitate: ";
    out << this->complexity << '\n';
    std::cout << "Creativitate: ";
    out << this->creativity << '\n';
    std::cout << "GUI: ";
    out << (this->gui  == true ? "da" : "nu") << '\n';
}

template<class Type>
std::istream &operator>>(std::istream &in, Project1<Type> &object) {
    object.read(in);
    return in;
}

template<class Type>
std::ostream &operator<<(std::ostream &out, const Project1<Type> &object) {
    object.print(out);
    return out;
}

template<class GradeType>
Project1<GradeType>::~Project1() {

}

#endif //POO3_PROJECT1_H
