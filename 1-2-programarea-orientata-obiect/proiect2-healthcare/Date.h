//
// Created by eduarddumitrescul on 3/30/23.
//

#ifndef OOP_HEALTHCARE_DATE_H
#define OOP_HEALTHCARE_DATE_H

#include <istream>
#include <iostream>

struct Date {
    int year = 0, month = 0, day = 0;

    friend std::istream& operator >>(std::istream& in, Date& object) {
        std::cout << "Year: ";
        std::cin >> object.year;
        std::cout << "Month: ";
        std::cin >> object.month;
        std::cout << "Day: ";
        std::cin >> object.day;
        return in;
    }

    friend std::ostream& operator <<(std::ostream& out, const Date& object) {
        out << object.asString();
        return out;
    }

    std::string asString() const{
        return std::to_string(day) + '.' + std::to_string(month) + '.' + std::to_string(year);
    }
};


#endif //OOP_HEALTHCARE_DATE_H
