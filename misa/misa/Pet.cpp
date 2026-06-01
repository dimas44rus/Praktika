#include "Pet.h"
#include <iostream>

// Базовая реализация общих для всех животных полей и методов
Pet::Pet(std::string n, std::string c) : name(n), character(c) {}
void Pet::Show() const { std::cout << "Имя: " << name << "\n"; }
void Pet::ShowFeatures() const { std::cout << "Характер/Особенности: " << character << "\n"; }

// Реализация уникального поведения для Собаки
Dog::Dog(std::string n, std::string c) : Pet(n, c) {}
void Dog::Sound() const { std::cout << "Звук: Гав-гав!\n"; }
void Dog::Type() const { std::cout << "Подвид: Собака домашняя\n"; }

// Реализация уникального поведения для Кошки
Cat::Cat(std::string n, std::string c) : Pet(n, c) {}
void Cat::Sound() const { std::cout << "Звук: Мяу-мяу!\n"; }
void Cat::Type() const { std::cout << "Подвид: Кошка домашняя\n"; }

// Реализация уникального поведения для Попугая
Parrot::Parrot(std::string n, std::string c) : Pet(n, c) {}
void Parrot::Sound() const { std::cout << "Звук: Кеша хороший! Пиастры!\n"; }
void Parrot::Type() const { std::cout << "Подвид: Попугай волнистый\n"; }

// Реализация уникального поведения для Хомяка
Hamster::Hamster(std::string n, std::string c) : Pet(n, c) {}
void Hamster::Sound() const { std::cout << "Звук: Фыр-фыр / Хрум-хрум\n"; }
void Hamster::Type() const { std::cout << "Подвид: Хомяк сирийский\n"; }
