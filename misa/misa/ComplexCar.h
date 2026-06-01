#pragma once
#include <string>

// Независимый базовый класс "Колеса"
class Wheels {
protected:
    int wheelCount;
public:
    Wheels(int count);
    void showWheels() const;
};

// Независимый базовый класс "Двигатель"
class Engine {
protected:
    int horsepower;
public:
    Engine(int hp);
    void showEngine() const;
};

// Независимый базовый класс "Двери"
class Doors {
protected:
    int doorCount;
public:
    Doors(int count);
    void showDoors() const;
};

// Класс "Автомобиль", использующий механизм множественного наследования.
// Он объединяет в себе свойства и методы всех трех базовых классов.
class ComplexCar : public Wheels, public Engine, public Doors {
private:
    std::string model; // Собственное уникальное свойство автомобиля
public:
    ComplexCar(std::string m, int w, int hp, int d);

    // Метод, который комбинирует вызовы функций из разных базовых классов
    void showCarInfo() const;
};
