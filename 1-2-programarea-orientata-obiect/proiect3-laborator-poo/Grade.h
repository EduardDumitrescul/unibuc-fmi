//
// Created by eduarddumitrescul on 5/16/23.
//

#ifndef POO3_GRADE_H
#define POO3_GRADE_H


#include <istream>

template <class GradeType>
class Grade {
    GradeType value{};
    std::string comment;
    bool star;

public:
    Grade();
    Grade(GradeType value, std::string comment = "", bool start = false);
    Grade(const Grade& object);
    Grade& operator=(const Grade&);

    bool operator <(const Grade& object);
    bool operator >(const Grade& object);
    bool operator ==(const Grade& object);

    template <class T>
    friend std::istream& operator >>(std::istream& in, Grade<T>&);
    template <class T>
    friend std::ostream& operator <<(std::ostream& out, const Grade<T>&);

    void setComments(std::string comment);

    GradeType getValue() const;
    bool getStar() const;

    ~Grade();
};

template<class GradeType>
bool Grade<GradeType>::getStar() const {
    return this->star;
}

template<class GradeType>
GradeType Grade<GradeType>::getValue() const {
    return this->value;
}

template<class GradeType>
void Grade<GradeType>::setComments(std::string comment) {
    this->comment = comment;
}

template<class Type>
bool Grade<Type>::operator==(const Grade<Type> &object) {
    return this->value == object.value and this->star == object.star;
}

template<class Type>
bool Grade<Type>::operator>(const Grade<Type> &object) {
    if(this->value == object.value)
        return this->star > object.star;
    return this->value > object.value;
}

template<class Type>
bool Grade<Type>::operator<(const Grade<Type> &object) {
    if(this->value == object.value)
        return this->star < object.star;
    return this->value < object.value;
}

template<class Type>
Grade<Type>::~Grade() {

}

template<class Type>
Grade<Type> &Grade<Type>::operator=(const Grade &object) {
    if(this != &object) {
        this->value = object.value;
        this->comment = object.comment;
        this->star = object.star;
    }
    return *this;
}

template<class Type>
Grade<Type>::Grade(const Grade &object) {
    this->value = object.value;
    this->comment = object.comment;
    this->star = object.star;
}

template<class Type>
Grade<Type>::Grade(Type value, std::string comment, bool star) {
    this->value = value;
    this->comment = comment;
    this->star = star;
}

template<class Type>
Grade<Type>::Grade() {

}

template <class Type>
std::istream &operator>>(std::istream &in, Grade<Type> &object) {
    std::cout << "Ce nota ii dai?  ";
    in >> object.value;
    std::cout << "Vreun comentariu?  ";
    std::getline(in, object.comment);
    std::getline(in, object.comment);
    std::cout << "Ii dai steluta? (1/0): ";
    in >> object.star;
    return in;
}

template <class Type>
std::ostream &operator<<(std::ostream &out, const Grade<Type> &object) {
    out << "Nota: " << object.value << '\n';
    out << "Comentarii: " << object.comment << '\n';
    out << "Are steluta?: " << (object.star == true ? "da" : "nu") << '\n';
    return out;
}


#endif //POO3_GRADE_H
