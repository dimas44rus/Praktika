#include "Vehicle.h"

// Конструктор базового класса инициализирует защищенные поля
Vehicle::Vehicle(std::string n, double s, double c) : name(n), speed(s), costPerKm(c) {}

std::string Vehicle::getName() const { return name; }

// Реализация базового расчета времени: t = S / v
double Vehicle::calculateTime(double distance) const {
    return distance / speed;
}

// Базовая формула стоимости: расстояние * тариф + надбавка за вес и пассажиров
double Vehicle::calculateCost(double distance, double weight, int passengers) const {
    return (distance * costPerKm) + (weight * 0.1) + (passengers * 50);
}

// Конструкторы дочерних классов вызывают конструктор базового класса с фиксированными параметрами
Car::Car() : Vehicle("Автомобиль", 90.0, 15.0) {}

Bicycle::Bicycle() : Vehicle("Велосипед", 15.0, 0.0) {}

// Специфическая реализация для велосипеда: груз > 30кг или наличие пассажиров делают поездку невозможной (-1)
double Bicycle::calculateCost(double distance, double weight, int passengers) const {
    if (weight > 30 || passengers > 0) return -1;
    return 0; // На велосипеде везти бесплатно (нет расхода топлива)
}

Cart::Cart() : Vehicle("Повозка", 10.0, 5.0) {}
