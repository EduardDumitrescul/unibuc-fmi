//
// Created by eduarddumitrescul on 5/17/23.
//

#ifndef POO3_DATA_H
#define POO3_DATA_H

#include <vector>
#include <string>
#include <fstream>

struct Data {
private:
    static bool projectNameFileOpened;
    static std::vector <std::string> studentNames;
    static std::vector <std::string> projectNames;

public:
    static std::string getRandomProjectName();
    static std::string getName();
    static int randomInt(int min, int max);

};
bool Data::projectNameFileOpened = false;
std::vector <std::string> Data::projectNames{};


std::vector <std::string> Data::studentNames = {
        "Alexandra",
        "Andrei",
        "Bianca",
        "Cristian",
        "Diana",
        "Elena",
        "Florin",
        "Gabriela",
        "Ionut",
        "Laura"
};

std::string Data::getRandomProjectName() {
    //TODO add exception
    if (!Data::projectNameFileOpened) {
        std::ifstream fin("../data/project-names.txt");
        std::string temp;
        int n;
        fin >> n;
        while(n --) {
            std::getline(fin, temp);
            Data::projectNames.push_back(temp);
        }
        Data::projectNameFileOpened = true;
    }
    return Data::projectNames[rand() % Data::projectNames.size()];
}

std::string Data::getName() {
    return Data::studentNames[rand() % Data::studentNames.size()];
}

int Data::randomInt(int min, int max) {
    return min + rand() % (max - min);
}

#endif //POO3_DATA_H
