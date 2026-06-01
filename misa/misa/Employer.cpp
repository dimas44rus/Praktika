#include "Employer.h"
#include <iostream>

Employer::Employer(std::string n, double s) : name(n), salary(s) {}

// Реализация вывода под конкретную специфику Президента
President::President(std::string n, double s, std::string comp) : Employer(n, s), companyName(comp) {}
void President::Print() const {
    std::cout << "Должность: Президент компании \"" << companyName << "\"\n";
    std::cout << "Имя: " << name << ", Оклад: " << salary << " $\n";
}

// Реализация вывода под конкретную специфику Менеджера
Manager::Manager(std::string n, double s, int team) : Employer(n, s), teamSize(team) {}
void Manager::Print() const {
    std::cout << "Должность: Менеджер\n";
    std::cout << "Имя: " << name << ", Оклад: " << salary << " руб.\n";
    std::cout << "В подчинении сотрудников: " << teamSize << "\n";
}

// Реализация вывода под конкретную специфику Рабочего
Worker::Worker(std::string n, double s, std::string spec) : Employer(n, s), specialization(spec) {}
void Worker::Print() const {
    std::cout << "Должность: Рабочий\n";
    std::cout << "Имя: " << name << ", Оклад: " << salary << " руб.\n";
    std::cout << "Специализация: " << specialization << "\n";
}
