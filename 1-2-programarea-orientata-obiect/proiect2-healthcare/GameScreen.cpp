//
// Created by eduarddumitrescul on 4/1/23.
//


#include "GameScreen.h"

int GameScreen::doctorPanelStartLine = 3;
int GameScreen::eventsPanelStartLine = 3;
int GameScreen::paddingLeft = 3;
int GameScreen::treatmentCardStartLine = 10;

GameScreen::GameScreen(int width, int height) {
    this->width = width;
    this->height = height;
    screen.resize(height);
    for(auto& line: screen) {
        line.resize(width, ' ');
    }
    for(int i = 0; i < screen[0].size(); i ++)
        screen[0][i] = '*';

    doctorPanelWidth = width / 3.2;
}

void GameScreen::show(std::ostream & out) {
    for(auto& line: screen) {
        out << line + "\n";
    }
}

void GameScreen::setDoctors(std::vector<const Doctor *> doctors) {
    this->clearDoctorPanel();
    this->doctors = doctors;
    for(int i = 0; i < doctors.size(); i++) {
        std::string docInfo = std::to_string(i + 1) + ". " + doctors[i]->shortString();
        screen[doctorPanelStartLine + i].replace(
                width - doctorPanelWidth,
                docInfo.size(),
                docInfo
        );
    }
}

void GameScreen::clearDoctorPanel() {
    for(int i = 0; i < this->doctors.size(); i++) {
        for(int j = width - this->doctorPanelWidth; j < this->width - 1; j ++)
            this->screen[doctorPanelStartLine + i][j] = ' ';
    }
}

void GameScreen::setEvents(std::vector<std::string> events) {
    this->clearEventsPanel();
    this->events = events;
    for(int i = 0; i < this->events.size(); i ++) {
        std::string s = std::to_string(i+1) + ". " + this->events[i];
        this->screen[eventsPanelStartLine + i].replace(
                paddingLeft,
                s.size(),
                s
        );
    }
}

void GameScreen::clearEventsPanel() {
    for(int i = 0; i < this->events.size(); i ++) {
        for(int j = 0; j < this->events[i].size() + 5; j ++) {
            this->screen[eventsPanelStartLine + i][paddingLeft + j] = ' ';
        }
    }
}

void GameScreen::setTreatmentCard(TreatmentCard card) {
    for(int i = 0; i < card.card.size(); i ++) {
        this->screen[treatmentCardStartLine + i].replace(
                paddingLeft,
                card.card[i].size(),
                card.card[i]
        );
    }
}

