#include <iostream>
#include <vector>
#include <memory>
#include <clocale>
#include <Windows.h>

// Подключение созданных заголовочных файлов всех модулей
#include "Vehicle.h"
#include "ComplexCar.h"
#include "Pet.h"
#include "Employer.h"

// Запуск демонстрации Задания №1
void runTask1() {
    std::cout << "\n--- Задание 1: Транспорт ---\n";

    // Использование ПОЛИМОРФИЗМА: вектор хранит умные указатели на базовый тип Vehicle.
    // Это позволяет обрабатывать разные объекты (Car, Bicycle, Cart) одинаковым образом.
    std::vector<std::unique_ptr<Vehicle>> vehicles;
    vehicles.push_back(std::make_unique<Car>());
    vehicles.push_back(std::make_unique<Bicycle>());
    vehicles.push_back(std::make_unique<Cart>());

    double dist = 50.0;     // Заданная дистанция 50 км
    double weight = 20.0;   // Груз 20 кг
    int passengers = 1;     // 1 пассажир

    std::cout << "Дистанция: " << dist << " км, Груз: " << weight << " кг, Пассажиры: " << passengers << "\n\n";

    // Цикл полиморфно вызывает нужные методы в зависимости от реального типа объекта
    for (const auto& v : vehicles) {
        double time = v->calculateTime(dist);
        double cost = v->calculateCost(dist, weight, passengers);

        std::cout << "Транспорт: " << v->getName() << "\n";
        std::cout << "Время в пути: " << time << " ч.\n";

        if (cost < 0) {
            std::cout << "Стоимость: невозможно перевезти такой груз/пассажиров.\n";
        }
        else {
            std::cout << "Стоимость: " << cost << " руб.\n";
        }
        std::cout << "---------------------\n";
    }
}

// Запуск демонстрации Задания №2
void runTask2() {
    std::cout << "\n--- Задание 2: Множественное наследование ---\n";
    // Создаем объект сложного автомобиля, передавая параметры для всех его базовых частей
    ComplexCar myCar("Tesla Model S", 4, 670, 5);
    myCar.showCarInfo();
}

// Запуск демонстрации Задания №3
void runTask3() {
    std::cout << "\n--- Задание 3: Домашние животные ---\n";

    // Полиморфный контейнер для хранения различных домашних животных
    std::vector<std::unique_ptr<Pet>> pets;
    pets.push_back(std::make_unique<Dog>("Рекс", "Преданный, любит играть в мяч"));
    pets.push_back(std::make_unique<Cat>("Мурка", "Ленивая, часто спит на солнце"));
    pets.push_back(std::make_unique<Parrot>("Кеша", "Громкий, повторяет слова"));
    pets.push_back(std::make_unique<Hamster>("Хомка", "Запасливый, постоянно ест"));

    // Для каждого животного вызывается своя цепочка виртуальных функций
    for (const auto& pet : pets) {
        pet->Type();          // Специфично для каждого класса
        pet->Show();          // Базовый метод
        pet->ShowFeatures();  // Базовый метод
        pet->Sound();         // Специфично для каждого класса
        std::cout << "---------------------\n";
    }
}

// Запуск демонстрации Задания №4
void runTask4() {
    std::cout << "\n--- Задание 4: Служащие ---\n";

    // Еще один пример динамического полиморфизма
    std::vector<std::unique_ptr<Employer>> staff;
    staff.push_back(std::make_unique<President>("Илон Маск", 1, "SpaceX"));
    staff.push_back(std::make_unique<Manager>("Алексей Иванов", 120000, 8));
    staff.push_back(std::make_unique<Worker>("Петр Петров", 60000, "Сварщик 5-го разряда"));

    // Вызов виртуальной функции Print() подстраивается под тип сотрудника
    for (const auto& employee : staff) {
        employee->Print();
        std::cout << "---------------------\n";
    }
}

// Главный цикл текстового интерфейса
int main() {
    // Включение поддержки русского языка в консоли (Windows/Linux)
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    int choice = -1;
    while (choice != 0) {
        std::cout << "\n=========================================\n";
        std::cout << "       ГЛАВНОЕ МЕНЮ ПРАКТИКИ ООП        \n";
        std::cout << "=========================================\n";
        std::cout << "1. Задание №1 (Транспортные средства)\n";
        std::cout << "2. Задание №2 (Множественное наследование автомобиля)\n";
        std::cout << "3. Задание №3 (Домашние животные)\n";
        std::cout << "4. Задание №4 (Класс Employer и иерархия)\n";
        std::cout << "0. Выход из программы\n";
        std::cout << "=========================================\n";
        std::cout << "Выберите номер задания: ";

        // Защита от некорректного ввода (например, если ввели букву вместо цифры)
        if (!(std::cin >> choice)) {
            std::cout << "Ошибка ввода! Введите число.\n";
            std::cin.clear(); // Сброс флага ошибки
            std::cin.ignore(10000, '\n'); // Очистка буфера ввода
            continue;
        }

        switch (choice) {
        case 1: runTask1(); break;
        case 2: runTask2(); break;
        case 3: runTask3(); break;
        case 4: runTask4(); break;
        case 0: std::cout << "Программа завершена.\n"; break;
        default: std::cout << "Неверный пункт меню. Попробуйте снова.\n"; break;
        }
    }
    return 0;
}
