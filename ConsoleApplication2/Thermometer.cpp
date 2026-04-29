#include "Thermometer.h"
#include <iostream>
#include <cstring>
#include <iomanip>
using namespace std;

// 1. КОНСТРУКТОР ПО УМОЛЧАНИЮ (без параметров)
Thermometer::Thermometer()
{
    celsius = 0.0;                             // Температура 0°C
    location = new char[30];                   // Выделяем память для строки
    strcpy_s(location, 30, "Неизвестно");      // Устанавливаем место по умолчанию
}

// 2. КОНСТРУКТОР С ОДНИМ ПАРАМЕТРОМ (только температура)
Thermometer::Thermometer(double tempCelsius)
{
    celsius = tempCelsius;                     // Устанавливаем переданную температуру
    location = new char[30];                   // Выделяем память
    strcpy_s(location, 30, "Неизвестно");      // Место - "Неизвестно"
}

// 3. КОНСТРУКТОР С ДВУМЯ ПАРАМЕТРАМИ (место и температура)
Thermometer::Thermometer(const char* place, double tempCelsius)
{
    celsius = tempCelsius;                     // Устанавливаем температуру

    size_t len = strlen(place);                // Узнаём длину строки места
    location = new char[len + 10];             // Выделяем память с запасом
    strcpy_s(location, len + 10, place);       // Копируем место
}

// ДЕСТРУКТОР
Thermometer::~Thermometer()
{
    delete[] location;  // Освобождаем память, выделенную под строку location
}

// Геттер для температуры в Цельсиях
double Thermometer::getCelsius()
{
    return celsius;
}

// КОНВЕРТАЦИЯ Цельсий → Фаренгейт
// Формула: F = C × 9/5 + 32
double Thermometer::getFahrenheit()
{
    return celsius * 9.0 / 5.0 + 32;
}

// Вывод информации о термометре
void Thermometer::printInfo()
{
    cout << "Место измерения: " << location << endl;
    cout << "Температура: " << fixed << setprecision(1)
        << celsius << "°C / " << getFahrenheit() << "°F" << endl;
}

// ВНИМАНИЕ: НЕТ main()!