#include "String.h"
#include <iostream>
#include <windows.h>

using namespace std;

int main() {
    SetConsoleOutputCP(CP_UTF8);

    // SetConsoleCP - устанавливает кодировку для ВВОДА текста из консоли
    // CP_UTF8 - чтобы корректно читать русские буквы, введённые пользователем
    SetConsoleCP(CP_UTF8);

    cout << "\n========== Тест 1: Конструктор по умолчанию ==========" << endl;
    String s1;
    s1.output();

    cout << "\n========== Тест 2: Конструктор с размером ==========" << endl;
    String s2(10);
    s2.output();

    cout << "\n========== Тест 3: Конструктор из C-строки ==========" << endl;
    String s3("Привет, мир!");
    s3.output();

    cout << "\n========== Тест 4: Конструктор копирования ==========" << endl;
    String s4(s3);
    s4.output();

    cout << "\n========== Тест 5: Ввод с клавиатуры ==========" << endl;
    String s5;
    cout << "Введите строку для s5: ";
    s5.input();
    s5.output();

    cout << "\n========== Тест 6: Проверка счетчика экземпляров ==========" << endl;
    cout << "Всего создано экземпляров String: " << String::getInstanceCount() << endl;

    cout << "\n========== Тест 7: Работа с геттерами ==========" << endl;
    cout << "Содержимое s3: " << s3.getString() << endl;
    cout << "Длина s3: " << s3.getLength() << endl;

    cout << "\n========== Тест 8: Оператор присваивания ==========" << endl;
    String s6;
    s6 = s3;
    s6.output();

    cout << "\n========== Тест 9: Создание массива объектов ==========" << endl;
    String* arr = new String[3];
    delete[] arr;

    cout << "\n========== Тест 10: Финальный подсчет ==========" << endl;
    cout << "Осталось экземпляров String: " << String::getInstanceCount() << endl;

    cout << "\n========== Конец программы ==========" << endl;

    return 0;
}