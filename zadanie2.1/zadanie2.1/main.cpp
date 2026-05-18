// ===================================================
// ПОДКЛЮЧЕНИЕ ЗАГОЛОВОЧНЫХ ФАЙЛОВ
// ===================================================
#include <iostream>
#include <string>
#include "Shapes.h"       // Задание 2.1 - геометрические фигуры
#include "Department.h"   // Задание 2.2 - сотрудники и отдел

using namespace std;

// ===================================================
// ВСПОМОГАТЕЛЬНАЯ ФУНКЦИЯ ДЛЯ КРАСИВОГО ВЫВОДА
// ===================================================
// @param title - текст заголовка
// Выводит строку из 60 знаков "=", затем заголовок, затем ещё одну строку
void printHeader(const string& title) {
    cout << "\n" << string(60, '=') << endl;
    cout << "  " << title << endl;
    cout << string(60, '=') << endl;
}

// ===================================================
// ЗАДАНИЕ 2.1: ДЕМОНСТРАЦИЯ ГЕОМЕТРИЧЕСКИХ ФИГУР
// ===================================================
void demoShapes() {
    printHeader("Task 2.1: Geometric Shapes");

    try {
        // ===================================================
        // ПОЛИМОРФНЫЙ МАССИВ УКАЗАТЕЛЕЙ
        // ===================================================
        // Массив указателей на базовый класс Shape
        // Может хранить указатели на объекты ЛЮБЫХ производных классов
        // Это и есть полиморфизм - один интерфейс, много реализаций
        Shape* shapes[3];

        // Создаём объекты разных типов
        shapes[0] = new Circle(5);        // Круг радиусом 5
        shapes[1] = new Rectangle(3, 4);  // Прямоугольник 3×4
        shapes[2] = new Triangle(3, 4, 5); // Прямоугольный треугольник (египетский)

        cout << "Information about figures:" << endl;
        for (int i = 0; i < 3; i++) {
            cout << i + 1 << ". ";
            shapes[i]->print();  // Полиморфный вызов - определяется тип объекта во время выполнения
        }

        // Статический метод - можно вызывать без объекта, через класс
        cout << "\nTotal figures created: " << Shape::getCount() << endl;

        // ===================================================
        // ОСВОБОЖДЕНИЕ ПАМЯТИ
        // ===================================================
        // Виртуальный деструктор гарантирует правильное удаление объектов
        for (int i = 0; i < 3; i++) {
            delete shapes[i];  // Вызывается правильный деструктор (Circle, Rectangle или Triangle)
        }

        cout << "After deletion, remaining figures: " << Shape::getCount() << endl;

    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

// ===================================================
// ЗАДАНИЕ 2.2: ДЕМОНСТРАЦИЯ ИЕРАРХИИ СОТРУДНИКОВ
// ===================================================
void demoEmployees() {
    printHeader("Task 2.2: Employee Hierarchy");

    try {
        // ===================================================
        // СОЗДАНИЕ ОТДЕЛА И ДОБАВЛЕНИЕ СОТРУДНИКОВ
        // ===================================================
        Department dept;

        // Добавляем сотрудников разных типов
        // Все они хранятся как Employee* (указатель на базовый класс)
        dept.addEmployee(new Manager("Ivan Petrov", 1, 50000, 20, 5));
        dept.addEmployee(new Developer("Anna Sidorova", 2, 60000, "C++", 3));
        dept.addEmployee(new Developer("Sergey Ivanov", 3, 55000, "Python", 2));
        dept.addEmployee(new Intern("Maria Kuznetsova", 4, 30000, true));
        dept.addEmployee(new Manager("Olga Smirnova", 5, 52000, 15, 3));

        // Выводим всех сотрудников
        dept.printAll();

        // Общая зарплата
        cout << "\nTotal department salary: " << dept.getTotalSalary() << " rub." << endl;

        // Сотрудник с максимальной зарплатой
        Employee* maxSalary = dept.getMaxSalaryEmployee();
        if (maxSalary) {
            cout << "Employee with maximum salary: ";
            maxSalary->getInfo();
        }

        // ===================================================
        // СОРТИРОВКА СОТРУДНИКОВ
        // ===================================================
        cout << "\n--- After salary sorting (descending) ---" << endl;
        dept.sortBySalary();  // Сортировка по убыванию зарплаты
        dept.printAll();

        // ===================================================
        // УДАЛЕНИЕ СОТРУДНИКА
        // ===================================================
        cout << "\n--- Deleting employee with ID 3 ---" << endl;
        dept.removeEmployee(3);  // Удаляем Сергея Иванова
        dept.printAll();

        // Итоговая зарплата после удаления
        cout << "\nFinal total salary: " << dept.getTotalSalary() << " rub." << endl;

    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

// ===================================================
// ГЛАВНАЯ ФУНКЦИЯ (ТОЧКА ВХОДА В ПРОГРАММУ)
// ===================================================
int main() {
    // Выводим красивый заголовок программы
    cout << string(60, '*') << endl;
    cout << "  PRACTICAL WORK" << endl;
    cout << "  Inheritance" << endl;
    cout << string(60, '*') << endl;

    // Последовательно запускаем демонстрацию обоих заданий
    demoShapes();       // Задание 2.1 - геометрические фигуры
    demoEmployees();    // Задание 2.2 - иерархия сотрудников

    printHeader("Completion");
    cout << "\nAll tasks completed!" << endl;

    // Пауза перед закрытием (чтобы консоль не закрылась сразу)
    cout << "\nPress Enter to exit...";
    cin.get();  // Ждём нажатия Enter

    return 0;  // Возвращаем 0 - программа завершилась успешно
}