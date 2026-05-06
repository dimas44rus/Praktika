#pragma warning(disable: 4996)
#include "Array.h"
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);

    // SetConsoleCP - устанавливает кодировку для ВВОДА текста из консоли
    // CP_UTF8 - чтобы корректно читать русские буквы, введённые пользователем
    SetConsoleCP(CP_UTF8);


    std::cout << "========== Задание 2: Класс Array ==========\n\n";

    // Тест 1: Создание и заполнение
    std::cout << "--- Тест 1: Создание массива на 5 элементов ---\n";
    Array arr(5);
    arr.fill();
    arr.display();

    // Тест 2: Минимум и максимум (теперь работает)
    std::cout << "\n--- Тест 2: Минимум и максимум ---\n";
    std::cout << "Минимум: " << arr.getMin() << std::endl;
    std::cout << "Максимум: " << arr.getMax() << std::endl;

    // Тест 3: Сортировка
    std::cout << "\n--- Тест 3: Сортировка массива ---\n";
    arr.sortArray();
    arr.display();

    // Тест 4: Изменение размера
    std::cout << "\n--- Тест 4: Изменение размера до 8 ---\n";
    arr.resize(8);
    arr.display();

    // Тест 5: Конструктор копирования
    std::cout << "\n--- Тест 5: Конструктор копирования ---\n";
    Array arr2 = arr;
    arr2.display();

    // Тест 6: Оператор []
    std::cout << "\n--- Тест 6: Оператор индексации ---\n";
    std::cout << "Первый элемент: " << arr[0] << std::endl;

    // Тест 7: Подсчет экземпляров
    std::cout << "\n--- Тест 7: Подсчет экземпляров ---\n";
    std::cout << "Создано объектов Array: " << Array::getInstanceCount() << std::endl;

    system("pause");
    return 0;
}