#include <iostream>  // Для вывода на экран
#include <string>    // Для работы со строками
#include <iomanip>   // Для форматирования вывода
#include <windows.h> // Для русского языка

using namespace std;

// КЛАСС БАНКОВСКИЙ СЧЕТ
class BankAccount {
private:
    // ПРИВАТНЫЕ ПОЛЯ - данные счета, скрыты от прямого доступа
    string accountNumber;   // Номер счета (строка)
    double balance;         // Баланс счета (дробное число для денег)
    string ownerName;       // Имя владельца (строка)

public:
    // КОНСТРУКТОР - создает новый счет
    // initialBalance = 0 - если не указать начальный баланс, будет 0
    BankAccount(string accNumber, string owner, double initialBalance = 0) {
        accountNumber = accNumber;   // Сохраняем номер счета
        ownerName = owner;           // Сохраняем имя владельца
        balance = initialBalance;    // Сохраняем начальный баланс
    }

    // ГЕТТЕР для номера счета (только чтение)
    string getAccountNumber() const {
        return accountNumber;
    }

    // ГЕТТЕР для имени владельца
    string getOwnerName() const {
        return ownerName;
    }

    // СЕТТЕР для имени владельца (позволяет изменить)
    void setOwnerName(const string& name) {
        if (!name.empty()) {      // Проверка: имя не пустое?
            ownerName = name;     // Если да - сохраняем новое имя
        }
    }

    // ГЕТТЕР для баланса (только чтение)
    double getBalance() const {
        return balance;
    }

    // МЕТОД ПОПОЛНЕНИЯ СЧЕТА
    void deposit(double amount) {
        // Проверка: сумма должна быть положительной
        if (amount <= 0) {
            cout << "Ошибка: Сумма должна быть положительной" << endl;
            return;  // Выходим из метода, ничего не меняя
        }

        balance = balance + amount;  // Увеличиваем баланс

        cout << fixed << setprecision(2);
        cout << "Пополнение на " << amount << " руб." << endl;
        cout << "Текущий баланс: " << balance << " руб." << endl;
    }

    // МЕТОД СНЯТИЯ ДЕНЕГ СО СЧЕТА
    void withdraw(double amount) {
        // Проверка 1: сумма должна быть положительной
        if (amount <= 0) {
            cout << "Ошибка: Сумма должна быть положительной" << endl;
            return;
        }

        // Проверка 2: на счете должно хватать денег
        if (amount > balance) {
            cout << "Ошибка: Недостаточно средств!" << endl;
            cout << "Доступно: " << balance << " руб." << endl;
            return;  // Не снимаем деньги
        }

        balance = balance - amount;  // Уменьшаем баланс

        cout << fixed << setprecision(2);
        cout << "Снятие " << amount << " руб." << endl;
        cout << "Текущий баланс: " << balance << " руб." << endl;
    }

    // МЕТОД ВЫВОДА ИНФОРМАЦИИ О СЧЕТЕ
    void displayInfo() const {
        cout << "Номер счета: " << accountNumber << endl;
        cout << "Владелец: " << ownerName << endl;
        cout << fixed << setprecision(2);
        cout << "Баланс: " << balance << " руб." << endl;
    }
};

// ГЛАВНАЯ ФУНКЦИЯ - ДЕМОНСТРАЦИЯ РАБОТЫ
int main() {
    SetConsoleOutputCP(CP_UTF8);

    // SetConsoleCP - устанавливает кодировку для ВВОДА текста из консоли
    // CP_UTF8 - чтобы корректно читать русские буквы, введённые пользователем
    SetConsoleCP(CP_UTF8);
    // Создаем счет с начальным балансом 1000 рублей
    BankAccount account("1234567890", "Иван Петров", 1000);

    // Показываем информацию о счете
    account.displayInfo();

    // Пополняем счет на 500 рублей
    account.deposit(500);

    // Снимаем 200 рублей
    account.withdraw(200);

    // Пробуем снять 2000 рублей (должна быть ошибка)
    account.withdraw(2000);

    return 0;
}