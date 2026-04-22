#include <iostream>  // Для вывода на экран (cout)
#include <string>    // Для работы со строками (string)
#include <iomanip>   // Для форматирования вывода (setprecision)
#include <windows.h> // Для русского языка

using namespace std; // Чтобы писать cout вместо std::cout

// КЛАСС СТУДЕНТ
class Student {
private:
    // ПРИВАТНЫЕ ПОЛЯ - хранят данные, скрыты от внешнего доступа
    string fullName;   // Имя студента (строка)
    string group;      // Группа студента (строка)
    int grades[5];     // Массив оценок на 5 предметов (целые числа)

public:
    // КОНСТРУКТОР - срабатывает при создании объекта
    // Принимает: имя, группу и массив оценок
    Student(string name, string gr, int grd[5]) {
        fullName = name;   // Сохраняем имя в поле класса
        group = gr;        // Сохраняем группу в поле класса

        // Копируем все 5 оценок из переданного массива в массив класса
        for (int i = 0; i < 5; i++) {
            grades[i] = grd[i];
        }
    }

    // ГЕТТЕР для имени - просто возвращает значение поля fullName
   const string getFullName() const {
        return fullName;
    }

    // ГЕТТЕР для группы - возвращает значение поля group
    string getGroup() const {
        return group;
    }

    // МЕТОД ВЫЧИСЛЕНИЯ СРЕДНЕГО БАЛЛА
    double getAverageGrade() const {
        int sum = 0;  // Переменная для суммы оценок, начинаем с нуля

        // Складываем все 5 оценок
        for (int i = 0; i < 5; i++) {
            sum = sum + grades[i];  // Добавляем очередную оценку
        }

        // Делим сумму на 5 и возвращаем результат
        // static_cast<double> - превращает целое число в дробное для точности
        return static_cast<double>(sum) / 5;
    }

    // МЕТОД ВЫВОДА ИНФОРМАЦИИ НА ЭКРАН
    void displayInfo() const {
        cout << "Студент: " << fullName << endl;      // Выводим имя
        cout << "Группа: " << group << endl;         // Выводим группу

        cout << "Оценки: ";
        for (int i = 0; i < 5; i++) {
            cout << grades[i] << " ";   // Выводим каждую оценку
        }
        cout << endl;  // Переход на новую строку

        // Настройка вывода дробных чисел: 2 знака после запятой
        cout << fixed << setprecision(2);
        cout << "Средний балл: " << getAverageGrade() << endl;
    }
};

// ГЛАВНАЯ ФУНКЦИЯ - ЗДЕСЬ НАЧИНАЕТСЯ РАБОТА ПРОГРАММЫ
int main() {
    SetConsoleOutputCP(CP_UTF8);

    // SetConsoleCP - устанавливает кодировку для ВВОДА текста из консоли
    // CP_UTF8 - чтобы корректно читать русские буквы, введённые пользователем
    SetConsoleCP(CP_UTF8);
    // ШАГ 1: создаем массив с оценками студента
    int grades[] = { 5, 4, 5, 4, 5 };

    // ШАГ 2: создаем объект student класса Student
    // Передаем в конструктор: имя, группу, массив оценок
    Student student("Иван Петров", "Группа 101", grades);

    // ШАГ 3: вызываем метод для вывода информации
    student.displayInfo();

    return 0;  // 0 означает "программа отработала без ошибок"
}