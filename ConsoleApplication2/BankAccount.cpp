#include "BankAccount.h"
#include <iostream>
#include <cstring>
#include <iomanip>
using namespace std;

// КОНСТРУКТОР
BankAccount::BankAccount(const char* ownerName, int number, double initialBalance)
{
    // 1. Выделяем память для имени владельца
    size_t len = strlen(ownerName);        // Узнаём длину строки
    owner = new char[len + 10];            // Выделяем память (+10 запас)
    strcpy_s(owner, len + 10, ownerName);  // Копируем имя

    // 2. Устанавливаем номер счёта
    accountNumber = number;

    // 3. Проверка начального баланса (ВАЛИДАЦИЯ!)
    if (initialBalance < 0)
    {
        // Отрицательный баланс - недопустим, устанавливаем 0
        balance = 0;
        cout << "Предупреждение: Начальный баланс не может быть отрицательным!"
            << " Установлен баланс 0 руб." << endl;
    }
    else
    {
        balance = initialBalance;
    }
}

// ДЕСТРУКТОР
BankAccount::~BankAccount()
{
    delete[] owner;  // Освобождаем память, выделенную под имя владельца
}

// ПОПОЛНЕНИЕ СЧЁТА
void BankAccount::deposit(double amount)
{
    // Валидация: сумма должна быть положительной
    if (amount <= 0)
    {
        cout << "Ошибка: Сумма пополнения должна быть положительной!" << endl;
    }
    else
    {
        balance += amount;  // Увеличиваем баланс
        cout << "Счёт пополнен на " << fixed << setprecision(2)
            << amount << " руб." << endl;
    }
}

// СНЯТИЕ ДЕНЕГ
bool BankAccount::withdraw(double amount)
{
    // Валидация 1: сумма должна быть положительной
    if (amount <= 0)
    {
        cout << "Ошибка: Сумма снятия должна быть положительной!" << endl;
        return false;
    }

    // Валидация 2: на счету должно быть достаточно средств
    if (amount > balance)
    {
        cout << "Ошибка: Недостаточно средств! Требуется: " << amount
            << " руб., доступно: " << balance << " руб." << endl;
        return false;
    }

    // Все проверки пройдены - можно снимать
    balance -= amount;
    cout << "Снято " << fixed << setprecision(2) << amount << " руб." << endl;
    return true;  // Операция успешна
}

// АКСЕССОР - возвращает текущий баланс (только чтение)
double BankAccount::getBalance()
{
    return balance;
}

// ВЫВОД ИНФОРМАЦИИ О СЧЁТЕ
void BankAccount::printInfo()
{
    cout << "\n=== ИНФОРМАЦИЯ О СЧЁТЕ ===" << endl;
    cout << "Владелец: " << owner << endl;
    cout << "Счёт №: " << accountNumber << endl;
    cout << "Баланс: " << fixed << setprecision(2) << balance << " руб." << endl;
}

// ВНИМАНИЕ: НЕТ main()! main() только в main.cpp