#define NOMINMAX
#pragma warning(disable: 4996)

#include "Human.h"
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);

    // SetConsoleCP - устанавливает кодировку для ВВОДА текста из консоли
    // CP_UTF8 - чтобы корректно читать русские буквы, введённые пользователем
    SetConsoleCP(CP_UTF8);

    std::cout << "========== ЗАДАНИЕ 3: КЛАСС ЧЕЛОВЕК ==========\n\n";

    // ===== ТЕСТ 1: Конструктор с параметрами =====
    std::cout << "--- Тест 1: Конструктор с параметрами ---\n";
    Date birth1(15, 5, 1990);
    Human h1(1, "Иванов", "Иван", "Иванович", birth1);
    h1.display();
    std::cout << std::endl;

    // ===== ТЕСТ 2: Конструктор по умолчанию (делегирование) =====
    std::cout << "--- Тест 2: Конструктор по умолчанию (делегирование) ---\n";
    Human h2;
    h2.display();
    std::cout << std::endl;

    // ===== ТЕСТ 3: Конструктор копирования =====
    std::cout << "--- Тест 3: Конструктор копирования ---\n";
    Human h3 = h1;
    h3.display();
    std::cout << std::endl;

    // ===== ТЕСТ 4: Сеттеры =====
    std::cout << "--- Тест 4: Изменение данных через сеттеры ---\n";
    h2.setId(2);
    h2.setSurname("Петров");
    h2.setName("Петр");
    h2.setPatronymic("Петрович");
    Date newBirth(20, 10, 1985);
    h2.setBirthDate(newBirth);
    h2.display();
    std::cout << std::endl;

    // ===== ТЕСТ 5: Геттеры =====
    std::cout << "--- Тест 5: Получение данных через геттеры ---\n";
    std::cout << "ID: " << h1.getId() << std::endl;
    std::cout << "Фамилия: " << h1.getSurname() << std::endl;
    std::cout << "Имя: " << h1.getName() << std::endl;
    std::cout << "Отчество: " << h1.getPatronymic() << std::endl;
    std::cout << "Дата рождения: ";
    h1.getBirthDate().output();
    std::cout << std::endl << std::endl;

    // ===== ТЕСТ 6: Ввод с клавиатуры =====
    std::cout << "--- Тест 6: Создание человека с вводом с клавиатуры ---\n";
    int id;
    char surname[50], name[50], patronymic[50];
    Date birthDate;

    std::cout << "Введите ID: ";
    std::cin >> id;
    std::cin.ignore();
    std::cout << "Введите фамилию: ";
    std::cin.getline(surname, 50);
    std::cout << "Введите имя: ";
    std::cin.getline(name, 50);
    std::cout << "Введите отчество: ";
    std::cin.getline(patronymic, 50);
    birthDate.input();

    Human h4(id, surname, name, patronymic, birthDate);
    h4.display();
    std::cout << std::endl;

    // ===== ТЕСТ 7: Оператор присваивания =====
    std::cout << "--- Тест 7: Оператор присваивания ---\n";
    Human h5;
    h5 = h1;
    h5.display();
    std::cout << std::endl;

    // ===== ТЕСТ 8: Подсчет экземпляров =====
    std::cout << "--- Тест 8: Подсчет созданных экземпляров ---\n";
    std::cout << "Всего создано объектов Human: " << Human::getTotalInstances() << std::endl;
    std::cout << std::endl;

    // ===== ТЕСТ 9: Массив объектов =====
    std::cout << "--- Тест 9: Массив из 3 объектов ---\n";
    Human* people = new Human[3];
    std::cout << "Массив создан\n";
    delete[] people;
    std::cout << "Массив удален\n";
    std::cout << std::endl;

    // ===== Финальный подсчет =====
    std::cout << "--- Финальный подсчет ---\n";
    std::cout << "Осталось объектов Human: " << Human::getTotalInstances() << std::endl;

    std::cout << "\n========== КОНЕЦ ТЕСТИРОВАНИЯ ==========\n";

    system("pause");
    return 0;
}