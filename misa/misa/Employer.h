#pragma once
#include <string>

// Абстрактный базовый класс Employer
class Employer {
protected:
    std::string name; // Имя служащего
    double salary;    // Зарплата
public:
    Employer(std::string n, double s);
    virtual ~Employer() = default;

    // Чисто виртуальная функция, обеспечивающая интерфейс вывода информации
    virtual void Print() const = 0;
};

// Класс Президент
class President : public Employer {
private:
    std::string companyName; // Дополнительное приватное поле
public:
    President(std::string n, double s, std::string comp);
    void Print() const override; // Переопределение для Президента
};

// Класс Менеджер
class Manager : public Employer {
private:
    int teamSize; // Дополнительное приватное поле
public:
    Manager(std::string n, double s, int team);
    void Print() const override; // Переопределение для Менеджера
};

// Класс Рабочий
class Worker : public Employer {
private:
    std::string specialization; // Дополнительное приватное поле
public:
    Worker(std::string n, double s, std::string spec);
    void Print() const override; // Переопределение для Рабочего
};
