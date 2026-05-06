#ifndef DATE_H
#define DATE_H

#include <iostream>

class Date {
private:
    int day, month, year;

public:
    Date(int d = 1, int m = 1, int y = 2000);
    Date(const Date& other);
    ~Date() = default;

    void input();
    void output() const;

    // Геттеры и сеттеры
    int getDay() const;
    int getMonth() const;
    int getYear() const;
    void setDay(int d);
    void setMonth(int m);
    void setYear(int y);

    Date& operator=(const Date& other);
};

#endif