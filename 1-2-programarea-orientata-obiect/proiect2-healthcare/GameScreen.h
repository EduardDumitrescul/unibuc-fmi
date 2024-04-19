//
// Created by eduarddumitrescul on 4/1/23.
//

#ifndef OOP_HEALTHCARE_GAMESCREEN_H
#define OOP_HEALTHCARE_GAMESCREEN_H

#include <vector>
#include <string>
#include "people/Doctor.h"
#include "DrawingUtil.h"

class GameScreen {
    static int doctorPanelStartLine;
    static int eventsPanelStartLine;
    static int treatmentCardStartLine;
    static int paddingLeft;
    int doctorPanelWidth;
    int width, height;
    std::vector <std::string> screen;
    std::vector <const Doctor*> doctors;
    std::vector <std::string> events;

    void clearDoctorPanel();
    void clearEventsPanel();
public:
    GameScreen(int, int);

    void show(std::ostream&);
    void setDoctors(std::vector <const Doctor*>);
    void setEvents(std::vector <std::string>);
    void setTreatmentCard(TreatmentCard card);
};

#endif //OOP_HEALTHCARE_GAMESCREEN_H
