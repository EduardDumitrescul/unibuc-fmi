//
// Created by eduarddumitrescul on 5/17/23.
//

#ifndef POO3_PROJECT3_H
#define POO3_PROJECT3_H

#include "Project2.h"

template <class GradeType>
class Project3: public Project2<GradeType> {
private:
    int templateFunctions;
    int exceptions;
    int casting;
    bool templateClass;
public:

    Project3();
    Project3(Grade<GradeType> grade, std::string nume, int numberOfClasses, int dataVariety, int constructors,
             int operators, int complexity, int creativity, bool gui, int virtualization,
             int inheritance, bool diamond, bool abstractOrInterface,
             int templateFunctions, int exceptions, int casting, bool templateClass);
    Project3(const Project3& object);
    Project3<GradeType>& operator=(const Project3<GradeType> object);

    void randomStats();
    virtual std::vector <std::pair<std::string, bool>> getBoolStats() const;
    virtual std::vector <std::tuple<std::string, int, int, int>> getRangeStats() const;

    void read(std::istream& in);
    void print(std::ostream& out) const;

    ~Project3();

};

template<class GradeType>
std::vector<std::tuple<std::string, int, int, int>> Project3<GradeType>::getRangeStats() const {
    std::vector <std::tuple <std::string, int, int, int>> stats = Project2<GradeType>::getRangeStats();
    stats.push_back({"Numar de Fucntii Template", this->templateFunctions, 0, 2});
    stats.push_back({"Mumar de Exceptii Tratate", this->exceptions, 0, 6});
    stats.push_back({"Upcasting si Downcasting", this->casting, Project1<GradeType>::MIN, Project1<GradeType>::MAX});
    return stats;
}

template<class GradeType>
std::vector<std::pair<std::string, bool>> Project3<GradeType>::getBoolStats() const {
    std::vector <std::pair <std::string, bool>> stats = Project2<GradeType>::getBoolStats();
    stats.push_back({"Clasa Template", this->templateClass});
    return stats;
}

template<class GradeType>
void Project3<GradeType>::randomStats() {
    Project2<GradeType>::randomStats();
    this-> templateFunctions = Data::randomInt(0, 5);
    this-> exceptions = Data::randomInt(0, 10);
    this-> casting = Data::randomInt(40, 100);
    this->templateClass = (rand() % 100 >= 70);
}

template<class GradeType>
Project3<GradeType>::Project3(): Project2<GradeType>() {
    this->templateFunctions = Project1<GradeType>::MIN;
    this->exceptions = Project1<GradeType>::MIN;
    this->casting = Project1<GradeType>::MIN;
    this->templateClass = false;
}

template<class GradeType>
Project3<GradeType>::Project3(Grade<GradeType> grade, std::string nume, int numberOfClasses, int dataVariety, int constructors,
                              int operators, int complexity, int creativity, bool gui, int virtualization,
                              int inheritance, bool diamond, bool abstractOrInterface, int templateFunctions,
                              int exceptions, int casting, bool templateClass):
          Project2<GradeType>(grade, nume, numberOfClasses, dataVariety, constructors, operators, complexity, creativity, gui, virtualization, inheritance, diamond, abstractOrInterface){
    this->templateFunctions = templateFunctions;
    this->exceptions = exceptions;
    this->casting = casting;
    this->templateClass = templateClass;
}

template<class GradeType>
Project3<GradeType>::Project3(const Project3 &object): Project2<GradeType>((Project2<GradeType>&) object) {
    this->templateFunctions = object.templateFunctions;
    this->exceptions = object.exceptions;
    this->casting = object.casting;
    this->templateClass = object.templateClass;
}

template<class GradeType>
Project3<GradeType> &Project3<GradeType>::operator=(const Project3<GradeType> object) {
    if(this != &object) {
        (Project2<GradeType>&)this = object;
        this->templateFunctions = object.templateFunctions;
        this->exceptions = object.exceptions;
        this->casting = object.casting;
        this->templateClass = object.templateClass;
    }
    return *this;
}

template<class GradeType>
void Project3<GradeType>::read(std::istream &in) {
    Project2<GradeType>::read(in);
    std::cout << "Cate functii template are?: ";
    in >> this->templateFunctions;
    std::cout << "Cate exceptii trateaza?: ";
    in >> this->exceptions;
    std::cout << "Corectitudinea Downcasting-ului si a Upcasting-ului: ";
    in >> this->casting;
    std::cout << "Are clasa template? (0/1): ";
    in >> this->templateClass;
}

template<class GradeType>
void Project3<GradeType>::print(std::ostream &out) const {
    Project2<GradeType>::print(out);
    std::cout << "Numar de functii template: ";
    out << this->templateFunctions << '\n';
    std::cout << "Exceptii tratate: ";
    out << this->exceptions << '\n';
    std::cout << "Corectitudinea Downcasting-ului si a Upcasting-ului: ";
    out << this->casting << '\n';
    std::cout << "Are clasa template?: ";
    out << (this->templateClass ? "da" : "nu") << '\n';
}

template<class GradeType>
Project3<GradeType>::~Project3() {

}

#endif //POO3_PROJECT3_H
