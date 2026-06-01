#pragma once
#include <string>

// Абстрактный базовый класс для домашних питомцев
class Pet {
protected:
    std::string name;       // Имя животного
    std::string character;  // Его характеристики (характер, повадки)
public:
    // Конструктор для установки имени и характеристик
    Pet(std::string n, std::string c);
    virtual ~Pet() = default;

    // Чисто виртуальные функции (делают класс абстрактным).
    // Каждый потомок обязан их реализовать.
    virtual void Sound() const = 0; // Воспроизведение звука
    virtual void Type() const = 0;  // Отображение подвида

    // Обычные виртуальные функции с базовой реализацией
    virtual void Show() const;          // Показ имени
    virtual void ShowFeatures() const;  // Показ характеристик
};

// Производный класс Собака
class Dog : public Pet {
public:
    Dog(std::string n, std::string c);
    void Sound() const override;
    void Type() const override;
};

// Производный класс Кошка
class Cat : public Pet {
public:
    Cat(std::string n, std::string c);
    void Sound() const override;
    void Type() const override;
};

// Производный класс Попугай
class Parrot : public Pet {
public:
    Parrot(std::string n, std::string c);
    void Sound() const override;
    void Type() const override;
};

// Производный класс Хомяк
class Hamster : public Pet {
public:
    Hamster(std::string n, std::string c);
    void Sound() const override;
    void Type() const override;
};
