#include "StringMemory.h"
#include <iostream>

// Задача 7: Динамическое изменение конца строки
void StringMemory::buildAndShrink() {
    buffer = "";
    // Цикл добавляет буквы от A до Z в конец строки
    for (char c = 'A'; c <= 'Z'; ++c) {
        buffer.push_back(c); // .push_back(символ) прикрепляет один символ в самый конец
    }
    std::cout << "Полная строка: " << buffer << std::endl;

    // Цикл удаляет последние 5 символов строки
    for (int i = 0; i < 5; ++i) {
        if (!buffer.empty()) {
            buffer.pop_back(); // .pop_back() удаляет ровно один символ с конца строки
        }
    }
    std::cout << "После удаления 5 символов: " << buffer << std::endl;
}

// Задача 9: Очищение памяти
void StringMemory::clearAndVerify() {
    std::string msg = "Это важное сообщение";
    std::cout << "Исходная длина: " << msg.length() << std::endl;

    msg.clear(); // .clear() полностью опустошает строку, сбрасывая ее длину до 0
    std::cout << "Строка очищена. Длина: " << msg.length() << std::endl;

    // .empty() возвращает true (истина), если строка пустая, и false, если в ней есть символы
    std::cout << "Строка пуста: " << (msg.empty() ? "да" : "нет") << std::endl;
}
