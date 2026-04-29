#pragma once

// Класс "BankAccount" (Банковский счёт) - демонстрация:
// 1. Инкапсуляции (поля закрыты private)
// 2. Валидации данных (проверка корректности вводимых значений)
// 3. Работы с динамической памятью
class BankAccount
{
private:
    char* owner;           // Владелец счёта (динамическая строка)
    int accountNumber;     // Номер счёта
    double balance;        // Баланс счёта (закрыт от прямого доступа)

public:
    // Конструктор - выделяет память и инициализирует счёт
    // const char* - указатель на константную строку (нельзя изменить исходные данные)
    BankAccount(const char* ownerName, int number, double initialBalance);

    // Деструктор - освобождает память
    ~BankAccount();

    // Метод пополнения счёта (депозит)
    void deposit(double amount);

    // Метод снятия денег (возвращает true, если операция успешна)
    bool withdraw(double amount);

    // Аксессор - только для чтения баланса (нельзя изменить напрямую)
    double getBalance();

    // Вывод всей информации о счёте
    void printInfo();
};