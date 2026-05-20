#include "StringBasic.h"
#include <iostream>

// Конструктор инициализирует базовые строки при создании объекта
StringBasic::StringBasic() {
    name = "Анна";
    text = "C++ — мощный язык программирования. Класс string очень удобен.";
}

// Задача 1: Анализ строки
void StringBasic::greetAndAnalyze() {
    std::cout << "Привет, " << name << "!" << std::endl;
    // .length() возвращает количество символов (длину) в строке
    std::cout << "Длина имени: " << name.length() << std::endl;
    // .at(0) безопасно возвращает символ на позиции 0 (первый символ) с проверкой границ
    std::cout << "Первый символ: " << name.at(0) << std::endl;
}

// Задача 2: Чтение строки целиком
void StringBasic::readFullName() {
    std::string fullName;
    std::cout << "Введите ваше имя и фамилию: ";
    // std::ws убирает оставшиеся в буфере пробелы и переводы строк
    // std::getline считывает всю строку до нажатия Enter, включая пробелы
    std::getline(std::cin >> std::ws, fullName);

    // Конкатенация (склеивание) строк с помощью оператора +
    std::string greeting = "Добрый день, " + fullName + "!";
    std::cout << greeting << std::endl;
}

// Задача 3: Поиск подстроки
void StringBasic::findSubstring() {
    // .find() ищет слово и возвращает индекс его первого символа
    size_t pos = text.find("string");

    // Если подстрока не найдена, .find() возвращает константу std::string::npos
    if (pos != std::string::npos) {
        std::cout << "Слово 'string' найдено на позиции " << pos << std::endl;
    }
    else {
        std::cout << "Слово не найдено" << std::endl;
    }
}
