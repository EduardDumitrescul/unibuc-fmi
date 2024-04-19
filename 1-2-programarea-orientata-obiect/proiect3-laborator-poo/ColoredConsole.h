//
// Created by eduarddumitrescul on 5/18/23.
//

#ifndef POO3_COLOREDCONSOLE_H
#define POO3_COLOREDCONSOLE_H

#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>

class ColoredConsole{
public:
    static const int UNSET = 29;
    static const int BLACK = 30;
    static const int RED = 31;
    static const int GREEN = 32;
    static const int YELLOW = 33;
    static const int BLUE = 34;
    static const int MAGENTA = 35;
    static const int CYAN = 36;
    static const int WHITE = 37;

    static const int BOLD = 1;
    static const int UNDERLINE = 4;
    static const int INVERSE = 7;
    static const int BOLD_OFF = 21;
    static const int UNDERLINE_OFF = 24;
    static const int INVERSE_OFF = 27;

public:
    static void print(std::ostream& out, std::string text, int fg = WHITE, int bg = BLACK, bool bold = false, bool underline = false, bool inverse = false);


};

void ColoredConsole::print(std::ostream &out, std::string text, int fg, int bg, bool bold, bool underline, bool inverse) {
    if (not (UNSET <= fg and fg <= WHITE)) {
        throw std::invalid_argument("foreground value not in range");
    }
    if (not (UNSET <= bg and bg <= WHITE)) {
        throw std::invalid_argument("background value not in range");
    }
    std::string string = "\033[0" + (bold ? ";" + std::to_string(BOLD) : "") + (underline ? ";" + std::to_string(UNDERLINE) : "") + (inverse ? ";" + std::to_string(INVERSE): "")
            + ((fg != UNSET) ? ";" + std::to_string(fg) : "") + ((bg != UNSET) ? std::to_string(bg+10) : "")  + "m" + text + "\033[0m";
    std::cout << string;
}

#endif //POO3_COLOREDCONSOLE_H
