//
// Created by eduarddumitrescul on 5/18/23.
//

#ifndef POO3_GAME_H
#define POO3_GAME_H

#include <thread>
#include <unordered_map>
#include <algorithm>
#include "ColoredConsole.h"
#include "Database.h"

template <class GradeType>
class Game: private ColoredConsole {
     constexpr const static float NO_PROJECT_CHANCE = 0.1;
protected:
    int students{};
    int grading{};
    Database<GradeType> database;

    std::unordered_map <std::string, bool> existsStudent;
    std::unordered_map <std::string, bool> existsProjectName;

    Game() = default;
    Game(int students, int grading);
    static Game* game_;
    static int instances;

public:
    Game(Game& object) = delete;
    void operator =(const Game& object) = delete;

    static Game* getInstance(int students, int grading);

    void run();
    void setup();
    void testSetup();
    template <class ProjectType> int createProject();
    void playStage(int stage);
    void leaderboardScreen();
    void printProgressBar(int value, int min, int max);
    void printLegend();
    int readInt();

    void studentScreen(int id, int stage);

    ~Game();

    void printTitle();

    void printStageTitle(int stage);

    void printWithRandomDelay(std::string text, int maxDelay);

    void printErrorMessage(std::string msg);

    void sleep(int milliseconds);

    void clearScreen();
};

template<class GradeType>
int Game<GradeType>::readInt() {
    std::string temp;
    std::getline(std::cin, temp);
    return std::stoi(temp);
}

template<class GradeType>
void Game<GradeType>::leaderboardScreen() {
    auto v = this->database.getLeaderboard();
    std::sort(v.begin(), v.end());
    clearScreen();
    printTitle();
    print(std::cout, "Tabelul cu Notele Studentilor\n", WHITE, BLACK, true, false, true);
    std::cout << '\n';
    for(auto it: v) {
        double medie = (std::get<0>(it.second) + std::get<1>(it.second) + std::get<2>(it.second)) / 3.0;
        int color = (medie >= 5 ? GREEN : RED);
        print(std::cout, it.first + " - medie: " + std::to_string(medie), color, UNSET, true, false, false);
        std::cout << " (";
        std::cout << std::get<0>(it.second) << ", " << std::get<1>(it.second) << ", " << std::get<2>(it.second) << ")  -  ";
        print(std::cout, "stelute: " + std::to_string(std::get<3>(it.second)), color, UNSET, true, false, false);
        std::cout << "\n";

    }

}

template<class GradeType>
void Game<GradeType>::printLegend() {

    std::cout << "\n\n\n";
    print(std::cout, "       Foarte bine      ", GREEN, UNSET, true, false, true);
    std::cout << '\n';
    print(std::cout, "       asa si asa       ", YELLOW, UNSET, true, false, true);
    std::cout << '\n';
    print(std::cout, "         slabut         ", RED, UNSET, true, false, true);
    std::cout << '\n';
}

template<class GradeType>
void Game<GradeType>::printProgressBar(int value, int min, int max) {
    int color;
    if(value >= min + 0.75 * (max - min))
        color = GREEN;
    else if(value >= min + 0.3 * (max - min))
        color = YELLOW;
    else color = RED;

    std::string bar = "";

    int length = 20;
    int i;
    for(i = 0; i < length * value / max and i < length; i ++)
        bar += "▇";
    for(; i < length; i ++)
        bar.push_back(' ');
   // std::cout << '[';
    print(std::cout, bar, color, UNSET, false, false, false);
   // std::cout << "]  ";
   std::cout << "    ";

    print(std::cout, std::to_string(value) + "/" + std::to_string(max), color, UNSET, true, false, false);

}

template<class GradeType>
void Game<GradeType>::testSetup() {
    for(auto it: this->database.getStudents()){
        std::cout << it->getName() << ' ' << this->database.getProject(it->getProject1()) << ' ' <<  this->database.getProject(it->getProject2()) << ' '<< '\n';
    }
}

template<class GradeType>
template<class ProjectType>
int Game<GradeType>::createProject() {
    int rng = rand() % 100;
    if(rng <= 100 * NO_PROJECT_CHANCE) {
        return -1;
    }
    while(true) {
        std::string name = Data::getRandomProjectName();
        if(this->existsProjectName[name] == false) {
            this->existsProjectName[name] = true;
            ProjectType p;
            p.setName(name);
            p.randomStats();
            return this->database.insertProject(p);
        }
    }
}

