//
// Created by eduarddumitrescul on 5/18/23.
//

#ifndef POO3_MENU_H
#define POO3_MENU_H

#include <thread>
#include <cstdlib>
#include <iostream>
#include "ColoredConsole.h"
#include "Game.h"

class Menu: protected ColoredConsole {
    static const int TYPE_DELAY = 30;
    static const int INT10 = 1;
    static const int FLOAT10 = 2;

    int students = 3;
    int grading = 1;
    bool tutorialDone = false;

    static int instances;
    static Menu* menu_;

    Menu() = default;
    Menu(const Menu& object) = delete;
    Menu& operator= (const Menu& object) = delete;

public:
    void run();
    void tutorial();
    void settingsScreen();
    void descriptionScreen();
    void printTitle();
    void startGame();
    static void printErrorMessage(std::string msg);
    static void printWithRandomDelay(std::string text, int maxDelay);
    static void sleep(int milliseconds);
    static void clearScreen();
    int readInt();

    static Menu* getInstance();
    ~Menu();
};

int Menu::instances = 0;
Menu* Menu::menu_ = nullptr;


Menu::~Menu() {
    instances --;
    if(instances == 0) {
        if(menu_ == nullptr)
            delete menu_;
        menu_ = nullptr;
    }
}

void Menu::run() {
    tutorialDone = false;
    tutorial();
    if(tutorialDone) {
        startGame();
    }
}


void Menu::tutorial() {
    bool running = true;
    while(running) {
        if(this->tutorialDone) {
            break;
        }
        clearScreen();
        printTitle();

        try {
            std::cout << "Apasa [0] pentru a iesi\n";
            std::cout << "Apasa [1] pentru a incepe\n";
            int cmd;
            cmd = this->readInt();
            switch(cmd) {
                case 0: {
                    running = false;
                    break;
                }
                case 1: {
                    descriptionScreen();
                    break;
                }
                default: {
                    throw std::string("Comanda incorecta");
                    break;
                }
            }
        }
        catch (std::string msg) {
            printErrorMessage(msg);
        }
        catch (std::invalid_argument ex) {
            printErrorMessage(ex.what());
        }
    }
}

void Menu::sleep(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds (milliseconds));
}

void Menu::clearScreen() {
    std::system("clear");
}

void Menu::descriptionScreen() {
    bool running = true;
    while(running) {
        if(this->tutorialDone) {
            break;
        }
        clearScreen();
        printTitle();

        std::cout << "\n";
        std::string desc = "Astazi, Eduard Szmeteanca te-a rugat sa tii laboratorul de POO in locul lui.\n"
                           "Totusi, a uitat sa mentioneze ca azi erau programati studentii pentru a prezenta proiectele.\n"
                           "Tu fiind un bun prieten, treci peste acest lucru si decizi sa faci o treaba cat mai buna.\n\n"
                           "Vor exista 3 etape, cate una pentru fiecare dintre cele 3 proiecte, iar datoria ta este sa notezi proiectele\n"
                           "in functie de cat de bine au fost realizate. Daca vreunele iti plac in mod special, poti sa le acorzi si stelute.\n\n\n";


        printWithRandomDelay(desc, TYPE_DELAY);

        try {
            std::cout << "Apasa [0] pentru a te intoarce\n";
            std::cout << "Apasa [1] pentru a continua\n";
            int cmd;
            cmd = this->readInt();
            switch(cmd) {
                case 0: {
                    running = false;
                    break;
                }
                case 1: {
                    settingsScreen();
                    break;
                }
                default: {
                    throw std::string("Comanda incorecta");
                    break;
                }
            }
        }
        catch (std::string msg) {
            printErrorMessage(msg);
        }
        catch (std::invalid_argument ex) {
            printErrorMessage(ex.what());
        }
    }
}

void Menu::printTitle() {
    print(std::cout, "                     Laborator POO 2023                     \n", WHITE, BLACK, true, false, true);
}

void Menu::printWithRandomDelay(std::string text, int maxDelay) {
    if(maxDelay == 0) {
        std::cout << text;
        return;
    }
    for(char chr: text) {
        int delay = rand() % maxDelay;
        std::cout << chr << std::flush;
        sleep(delay);
    }
}

void Menu::printErrorMessage(std::string msg) {
    print(std::cout, msg, RED, UNSET, true, false, false);
    std::cout << '\n';
    sleep(2000);
}

void Menu::settingsScreen() {
    bool running = true;


    while(running) {
        clearScreen();
        printTitle();

        std::cout << "Numar de studenti: " << this->students << '\n';
        std::cout << "Tip de notare: ";
        switch(grading) {
            case INT10: {
                std::cout << "0 - 10 (numere naturale)";
                break;
            }
            case FLOAT10: {
                std::cout << "0.0 - 10.0 (numere rationale)";
                break;
            }
            default: {
                std::cout << "0 - 10 (numere naturale)";
                break;
            }
        }
        std::cout << '\n' << '\n';

        try {
            std::cout << "Apasa [0] pentru a te intoarce\n";
            std::cout << "Apasa [1] pentru a modifica numarul de studenti\n";
            std::cout << "Apasa [2] pentru a modifica modalitatea de notare\n";
            std::cout << "Apasa [3] pentru a incepe laboratorul\n";

            int cmd;
            cmd = this->readInt();
            switch(cmd) {
                case 0: {
                    running = false;
                    break;
                }
                case 1: {
                    std::cout << "Insereaza o noua valoare: (min 1, max 10) \n";
                    int value;
                    value = this->readInt();
                    if(value < 1 or value > 10)
                        throw std::out_of_range("numarul de studenti trebuie sa fie intre 1 si 10 - valoarea ta: " + std::to_string(value));
                    this->students = value;
                    break;
                }
                case 2: {
                    std::cout << "[1] - note de la 1 la 10 (fara zecimale) \n";
                    std::cout << "[2] - note de la 1.0 la 10.0 (cu zecimale) \n";
                    int value;
                    value = this->readInt();
                    if(value < 1 or value > 2)
                        throw std::out_of_range("optiunea ta nu exista - optiunea ta: " + std::to_string(value));
                    this->grading = value;
                    break;
                }
                case 3: {
                    running = false;
                    tutorialDone = true;
                    break;
                }
                default: {
                    throw std::string("Comanda incorecta");
                }
            }
        }
        catch (std::string msg) {
            printErrorMessage(msg);
        }
        catch(std::out_of_range& ex) {
            printErrorMessage(ex.what());
        }
        catch (std::invalid_argument ex) {
            printErrorMessage(ex.what());
        }
    }
}

void Menu::startGame() {
    try {
        switch(this->grading) {
            case INT10: {
                Game<int>* game = Game<int>::getInstance(this->students, this->grading);
                game->run();
                break;
            }
            case FLOAT10: {
                Game<float>* game = Game<float>::getInstance(this->students, this->grading);
                game->run();
                break;
            }
            default: {
                throw std::invalid_argument("Nu se poate incepe jocul cu valorile:\nnumar de studenti = " + std::to_string(students) + "\nmetoda de notare = " + std::to_string(grading));
            }
        }
    }
    catch (std::invalid_argument ex) {
        printErrorMessage(ex.what());
    }
    catch (std::exception& ex) {
        printErrorMessage(ex.what());
    }

}

int Menu::readInt() {
    std::string temp;
    std::getline(std::cin, temp);
    return std::stoi(temp);
}

Menu *Menu::getInstance() {
    return nullptr;
}

#endif //POO3_MENU_H
