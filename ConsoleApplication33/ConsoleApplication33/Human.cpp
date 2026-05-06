#define NOMINMAX
#pragma warning(disable: 4996)

#include "Human.h"
#include <cstring>
#include <iostream>

int Human::totalInstances = 0;

// Конструктор с параметрами (с использованием списка инициализации)
Human::Human(int _id, const char* _surname, const char* _name,
    const char* _patronymic, const Date& _birthDate)
    : id(_id), birthDate(_birthDate) {

    surname = new char[strlen(_surname) + 1];
    name = new char[strlen(_name) + 1];
    patronymic = new char[strlen(_patronymic) + 1];

    strcpy(surname, _surname);
    strcpy(name, _name);
    strcpy(patronymic, _patronymic);

    totalInstances++;
    std::cout << "Создан человек: " << surname << " " << name << " (всего: " << totalInstances << ")\n";
}

// Конструктор по умолчанию с делегированием
Human::Human() : Human(0, "", "", "", Date(1, 1, 2000)) {
    std::cout << "Создан пустой человек (делегирование)\n";
}

// Конструктор копирования
Human::Human(const Human& other)
    : id(other.id), birthDate(other.birthDate) {

    surname = new char[strlen(other.surname) + 1];
    name = new char[strlen(other.name) + 1];
    patronymic = new char[strlen(other.patronymic) + 1];

    strcpy(surname, other.surname);
    strcpy(name, other.name);
    strcpy(patronymic, other.patronymic);

    totalInstances++;
    std::cout << "Скопирован человек: " << surname << " " << name << " (всего: " << totalInstances << ")\n";
}

// Деструктор
Human::~Human() {
    std::cout << "Удалён человек: " << surname << " " << name << " (осталось: " << totalInstances - 1 << ")\n";

    delete[] surname;
    delete[] name;
    delete[] patronymic;

    totalInstances--;
}

// Подсчет созданных экземпляров
int Human::getTotalInstances() {
    return totalInstances;
}

// Геттеры
int Human::getId() const { return id; }
const char* Human::getSurname() const { return surname; }
const char* Human::getName() const { return name; }
const char* Human::getPatronymic() const { return patronymic; }
Date Human::getBirthDate() const { return birthDate; }

// Сеттеры
void Human::setId(int _id) { id = _id; }

void Human::setSurname(const char* _surname) {
    delete[] surname;
    surname = new char[strlen(_surname) + 1];
    strcpy(surname, _surname);
}

void Human::setName(const char* _name) {
    delete[] name;
    name = new char[strlen(_name) + 1];
    strcpy(name, _name);
}

void Human::setPatronymic(const char* _patronymic) {
    delete[] patronymic;
    patronymic = new char[strlen(_patronymic) + 1];
    strcpy(patronymic, _patronymic);
}

void Human::setBirthDate(const Date& _birthDate) {
    birthDate = _birthDate;
}

// Вывод информации
void Human::display() const {
    std::cout << "\n=== Информация о человеке ===\n";
    std::cout << "ID: " << id << std::endl;
    std::cout << "Фамилия: " << surname << std::endl;
    std::cout << "Имя: " << name << std::endl;
    std::cout << "Отчество: " << patronymic << std::endl;
    std::cout << "Дата рождения: ";
    birthDate.output();
    std::cout << std::endl;
    std::cout << "============================\n";
}

// Оператор присваивания
Human& Human::operator=(const Human& other) {
    if (this != &other) {
        id = other.id;
        birthDate = other.birthDate;

        delete[] surname;
        delete[] name;
        delete[] patronymic;

        surname = new char[strlen(other.surname) + 1];
        name = new char[strlen(other.name) + 1];
        patronymic = new char[strlen(other.patronymic) + 1];

        strcpy(surname, other.surname);
        strcpy(name, other.name);
        strcpy(patronymic, other.patronymic);
    }
    return *this;
}