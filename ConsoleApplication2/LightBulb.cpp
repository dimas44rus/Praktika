#include "LightBulb.h"     // Подключаем описание класса
#include <iostream>        // Для cout
using namespace std;

// Реализация метода turnOn
void LightBulb::turnOn()
{
    isOn = true;   // Устанавливаем состояние "включено"
    cout << "Лампочка включена" << endl;
}

// Реализация метода turnOff
void LightBulb::turnOff()
{
    isOn = false;  // Устанавливаем состояние "выключено"
    cout << "Лампочка выключена" << endl;
}

// Реализация метода toggle
void LightBulb::toggle()
{
    // Оператор "!" (логическое НЕ) инвертирует значение:
    // если isOn был true, становится false, и наоборот
    isOn = !isOn;

    // Тернарный оператор "? :" - сокращённая форма if-else
    // (isOn ? "ВКЛ" : "ВЫКЛ") означает:
    // если isOn true, то "ВКЛ", иначе "ВЫКЛ"
    cout << "Лампочка переключена -> " << (isOn ? "ВКЛ" : "ВЫКЛ") << endl;
}

// Реализация метода getState
const char* LightBulb::getState()
{
    // Возвращаем строку "ON" если включена, "OFF" если выключена
    return isOn ? "ON" : "OFF";
}

// ВНИМАНИЕ: НЕТ main() - только методы класса!