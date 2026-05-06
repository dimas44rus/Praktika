#ifndef HUMAN_H
#define HUMAN_H

#include "Date.h"

class Human {
private:
    int id;
    char* surname;
    char* name;
    char* patronymic;
    Date birthDate;
    static int totalInstances;

public:
    // Конструкторы
    Human(int _id, const char* _surname, const char* _name,
        const char* _patronymic, const Date& _birthDate);
    Human();  // по умолчанию с делегированием
    Human(const Human& other);  // копирования
    ~Human();

    // Статическая функция для подсчета экземпляров
    static int getTotalInstances();

    // Геттеры
    int getId() const;
    const char* getSurname() const;
    const char* getName() const;
    const char* getPatronymic() const;
    Date getBirthDate() const;

    // Сеттеры
    void setId(int _id);
    void setSurname(const char* _surname);
    void setName(const char* _name);
    void setPatronymic(const char* _patronymic);
    void setBirthDate(const Date& _birthDate);

    // Вывод информации
    void display() const;

    // Оператор присваивания
    Human& operator=(const Human& other);
};

#endif