template<class GradeType>
void Game<GradeType>::setup() {
    for(int i = 0; i < students; i ++) {
        while(true) {
            std::string name = Data::getName();
            if(!existsStudent[name]) {
                existsStudent[name] = true;

                int id1 = this->createProject<Project1<GradeType>>();
                int id2 = this->createProject<Project2<GradeType>>();
                int id3 = this->createProject<Project3<GradeType>>();

                this->database.insertStudent(Student(name, id1, id2, id3));
                break;
            }
        }
    }
}

template<class GradeType>
void Game<GradeType>::studentScreen(int id, int stage) {
    bool running = true;
    while(running) {
        clearScreen();
        printTitle();
        printStageTitle(stage);

        const Student* student = this->database.getStudent(id);
        std::cout << *student;

        if(stage == 3)
            std::cout << "Proiecte: " << ((student->getProject1() != -1) + (student->getProject2() != -1) + (student->getProject3() != -1)) << "/3" << '\n';

        const Project1<GradeType>* p;
        switch(stage) {
            case 1: {
                p = this->database.getProject(student->getProject1());
                break;
            }
            case 2: {
                p = this->database.getProject(student->getProject2());
                break;
            }
            case 3: {
                p = this->database.getProject(student->getProject3());
                break;
            }
            default: {
                break;
            }
        }


        if(p == nullptr) {
            print(std::cout, "Nu a facut proiectul!!!\n", RED, UNSET, true, false, false);
            std::cout << student->getName() << " va primi in mod implicit nota 0 pentru acest proiect.\n";
            std::cout << "Apasa [enter] pentru a continua\n";
           /// std::cin.get();
            std::string tmp;
            std::getline(std::cin, tmp);
            running = false;
        }
        else {
            std::cout << '\n' << "Denumire Proiect: ";
            print(std::cout, p->getName(), UNSET, UNSET, true, true, false);
            std::cout << '\n' << '\n';

              std::vector <std::pair <std::string, bool>> boolStats = p->getBoolStats();
            std::vector <std::tuple <std::string, int, int, int>> rangeStats = p->getRangeStats();

            for(std::pair <std::string, bool> it: boolStats) {
                std::string name = "                                    ";
                name.replace(name.begin(), name.begin() + it.first.size(), it.first);
                std::cout << "■ " << name << ":   ";
                int color = (it.second ? GREEN : RED);
                std::string text = (it.second ? "DA" : "NU");
                print(std::cout, text, color, UNSET, false, false, false);
                std::cout << '\n';
            }
            std::cout << '\n';

            for(std::tuple <std::string, int, int, int> it: rangeStats) {
                std::string name = "                                    ";
                name.replace(name.begin(), name.begin() + std::get<0> (it).size(), std::get<0>(it));
                std::cout << "■ " << name << ":   ";
                this->printProgressBar(std::get<1>(it), std::get<2>(it), std::get<3>(it));
                std::cout << '\n';
            }

            printLegend();

            try {
                std::cout << "Ce nota ii dai? ";
                GradeType value;
                std::string comment = "";
                bool star = false;
                switch (grading) {
                    case 1: {
                        value = readInt();
                        if(value == 777) {
                            Project1 <GradeType>* temp;

                            if(dynamic_cast<const Project3<GradeType>*> (p) != nullptr) {
                                temp = new Project3<GradeType> (*dynamic_cast<const Project3<GradeType>*> (p));
                            }
                            else if(dynamic_cast<const Project2<GradeType>*> (p) != nullptr) {
                                temp = new Project2<GradeType> (*dynamic_cast<const Project2<GradeType>*> (p));
                            } else {
                                temp = new Project1<GradeType> (*p);
                            }
                            std::cin >> *temp;
                            this->database.editProject(p->getId(), *temp);
                            delete temp;
                            throw 777;
                        }
                        if(not(0 <= value and value <= 10))
                            throw std::string("Nota nu se afla in intervalul corespunzator 0 - 10 (valoarea ta " + std::to_string(value) + ")");
                        break;
                    }
                    case 2: {
                        value = readInt();
                        if(value == 777) {
                            Project1 <GradeType>* temp;

                            if(dynamic_cast<const Project3<GradeType>*> (p) != nullptr) {
                                temp = new Project3<GradeType> (*dynamic_cast<const Project3<GradeType>*> (p));
                            }
                            else if(dynamic_cast<const Project2<GradeType>*> (p) != nullptr) {
                                temp = new Project2<GradeType> (*dynamic_cast<const Project2<GradeType>*> (p));
                            } else {
                                temp = new Project1<GradeType> (*p);
                            }
                            std::cin >> *temp;
                            this->database.editProject(p->getId(), *temp);
                            delete temp;
                            throw 777;
                        }
                        if(not(0.0 <= value and value <= 10.0))
                            throw std::string("Nota nu se afla in intervalul corespunzator 0.0 - 10.0 (valoarea ta " + std::to_string(value) + ")");
                        break;
                    }
                    default: {
                        throw std::string("Nu exista aceasta metoda de notare");
                    }
                }

                std::cout << "Adauga un comentariu in notitele tale: ";
                std::cin.get();
                std::getline(std::cin, comment);

                std::cout << "Ii acorzi o steluta? [0/1]";
                int aux;
                aux = readInt();
                switch (aux) {
                    case 0: {
                        star = false;
                        break;
                    }
                    case 1: {
                        star = true;
                        break;
                    }
                    default: {
                        throw std::string("Valoarea introdusa nu e permisa!");
                    }
                }

                Project1 <GradeType>* temp;

                if(dynamic_cast<const Project3<GradeType>*> (p) != nullptr) {
                    temp = new Project3<GradeType> (*dynamic_cast<const Project3<GradeType>*> (p));
                    temp->setGrade(Grade(value, comment, star));
                }
                else if(dynamic_cast<const Project2<GradeType>*> (p) != nullptr) {
                    temp = new Project2<GradeType> (*dynamic_cast<const Project2<GradeType>*> (p));
                    temp->setGrade(Grade(value, comment, star));
                } else {
                    temp = new Project1<GradeType> (*p);
                    temp->setGrade(Grade(value, comment, star));
                }

                this->database.editProject(p->getId(), *temp);
                delete temp;
                running = false;
            }
            catch (std::string ex) {
                printErrorMessage(ex);
            }
            catch (int ex) {
                printErrorMessage("Eroare 777! Mai incearca");
            }
            catch (std::invalid_argument ex) {
                printErrorMessage(ex.what());
            }
        }
    }
}

