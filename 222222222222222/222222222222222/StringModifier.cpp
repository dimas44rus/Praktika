#include "StringModifier.h"
#include <iostream>
#include <cctype> // Необходимо для функций toupper и isspace

// Задача 4: Изменение регистра первой буквы каждого слова
void StringModifier::capitalizeWords() {
    std::string myString;
    std::cout << "Вход: ";
    std::getline(std::cin >> std::ws, myString);

    bool newWord = true; // Флаг: указывает, что сейчас начнется новое слово
    // range-based for: символ 'c' передается по ссылке (&), чтобы менять его внутри строки
    for (char& c : myString) {
        if (std::isspace(c)) {
            newWord = true; // Если встретили пробел, значит следующее за ним — новое слово
        }
        else if (newWord) {
            c = std::toupper(c); // std::toupper переводит символ в заглавный регистр
            newWord = false;     // Сбрасываем флаг, пока слово не закончится
        }
    }
    std::cout << "Выход: " << myString << std::endl;
}

// Задача 5: Вставка и замена
void StringModifier::insertAndReplace() {
    std::string str = "Сегодня хорошая погода.";

    size_t posInsert = str.find("хорошая");
    if (posInsert != std::string::npos) {
        // .insert(индекс, "текст") вставляет подстроку в указанную позицию
        str.insert(posInsert, "очень ");
    }
    std::cout << "После insert: " << str << std::endl;

    size_t posReplace = str.find("хорошая");
    if (posReplace != std::string::npos) {
        // .replace(индекс, длина, "текст") удаляет 7 символов с индекса и вставляет новое слово
        str.replace(posReplace, 7, "прекрасная");
    }
    std::cout << "После replace: " << str << std::endl;
}

// Задача 6: Вырезание фрагмента и удаление
void StringModifier::extractAndErase() {
    std::string str = "Код ошибки: 404 - Не найдено";
    size_t colonPos = str.find(":");

    if (colonPos != std::string::npos) {
        // .substr(индекс, количество) вырезает кусок строки (начиная через 2 символа после двоеточия, длина 3)
        std::string errorCode = str.substr(colonPos + 2, 3);
        std::cout << "Извлечённый код: " << errorCode << std::endl;

        size_t dashPos = str.find(" - ");
        if (dashPos != std::string::npos) {
            // .erase(индекс) удаляет всё содержимое строки, начиная с указанного индекса и до самого конца
            str.erase(dashPos);
        }
        std::cout << "Изменённая строка: " << str << std::endl;
    }
}
