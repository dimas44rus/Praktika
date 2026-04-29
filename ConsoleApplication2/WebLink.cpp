#include "WebLink.h"      // Подключаем описание класса
#include <iostream>       // Для cout
#include <cstring>        // Для работы со строками: strlen, strcpy_s
using namespace std;

// КОНСТРУКТОР
WebLink::WebLink(const char* linkUrl, const char* linkDesc)
{
    // Шаг 1: выделяем память под URL
    // strlen - вычисляет длину строки (без учёта нуль-терминатора)
    size_t urlLen = strlen(linkUrl);           // Узнаём длину URL
    url = new char[urlLen + 10];               // Выделяем память (+10 запас)
    strcpy_s(url, urlLen + 10, linkUrl);       // Копируем строку в выделенную память

    // Шаг 2: выделяем память под описание
    size_t descLen = strlen(linkDesc);         // Узнаём длину описания
    description = new char[descLen + 10];      // Выделяем память (+10 запас)
    strcpy_s(description, descLen + 10, linkDesc);  // Копируем строку
}

// ДЕСТРУКТОР
WebLink::~WebLink()
{
    // Освобождаем динамическую память
    // delete[] - удаляет массив (важно! не просто delete, а delete[])
    // Если забыть вызвать delete[], произойдёт УТЕЧКА ПАМЯТИ
    // Программа будет потреблять всё больше памяти при каждом создании объекта
    delete[] url;           // Освобождаем память, выделенную под URL
    delete[] description;   // Освобождаем память, выделенную под описание
}

// Метод print - вывод информации о ссылке
void WebLink::print()
{
    cout << "Описание: " << description << endl;
    cout << "Адрес: " << url << endl;
}

// ВНИМАНИЕ: НЕТ main()!