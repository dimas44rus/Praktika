// ===================================================
// ЗАЩИТА ОТ ПОВТОРНОГО ВКЛЮЧЕНИЯ
// ===================================================
#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// ===================================================
// БАЗОВЫЙ КЛАСС EMPLOYEE (СОТРУДНИК)
// ===================================================
// Базовый класс для всех типов сотрудников
class Employee {
protected:
    // Поля доступны наследникам (protected), но скрыты от внешнего кода (private)
    string name;        // Имя сотрудника
    int id;             // Уникальный идентификатор
    double baseSalary;  // Базовая зарплата

public:
    // ===================================================
    // КОНСТРУКТОР
    // ===================================================
    Employee(const string& n, int i, double salary)
        : name(n), id(i), baseSalary(salary) {
    }

    // ===================================================
    // ВИРТУАЛЬНЫЙ ДЕСТРУКТОР
    // ===================================================
    // Обязателен для корректного удаления объектов производных классов
    virtual ~Employee() {}

    // ===================================================
    // ВИРТУАЛЬНЫЙ МЕТОД РАСЧЁТА ЗАРПЛАТЫ
    // ===================================================
    // В базовом классе возвращает базовую зарплату
    // Каждый производный класс переопределяет этот метод по-своему
    virtual double calculateSalary() const {
        return baseSalary;
    }

    // ===================================================
    // ВИРТУАЛЬНЫЙ МЕТОД ВЫВОДА ИНФОРМАЦИИ
    // ===================================================
    virtual void getInfo() const {
        cout << "ID: " << id << ", Name: " << name
            << ", Salary: " << calculateSalary() << endl;
    }

    // ===================================================
    // ГЕТТЕРЫ (МЕТОДЫ ДЛЯ ПОЛУЧЕНИЯ ЗНАЧЕНИЙ)
    // ===================================================
    int getId() const { return id; }
};

// ===================================================
// КЛАСС MANAGER (МЕНЕДЖЕР) - НАСЛЕДУЕТ ОТ EMPLOYEE
// ===================================================
class Manager : public Employee {
private:
    double bonusPercent;  // Бонус в процентах (например, 20 = 20%)
    int subordinates;     // Количество подчинённых

public:
    // ===================================================
    // КОНСТРУКТОР
    // ===================================================
    Manager(const string& n, int i, double salary, double bonus, int sub)
        : Employee(n, i, salary), bonusPercent(bonus), subordinates(sub) {
    }

    // ===================================================
    // ПЕРЕОПРЕДЕЛЕНИЕ МЕТОДА РАСЧЁТА ЗАРПЛАТЫ
    // ===================================================
    // Формула: базовая + процент бонуса + 100 за каждого подчинённого
    // Пример: базовая 50000, бонус 20%, 5 подчинённых
    // = 50000 + 10000 + 500 = 60500
    double calculateSalary() const override {
        return baseSalary + (bonusPercent / 100.0) * baseSalary + subordinates * 100;
    }

    void getInfo() const override {
        cout << "Manager - ID: " << id << ", Name: " << name
            << ", Subordinates: " << subordinates
            << ", Salary: " << calculateSalary() << endl;
    }
};

// ===================================================
// КЛАСС DEVELOPER (РАЗРАБОТЧИК) - НАСЛЕДУЕТ ОТ EMPLOYEE
// ===================================================
class Developer : public Employee {
private:
    string programmingLanguage;  // Язык программирования (C++, Python, Java...)
    int experience;               // Опыт работы в годах

public:
    Developer(const string& n, int i, double salary, const string& lang, int exp)
        : Employee(n, i, salary), programmingLanguage(lang), experience(exp) {
    }

    // ===================================================
    // ПЕРЕОПРЕДЕЛЕНИЕ МЕТОДА РАСЧЁТА ЗАРПЛАТЫ
    // ===================================================
    // Формула: базовая + опыт * 5000
    // Пример: базовая 60000, опыт 3 года
    // = 60000 + 15000 = 75000
    double calculateSalary() const override {
        return baseSalary + experience * 5000;
    }

    void getInfo() const override {
        cout << "Developer - ID: " << id << ", Name: " << name
            << ", Language: " << programmingLanguage << ", Experience: " << experience << " years"
            << ", Salary: " << calculateSalary() << endl;
    }
};

