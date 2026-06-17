#include <iostream>
#include <numeric>   // Для std::gcd (нахождение НОД)
#include <clocale>   // Для поддержки русского языка в консоли

class Fraction {
private:
    int numerator;   // числитель дроби
    int denominator; // знаменатель дроби

    // Метод для сокращения дроби
    void simplify() {
        if (denominator == 0) {
            std::cerr << "Ошибка: знаменатель не может быть равен нулю!" << std::endl;
            return;
        }
        // Находим наибольший общий делитель (НОД)
        int gcd = std::gcd(std::abs(numerator), std::abs(denominator)); // вычисляем НОД числителя и знаменателя
        numerator /= gcd;     // делим числитель на НОД
        denominator /= gcd;   // делим знаменатель на НОД

        // Корректируем знак: минус должен быть только в числителе
        if (denominator < 0) {
            numerator = -numerator;     // меняем знак числителя
            denominator = -denominator; // меняем знак знаменателя на положительный
        }
    }

public:
    // Конструктор с параметрами (использует список инициализации)
    Fraction(int num, int denom) : numerator(num), denominator(denom) { // инициализируем поля напрямую
        simplify(); // автоматически сокращаем дробь при создании
    }

    // Конструктор по умолчанию (делегирует вызов основному конструктору)
    Fraction() : Fraction(0, 1) {} // передает 0 и 1 в конструктор с параметрами

    // Вывод дроби на экран
    void print() const {
        std::cout << numerator << "/" << denominator << std::endl; // выводим в формате "число/число"
    }

    // --- Операции с другой дробью (через return *this для цепочки вызовов) ---

    Fraction& add(const Fraction& other) {
        numerator = numerator * other.denominator + other.numerator * denominator; // приводим к общему знаменателю и складываем
        denominator = denominator * other.denominator; // перемножаем знаменатели
        simplify();     // сокращаем полученный результат
        return *this;   // возвращаем ссылку на текущий объект для цепочки
    }

    Fraction& subtract(const Fraction& other) {
        numerator = numerator * other.denominator - other.numerator * denominator; // приводим к общему знаменателю и вычитаем
        denominator = denominator * other.denominator; // перемножаем знаменатели
        simplify();     // сокращаем полученный результат
        return *this;   // возвращаем ссылку на текущий объект для цепочки
    }

    Fraction& multiply(const Fraction& other) {
        numerator *= other.numerator;       // перемножаем числители
        denominator *= other.denominator;   // перемножаем знаменатели
        simplify();     // сокращаем полученный результат
        return *this;   // возвращаем ссылку на текущий объект для цепочки
    }

    // --- Операции с целым числом (через return *this для цепочки вызовов) ---

    Fraction& add(int value) {
        numerator += value * denominator; // преобразуем целое число в дробь и складываем числители
        simplify();     // сокращаем полученный результат
        return *this;   // возвращаем ссылку на текущий объект для цепочки
    }

    Fraction& subtract(int value) {
        numerator -= value * denominator; // преобразуем целое число в дробь и вычитаем из числителя
        simplify();     // сокращаем полученный результат
        return *this;   // возвращаем ссылку на текущий объект для цепочки
    }

    Fraction& multiply(int value) {
        numerator *= value; // умножаем только числитель на целое число
        simplify();     // сокращаем полученный результат
        return *this;   // возвращаем ссылку на текущий объект для цепочки
    }
};

int main() {
    // Настройка локали для корректного вывода кириллицы в консоли
    std::setlocale(LC_ALL, "Russian"); // включаем поддержку русского языка

    std::cout << "Создание дроби по умолчанию (0/1): ";
    Fraction f1; // вызывается конструктор по умолчанию
    f1.print();  // выводит 0/1

    std::cout << "Создание дроби 4/8 (автоматически сокращается до 1/2): ";
    Fraction f2(4, 8); // создается дробь, которая сразу сократится внутри конструктора
    f2.print();        // выводит 1/2

    std::cout << "Создание дроби 1/3: ";
    Fraction f3(1, 3); // создается дробь 1/3
    f3.print();        // выводит 1/3

    // Пример цепочки вызовов: (1/3 + 1/2) * 2 - 1
    std::cout << "\nРезультат цепочки операций ((1/3 + 1/2) * 2 - 1): ";
    f3.add(f2).multiply(2).subtract(1); // последовательно применяем методы к объекту f3
    f3.print(); // выводит итоговый результат вычислений (2/3)

    return 0; // успешное завершение программы
}
