#define _CRT_SECURE_NO_WARNINGS
#include "String.h"
#include <cstring>
#include <algorithm>

// Инициализация статической переменной
int String::instanceCount = 0;

// Конструктор по умолчанию (строка 80 символов)
String::String() : length(80) {
    str = new char[length + 1];
    str[0] = '\0';
    instanceCount++;
    std::cout << "Создан объект String (по умолчанию, 80 символов). Всего: "
        << instanceCount << std::endl;
}

// Конструктор для строки произвольного размера
String::String(size_t size) : length(size) {
    str = new char[length + 1];
    str[0] = '\0';
    instanceCount++;
    std::cout << "Создан объект String (размер " << length
        << "). Всего: " << instanceCount << std::endl;
}

// Конструктор, инициализирующий строкой от пользователя
String::String(const char* input) : length(strlen(input)) {
    str = new char[length + 1];
    strcpy(str, input);
    instanceCount++;
    std::cout << "Создан объект String (из строки \"" << str
        << "\"). Всего: " << instanceCount << std::endl;
}

// Конструктор копирования
String::String(const String& other) : length(other.length) {
    str = new char[length + 1];
    strcpy(str, other.str);
    instanceCount++;
    std::cout << "Создан объект String (копия \"" << str
        << "\"). Всего: " << instanceCount << std::endl;
}

// Деструктор
String::~String() {
    std::cout << "Удалён объект String \"" << str
        << "\". Осталось: " << instanceCount - 1 << std::endl;
    delete[] str;
    instanceCount--;
}

// Ввод строки с клавиатуры
void String::input() {
    char buffer[1000];
    std::cout << "Введите строку: ";
    std::cin.getline(buffer, 1000);

    delete[] str;
    length = strlen(buffer);
    str = new char[length + 1];
    strcpy(str, buffer);

    std::cout << "Строка обновлена: \"" << str << "\"" << std::endl;
}

// Вывод строки на экран
void String::output() const {
    std::cout << "Строка: \"" << str << "\" (длина: " << length << ")" << std::endl;
}

// Геттер для строки
const char* String::getString() const {
    return str;
}

// Геттер для длины
size_t String::getLength() const {
    return length;
}

// Статический метод для получения количества экземпляров
int String::getInstanceCount() {
    return instanceCount;
}

// Оператор присваивания
String& String::operator=(const String& other) {
    if (this != &other) {
        delete[] str;
        length = other.length;
        str = new char[length + 1];
        strcpy(str, other.str);
        std::cout << "Присваивание: \"" << str << "\"" << std::endl;
    }
    return *this;
}