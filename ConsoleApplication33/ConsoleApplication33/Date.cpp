#define NOMINMAX
#pragma warning(disable: 4996)

#include "Date.h"

Date::Date(int d, int m, int y) : day(d), month(m), year(y) {}

Date::Date(const Date& other) : day(other.day), month(other.month), year(other.year) {}

void Date::input() {
    std::cout << "Введите день, месяц, год (через пробел): ";
    std::cin >> day >> month >> year;
}

void Date::output() const {
    std::cout << day << "." << month << "." << year;
}

int Date::getDay() const { return day; }
int Date::getMonth() const { return month; }
int Date::getYear() const { return year; }

void Date::setDay(int d) { day = d; }
void Date::setMonth(int m) { month = m; }
void Date::setYear(int y) { year = y; }

Date& Date::operator=(const Date& other) {
    if (this != &other) {
        day = other.day;
        month = other.month;
        year = other.year;
    }
    return *this;
}