#include "Product.h"      // Подключаем описание нашего класса
#include <iostream>       // Для работы с cout (вывод на экран)
#include <iomanip>        // Для форматирования: fixed, setprecision
using namespace std;      // Чтобы писать cout вместо std::cout

// Реализация метода print
// Синтаксис: тип_возврата ИмяКласса::ИмяМетода(параметры)
void Product::print()
{
    // Выводим название товара
    cout << "Товар: " << name << endl;

    // Выводим количество (endl - перевод строки)
    cout << "Количество: " << quantity << " шт." << endl;

    // fixed - выводить числа с фиксированной точкой (не в научном формате)
    // setprecision(2) - два знака после запятой
    cout << "Цена: " << fixed << setprecision(2) << price << " руб." << endl;
}

// Реализация метода getTotalCost
double Product::getTotalCost()
{
    // Общая стоимость = количество × цена
    return quantity * price;
}

// ВНИМАНИЕ: Здесь НЕТ функции main()!
// main() будет только в одном файле - main.cpp