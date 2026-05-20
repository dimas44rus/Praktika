#include <iostream>
#include "StringBasic.h"
#include "StringModifier.h"
#include "StringMemory.h"
#include "StringValidator.h"
#include "Windows.h"

int main() {
    // Настройка локали для корректного отображения кириллицы в консоли Windows
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::cout << "=== СТАРТ ООП ЛАБОРАТОРНОЙ РАБОТЫ (КЛАСС STRING) ===\n" << std::endl;

    // Создание объектов управляющих классов
    StringBasic basicObj;
    StringModifier modifierObj;
    StringMemory memoryObj;
    StringValidator validatorObj;

    // Вызовы методов первой группы (Базовые операции)
    std::cout << "[Раздел 1: Базовые методы]" << std::endl;
    basicObj.greetAndAnalyze();
    std::cout << std::endl;
    basicObj.readFullName();
    std::cout << std::endl;
    basicObj.findSubstring();
    std::cout << "\n-----------------------------------------\n" << std::endl;

    // Вызовы методов второй группы (Модификация)
    std::cout << "[Раздел 2: Модификация текста]" << std::endl;
    modifierObj.capitalizeWords();
    std::cout << std::endl;
    modifierObj.insertAndReplace();
    std::cout << std::endl;
    modifierObj.extractAndErase();
    std::cout << "\n-----------------------------------------\n" << std::endl;

    // Вызовы методов третьей группы (Память)
    std::cout << "[Раздел 3: Буферы и Очистка памяти]" << std::endl;
    memoryObj.buildAndShrink();
    std::cout << std::endl;
    memoryObj.clearAndVerify();
    std::cout << "\n-----------------------------------------\n" << std::endl;

    // Вызов валидатора (Сравнение строк)
    std::cout << "[Раздел 4: Проверка валидности]" << std::endl;
    validatorObj.checkPassword();

    std::cout << "\n=========================================" << std::endl;
    std::cout << "Все классы успешно отработали." << std::endl;

    return 0;
}
