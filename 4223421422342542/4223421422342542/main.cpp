#include <iostream>
#include <string>
#include "SmartArray.hpp" // Подключаем наш класс

int main() {
    // 1. Работа с целыми числами
    SmartArray<int> intArray;
    for (int i = 1; i <= 10; i++) {
        intArray.push_back(i * 10);
    }
    std::cout << "Size: " << intArray.size() << std::endl;

    // Поиск элемента
    int index = intArray.find(50);
    if (index != -1) {
        std::cout << "Found 50 at index: " << index << std::endl;
    }
    else {
        std::cout << "50 not found" << std::endl;
    }

    // Тест итератора (вывод всех элементов)
    std::cout << "Elements: ";
    for (int val : intArray) {
        std::cout << val << " ";
    }
    std::cout << std::endl << std::endl;

    // 2. Работа со строками
    SmartArray<std::string> strArray;
    strArray.push_back("Hello");
    strArray.push_back("World");
    strArray.push_back("C++");

    std::cout << "String array size: " << strArray.size() << std::endl;
    std::cout << "Last element: " << strArray.back() << std::endl;

    return 0;
}
