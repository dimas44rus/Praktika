#ifndef STRING_BASIC_H
#define STRING_BASIC_H

#include <string>

class StringBasic {
private:
    std::string name; // Хранит имя для первой задачи
    std::string text; // Хранит предложение для поиска подстроки

public:
    StringBasic();           // Конструктор класса
    void greetAndAnalyze(); // Метод для Задачи 1 (.length, .at)
    void readFullName();    // Метод для Задачи 2 (getline)
    void findSubstring();   // Метод для Задачи 3 (.find)
};

#endif