// ===================================================
// КЛАСС INTERN (СТАЖЁР) - НАСЛЕДУЕТ ОТ EMPLOYEE
// ===================================================
class Intern : public Employee {
private:
    bool hasMentor;  // Наличие наставника (true - есть, false - нет)

public:
    Intern(const string& n, int i, double salary, bool mentor)
        : Employee(n, i, salary), hasMentor(mentor) {
    }

    // ===================================================
    // ПЕРЕОПРЕДЕЛЕНИЕ МЕТОДА РАСЧЁТА ЗАРПЛАТЫ
    // ===================================================
    // Стажёр получает 70% от базовой зарплаты
    // Пример: базовая 30000 → зарплата 21000
    double calculateSalary() const override {
        return baseSalary * 0.7;
    }

    void getInfo() const override {
        cout << "Intern - ID: " << id << ", Name: " << name
            << ", Has mentor: " << (hasMentor ? "yes" : "no")
            << ", Salary: " << calculateSalary() << endl;
    }
};

// ===================================================
// КЛАСС DEPARTMENT (ОТДЕЛ)
// ===================================================
// Управляет списком сотрудников и выполняет различные операции
class Department {
private:
    // ===================================================
    // ВЕКТОР УКАЗАТЕЛЕЙ НА СОТРУДНИКОВ
    // ===================================================
    // vector - динамический массив, может расти и уменьшаться
    // Employee* - указатель на базовый класс (полиморфизм!)
    // Может хранить указатели на объекты ЛЮБЫХ производных классов
    vector<Employee*> employees;

public:
    // ===================================================
    // ДЕСТРУКТОР - ОСВОБОЖДАЕТ ПАМЯТЬ
    // ===================================================
    // При уничтожении отдела удаляем всех сотрудников
    ~Department() {
        for (Employee* emp : employees) {
            delete emp;  // Виртуальный деструктор Employee гарантирует правильное удаление
        }
    }

    // ===================================================
    // ДОБАВЛЕНИЕ СОТРУДНИКА
    // ===================================================
    // @param emp - указатель на сотрудника (должен быть создан через new)
    void addEmployee(Employee* emp) {
        employees.push_back(emp);  // Добавляем в конец вектора
    }

    // ===================================================
    // УДАЛЕНИЕ СОТРУДНИКА ПО ID
    // ===================================================
    // @param id - идентификатор сотрудника для удаления
    void removeEmployee(int id) {
        // remove_if - перемещает элементы, подлежащие удалению, в конец
        // Лямбда-функция [id](Employee* emp) проверяет совпадение ID
        auto it = remove_if(employees.begin(), employees.end(),
            [id](Employee* emp) { return emp->getId() == id; });

        // Освобождаем память удалённых сотрудников
        for (auto i = it; i != employees.end(); ++i) {
            delete* i;
        }
        // Удаляем из вектора
        employees.erase(it, employees.end());
    }

    // ===================================================
    // ПОДСЧЁТ ОБЩЕЙ ЗАРПЛАТЫ
    // ===================================================
    // @return сумма зарплат всех сотрудников отдела
    double getTotalSalary() const {
        double total = 0;
        for (Employee* emp : employees) {
            total += emp->calculateSalary();  // Полиморфный вызов
        }
        return total;
    }

    // ===================================================
    // ПОИСК СОТРУДНИКА С МАКСИМАЛЬНОЙ ЗАРПЛАТОЙ
    // ===================================================
    // @return указатель на сотрудника с максимальной зарплатой
    Employee* getMaxSalaryEmployee() const {
        if (employees.empty()) return nullptr;

        // max_element находит максимальный элемент по заданному критерию
        return *max_element(employees.begin(), employees.end(),
            [](Employee* a, Employee* b) {
                return a->calculateSalary() < b->calculateSalary();
            });
    }

    // ===================================================
    // СОРТИРОВКА СОТРУДНИКОВ ПО ЗАРПЛАТЕ
    // ===================================================
    // Сортирует по убыванию (от большего к меньшему)
    void sortBySalary() {
        sort(employees.begin(), employees.end(),
            [](Employee* a, Employee* b) {
                return a->calculateSalary() > b->calculateSalary();  // > для убывания
            });
    }

    // ===================================================
    // ВЫВОД ВСЕХ СОТРУДНИКОВ
    // ===================================================
    void printAll() const {
        cout << "\n=== Employee List ===" << endl;
        for (Employee* emp : employees) {
            emp->getInfo();  // Полиморфный вызов - вызывается метод нужного класса
        }
        cout << "=====================" << endl;
    }
};

#endif