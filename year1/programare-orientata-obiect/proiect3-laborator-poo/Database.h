//
// Created by eduarddumitrescul on 5/17/23.
//

#ifndef POO3_DATABASE_H
#define POO3_DATABASE_H

#include <vector>
#include <list>
#include <set>
#include "Project1.h"
#include "Project2.h"
#include "Project3.h"
#include "Student.h"

template <class GradeType>
class Database {
    std::set <Project1<GradeType>*> projects;
    std::vector <Student*> students;

public:
    Database();
    Database(const std::vector <Project1<GradeType>*>& projects, const std::vector <Student*>& students);
    Database(const Database& object);
    Database& operator=(const Database<GradeType>& object);

    template <class Type> friend std::istream& operator >> (std::istream& in, Database<Type>& object);
    template <class Type> friend std::ostream& operator << (std::ostream& out, const Database<Type>& object);

    int insertStudent(const Student& object);
//    int insertProject1(const Project1<GradeType>& object);
//    int insertProject2(const Project2<GradeType>& object);
//    int insertProject3(const Project3<GradeType>& object);

    const std::vector <Student *> getStudents() const;
    const Student* getStudent(int id) const ;
    const Project1<GradeType>* getProject(int id) const;

    std::vector <std::pair <std::string, std::tuple <GradeType, GradeType, GradeType, int>>> getLeaderboard() const;

    template <class ProjectType> bool editProject(int id, const ProjectType& object);

    template <class ProjectType> int insertProject(ProjectType& object);


    ~Database();
};

template<class GradeType>
std::vector<std::pair<std::string, std::tuple<GradeType, GradeType, GradeType, int>>> Database<GradeType>::getLeaderboard() const {
    std::vector <std::pair <std::string, std::tuple <GradeType, GradeType, GradeType, int>>> leaderboard;
    for(auto it: this->students) {
        auto p1 = this->getProject(it->getProject1());
        auto p2 = this->getProject(it->getProject2());
        auto p3 = this->getProject(it->getProject3());
        int star = 0;
        GradeType n1 = (p1 == nullptr ? 0 : p1->getGrade().getValue());
        GradeType n2 = (p2 == nullptr ? 0 : p2->getGrade().getValue());
        GradeType n3 = (p3 == nullptr ? 0 : p3->getGrade().getValue());
        star += (p1 == nullptr ? 0 : p1->getGrade().getStar());
        star += (p2 == nullptr ? 0 : p2->getGrade().getStar());
        star += (p3 == nullptr ? 0 : p3->getGrade().getStar());

        leaderboard.push_back({it->getName(), {n1, n2, n3, star}});
    }
    return leaderboard;
}

template<class GradeType>
template<class ProjectType>
bool Database<GradeType>::editProject(int id, const ProjectType &object) {
    for(auto& p: this->projects) {
        if(p->getId() == id) {
            *p = object;
            return true;
        }
    }
    return false;
}

template<class GradeType>
const Student *Database<GradeType>::getStudent(int id) const{
    for(const Student* it: this->students) {
        if(it->getId() == id)
            return it;
    }
    return nullptr;
}

template<class GradeType>
const Project1<GradeType>* Database<GradeType>::getProject(int id) const {
    for(const Project1<GradeType>* it: this->projects) {
        if(it->getId() == id)
            return it;
    }
    return nullptr;
}

template<class GradeType>
const std::vector<Student *> Database<GradeType>::getStudents() const{
    return this->students;
}

template<class GradeType>
template<class ProjectType>
int Database<GradeType>::insertProject(ProjectType &object) {
    ProjectType* p = new ProjectType(object);
    this->projects.insert(p);
    return p->getId();
}

//template<class GradeType>
//int Database<GradeType>::insertProject3(const Project3<GradeType> &object) {
//    Project3<GradeType>* p = new Project3(object);
//    this->projects.insert(p);
//    return p->getId();
//}
//
//template<class GradeType>
//int Database<GradeType>::insertProject2(const Project2<GradeType> &object) {
//    Project2<GradeType>* p = new Project2(object);
//    this->projects.insert(p);
//    return p->getId();
//}
//
//template<class GradeType>
//int Database<GradeType>::insertProject1(const Project1<GradeType> &object) {
//    Project1<GradeType>* p = new Project1(object);
//    this->projects.insert(p);
//    return p->getId();
//}

template<class GradeType>
int Database<GradeType>::insertStudent(const Student &object) {
    Student* p = new Student(object);
    this->students.push_back(p);
    return p->getId();
}

template<class GradeType>
Database<GradeType>::Database() {

}

template<class GradeType>
Database<GradeType>::Database(const std::vector<Project1<GradeType> *>& projects, const std::vector <Student*>& students) {
    this->projects = projects;
    this->students = students;
}

template<class GradeType>
Database<GradeType>::Database(const Database &object) {
    this->projects = object.projects;
    this->students = object.students;
}

template<class GradeType>
Database<GradeType> &Database<GradeType>::operator=(const Database<GradeType> &object) {
    if(this != &object) {
        for(int i = 0; i < this->projects.size(); i ++) {
            if(this->projects[i] != nullptr) {
                delete this->projects[i];
                this->projects[i] = nullptr;
            }
        }
        this->projects.clear();
        this->projects = object.projects;

        for(int i = 0; i < this->students.size(); i ++) {
            if(this->students[i] != nullptr) {
                delete this->students[i];
                this->students[i] = nullptr;
            }
        }
        this->students.clear();
        this->students = object.students;
    }
    return *this;
}

template<class Type>
std::istream &operator>>(std::istream &in, Database<Type> &object) {
    ///TODO
    return in;
}

template<class Type>
std::ostream &operator<<(std::ostream &out, const Database<Type> &object) {
    ///TODO
    return out;
}

template<class GradeType>
Database<GradeType>::~Database() {
    while(this->projects.empty() == false) {
        delete *this->projects.begin();
        this->projects.erase(this->projects.begin());
    }
//    for(int i = 0; i < this->projects.size(); i ++) {
//        if(this->projects[i] != nullptr) {
//            delete this->projects[i];
//            this->projects[i] = nullptr;
//        }
//    }
//    this->projects.clear();

    for(int i = 0; i < this->students.size(); i ++) {
        if(this->students[i] != nullptr) {
            delete this->students[i];
            this->students[i] = nullptr;
        }
    }
    this->students.clear();
}


#endif //POO3_DATABASE_H
