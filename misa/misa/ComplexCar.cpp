#include "ComplexCar.h"
#include <iostream>

// Реализация методов для класса Wheels
Wheels::Wheels(int count) : wheelCount(count) {}
void Wheels::showWheels() const { std::cout << "Количество колес: " << wheelCount << "\n"; }

// Реализация методов для класса Engine
Engine::Engine(int hp) : horsepower(hp) {}
void Engine::showEngine() const { std::cout << "Мощность двигателя: " << horsepower << " л.с.\n"; }

// Реализация методов для класса Doors
Doors::Doors(int count) : doorCount(count) {}
void Doors::showDoors() const { std::cout << "Количество дверей: " << doorCount << "\n"; }

// Конструктор ComplexCar обязан явно вызвать конструкторы всех родительских классов
ComplexCar::ComplexCar(std::string m, int w, int hp, int d)
    : Wheels(w), Engine(hp), Doors(d), model(m) {
}

// Демонстрация сборки объекта из компонентов родительских классов
void ComplexCar::showCarInfo() const {
    std::cout << "Модель автомобиля: " << model << "\n";
    showWheels(); // Вызов метода родительского класса Wheels
    showEngine(); // Вызов метода родительского класса Engine
    showDoors();  // Вызов метода родительского класса Doors
}
