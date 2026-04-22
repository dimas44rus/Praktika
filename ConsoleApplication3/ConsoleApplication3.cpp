#include <iostream>  // Для вывода на экран
#include <string>    // Для работы со строками
#include <iomanip>   // Для форматирования вывода
#include <windows.h> // Для русского языка

using namespace std;

// КЛАСС ТОВАР
class Product {
private:
    // ПРИВАТНЫЕ ПОЛЯ - характеристики товара
    string name;      // Название товара (строка)
    double price;     // Цена за штуку (дробное число)
    int quantity;     // Количество на складе (целое число)

public:
    // КОНСТРУКТОР - создает товар
    // : name(n), price(p), quantity(q) - список инициализации (быстрый способ)
    Product(string n, double p, int q) : name(n), price(p), quantity(q) {
        // Тело конструктора пустое, потому что поля уже заполнены
    }

    // ГЕТТЕР для названия
    string getName() const {
        return name;
    }

    // СЕТТЕР для названия
    void setName(const string& n) {
        name = n;
    }

    // ГЕТТЕР для цены
    double getPrice() const {
        return price;
    }

    // СЕТТЕР для цены (с проверкой - цена не может быть отрицательной)
    void setPrice(double p) {
        if (p >= 0) {   // Если цена не отрицательная
            price = p;  // То сохраняем новую цену
        }
    }

    // ГЕТТЕР для количества
    int getQuantity() const {
        return quantity;
    }

    // СЕТТЕР для количества (с проверкой - количество не может быть отрицательным)
    void setQuantity(int q) {
        if (q >= 0) {
            quantity = q;
        }
    }

    // МЕТОД ПОДСЧЕТА ОБЩЕЙ СТОИМОСТИ ТОВАРА НА СКЛАДЕ
    // Формула: цена × количество
    double getTotalValue() const {
        return price * quantity;
    }

    // МЕТОД ПРОДАЖИ ТОВАРА
    // Возвращает true если продажа успешна, false если нет
    bool sell(int amount) {
        // Проверка 1: количество для продажи должно быть положительным
        if (amount <= 0) {
            cout << "Ошибка: Количество должно быть положительным" << endl;
            return false;  // Продажа не удалась
        }

        // Проверка 2: на складе должно быть достаточно товара
        if (amount > quantity) {
            cout << "Ошибка: Недостаточно товара на складе!" << endl;
            cout << "Доступно: " << quantity << " шт." << endl;
            return false;  // Продажа не удалась
        }

        // Если проверки пройдены - продаем товар
        quantity = quantity - amount;  // Уменьшаем количество на складе

        cout << "Продано " << amount << " шт. '" << name << "'" << endl;
        cout << "Остаток на складе: " << quantity << " шт." << endl;

        return true;  // Продажа успешна
    }

    // МЕТОД ВЫВОДА ИНФОРМАЦИИ О ТОВАРЕ
    void displayInfo() const {
        cout << "Товар: " << name << endl;
        cout << fixed << setprecision(2);
        cout << "Цена: " << price << " руб." << endl;
        cout << "Количество на складе: " << quantity << " шт." << endl;
        cout << "Общая стоимость: " << getTotalValue() << " руб." << endl;
    }
};

// ГЛАВНАЯ ФУНКЦИЯ - ДЕМОНСТРАЦИЯ РАБОТЫ
int main() {
    SetConsoleOutputCP(CP_UTF8);

    // SetConsoleCP - устанавливает кодировку для ВВОДА текста из консоли
    // CP_UTF8 - чтобы корректно читать русские буквы, введённые пользователем
    SetConsoleCP(CP_UTF8);
    // Создаем товар: "Ноутбук", цена 50000 руб., количество 10 шт.
    Product product("Ноутбук", 50000, 10);

    // Выводим информацию о товаре
    product.displayInfo();

    // Продаем 3 штуки (успешно)
    product.sell(3);

    // Пробуем продать 10 штук (осталось только 7, будет ошибка)
    product.sell(10);

    // Меняем цену товара
    product.setPrice(45000);
    cout << "\nНовая цена: " << product.getPrice() << " руб." << endl;
    cout << "Новая общая стоимость: " << product.getTotalValue() << " руб." << endl;

    return 0;
}