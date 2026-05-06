#ifndef STRING_H
#define STRING_H

#include <iostream>

class String {
private:
    char* str;          // указатель на динамическую строку
    size_t length;      // длина строки
    static int instanceCount;  // счетчик созданных экземпляров

public:
    // Конструкторы
    String();                                    // по умолчанию (80 символов)
    explicit String(size_t size);                // произвольный размер
    String(const char* input);                   // инициализация строкой
    String(const String& other);                 // конструктор копирования

    // Деструктор
    ~String();

    // Методы
    void input();                                // ввод с клавиатуры
    void output() const;                         // вывод на экран

    // Геттеры
    const char* getString() const;
    size_t getLength() const;
    static int getInstanceCount();

    // Оператор присваивания (для полноты)
    String& operator=(const String& other);
};

#endif