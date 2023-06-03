//
// Created by eduarddumitrescul on 5/17/23.
//

#ifndef POO3_PROJECT2_H
#define POO3_PROJECT2_H

#include "IOInterface.h"
#include "Project1.h"

template <class GradeType>
class Project2: public Project1<GradeType> {
protected:
    int virtualization; /// 40 - 100
    int inheritance; /// 40 - 100
    bool diamond;
    bool abstractOrInterface;

public:
    Project2();
    Project2(Grade<GradeType> grade, std::string nume, int numberOfClasses, int dataVariety, int constructors,
             int operators, int complexity, int creativity, bool gui, int virtualization, int inheritance, bool diamond, bool abstractOrInterface);
    Project2(const Project2& object);
    Project2& operator = (const Project2& object);

    virtual void read(std::istream& in);
    virtual void print(std::ostream& out) const;

    virtual void randomStats();
    virtual std::vector <std::pair<std::string, bool>> getBoolStats() const;
    virtual std::vector <std::tuple<std::string, int, int, int>> getRangeStats() const;

    virtual ~Project2();
};

template<class GradeType>
std::vector<std::tuple<std::string, int, int, int>> Project2<GradeType>::getRangeStats() const {
    std::vector <std::tuple <std::string, int, int, int>> stats = Project1<GradeType>::getRangeStats();
    stats.push_back({"Implementarea Virtualizarii", this->virtualization, Project1<GradeType>::MIN, Project1<GradeType>::MAX});
    stats.push_back({"Corectitudinea Mostenirii", this->inheritance, Project1<GradeType>::MIN, Project1<GradeType>::MAX});
    return stats;
}

template<class GradeType>
std::vector<std::pair<std::string, bool>> Project2<GradeType>::getBoolStats() const {
    std::vector <std::pair <std::string, bool>> stats = Project1<GradeType>::getBoolStats();
    stats.push_back({"Problema Mostenirii in Diamant", this->diamond});
    stats.push_back({"Clasa Abstracta / Interfata", this->abstractOrInterface});
    return stats;
}

template<class GradeType>
void Project2<GradeType>::randomStats() {
    Project1<GradeType>::randomStats();
    this->virtualization = Data::randomInt(Project1<GradeType>::MIN, Project1<GradeType>::MAX);
    this->inheritance = Data::randomInt(Project1<GradeType>::MIN, Project1<GradeType>::MAX);
    this->diamond = (rand() % 100 >= 50);
    this->abstractOrInterface = (rand() % 100 >= 30);
}

template<class GradeType>
Project2<GradeType>::Project2(): Project1<GradeType>() {
    this->virtualization = Project1<GradeType>::MIN;
    this->inheritance = Project1<GradeType>::MIN;
    this->diamond = false;
    this->abstractOrInterface = false;
}

template<class GradeType>
Project2<GradeType>::Project2(Grade<GradeType> grade, std::string nume, int numberOfClasses, int dataVariety, int constructors,
                              int operators, int complexity, int creativity, bool gui, int virtualization,
                              int inheritance, bool diamond, bool abstractOrInterface):
        Project1<GradeType>(grade, nume, numberOfClasses, dataVariety, constructors, operators, complexity, creativity, gui){
    this->virtualization = virtualization;
    this->inheritance = inheritance;
    this->diamond = diamond;
    this->abstractOrInterface = abstractOrInterface;
}

template<class GradeType>
Project2<GradeType>::Project2(const Project2 &object): Project1<GradeType>((Project1<GradeType> &) object) {
    this->virtualization = object.virtualization;
    this->inheritance = object.inheritance;
    this->diamond = object.diamond;
    this->abstractOrInterface = object.abstractOrInterface;
}

template<class GradeType>
Project2<GradeType>& Project2<GradeType>::operator=(const Project2<GradeType> &object) {
    if(this != &object) {
        (Project1<GradeType>)this = object;
        this->virtualization = object.virtualization;
        this->inheritance = object.inheritance;
        this->diamond = object.diamond;
        this->abstractOrInterface = object.abstractOrInterface;
    }
    return *this;
}

template<class GradeType>
void Project2<GradeType>::read(std::istream &in) {
    Project1<GradeType>::read(in);
    std::cout << "Calitatea Virtualizarii (" << Project1<GradeType>::MIN << '-' << Project1<GradeType>::MAX << "): ";
    in >> this->virtualization;
    std::cout << "Corectitudinea Mostenirii (" << Project1<GradeType>::MIN << '-' << Project1<GradeType>::MAX << "): ";
    in >> this->inheritance;
    std::cout << "Rezolva Mostenirea in Diamant? (0/1): ";
    in >> this->diamond;
    std::cout << "Are Clasa Abstracta sau Interfata? (0/1): ";
    in >> this->abstractOrInterface;
}

template<class GradeType>
void Project2<GradeType>::print(std::ostream &out) const {
    Project1<GradeType>::print(out);
    std::cout << "Calitatea Virtualizarii: ";
    out << this->virtualization << '\n';
    std::cout << "Corectitudinea Mostenirii: ";
    out << this->inheritance << '\n';
    std::cout << "Rezolva Mostenirea in Diamant?: ";
    out << (this->diamond == true ? "da" : "nu") << '\n';
    std::cout << "Are Clasa Abstracta sau Interfata?: ";
    out << (this->abstractOrInterface == true ? "da" : "nu") << '\n';
}

template<class GradeType>
Project2<GradeType>::~Project2() {

}


#endif //POO3_PROJECT2_H