template<class GradeType>
void Game<GradeType>::printStageTitle(int stage) {
    print(std::cout, "   Proiectul " + std::to_string(stage) + "   \n", WHITE, BLACK, true, false, true);
}

template<class GradeType>
void Game<GradeType>::playStage(int stage) {

    for(const Student* s: this->database.getStudents()) {
        studentScreen(s->getId(), stage);
    }

}

template<class GradeType>
void Game<GradeType>::run() {
    setup();
    //testSetup();
    for(int stage = 1; stage <= 3; stage ++) {
        this->playStage(stage);
    }
    leaderboardScreen();
}

template<class GradeType>
Game<GradeType>::Game(int students, int grading) {
    this->students = students;
    this->grading = grading;
}

template <class GradeType>
int Game<GradeType>::instances = 0;
template <class GradeType>
Game<GradeType>* Game<GradeType>::game_ = nullptr;

template<class GradeType>
Game<GradeType>::~Game() {
    instances --;
    if(instances == 0) {
        if(game_ != nullptr)
            delete game_;
        game_ = nullptr;
    }
}

template<class GradeType>
Game<GradeType> *Game<GradeType>::getInstance(int students, int grading) {
    instances ++;
    if (game_ == nullptr) {
        game_ = new Game(students, grading);
    }
    return game_;
}
template <class GradeType>
void Game<GradeType>::printTitle() {
    print(std::cout, "                     Laborator POO 2023                     \n", WHITE, BLACK, true, false, true);
}

template <class GradeType>
void Game<GradeType>::printWithRandomDelay(std::string text, int maxDelay) {
    for(char chr: text) {
        int delay = rand() % maxDelay;
        std::cout << chr << std::flush;
        sleep(delay);
    }
}

template <class GradeType>
void Game<GradeType>::printErrorMessage(std::string msg) {
    print(std::cout, msg, RED, UNSET, true, false, false);
    std::cout << '\n';
    sleep(2000);
}

template <class GradeType>
void Game<GradeType>::sleep(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds (milliseconds));
}

template <class GradeType>
void Game<GradeType>::clearScreen() {
    std::system("clear");
}



#endif //POO3_GAME_H
