#include "StringValidator.h"
#include <iostream>

// Задача 8: Безопасное сравнение строк
void StringValidator::checkPassword() {
    std::string pass1, pass2;
    std::cout << "Введите пароль: ";
    std::cin >> pass1;
    std::cout << "Подтвердите пароль: ";
    std::cin >> pass2;

    // Метод .compare() лексикографически сравнивает строки. 
    // Он возвращает 0, если строки абсолютно идентичны.
    if (pass1.compare(pass2) == 0) {
        std::cout << "Доступ разрешён" << std::endl;
    }
    else {
        std::cout << "Доступ запрещён: пароли не совпадают" << std::endl;
        // Дополнительная проверка длин строк для информативности пользователя
        if (pass1.length() == pass2.length()) {
            std::cout << "(Длины совпадают, но символы различаются)" << std::endl;
        }
    }
}
