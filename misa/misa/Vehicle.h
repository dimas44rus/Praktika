#pragma once
#include <string>

// Абстрактный базовый класс для иерархии транспортных средств.
// Демонстрирует Абстракцию и Инкапсуляцию.
class Vehicle {
protected:
    // Данные защищены модификатором protected, чтобы производные классы имели к ним доступ напрямую
    std::string name;   // Название ТС
    double speed;       // Скорость в км/ч
    double costPerKm;   // Базовая стоимость за 1 км пути

public:
    // Конструктор инициализации
    Vehicle(std::string n, double s, double c);

    // Виртуальный деструктор обязателен для базовых классов при полиморфизме,
    // чтобы объекты производных классов корректно удалялись через указатель на базовый класс
    virtual ~Vehicle() = default;

    // Геттер для получения имени ТС (Инкапсуляция)
    std::string getName() const;

    // Виртуальная функция для расчета времени в пути
    virtual double calculateTime(double distance) const;

    // Виртуальная функция для расчета стоимости (будет переопределяться)
    virtual double calculateCost(double distance, double weight, int passengers) const;
};

// Производный класс "Автомобиль" (Наследование)
class Car : public Vehicle {
public:
    Car();
};

// Производный класс "Велосипед" (Наследование)
class Bicycle : public Vehicle {
public:
    Bicycle();

    // Переопределение метода (Полиморфизм) — у велосипеда свои жесткие ограничения по весу
    double calculateCost(double distance, double weight, int passengers) const override;
};

// Производный класс "Повозка" (Наследование)
class Cart : public Vehicle {
public:
    Cart();
};
