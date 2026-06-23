#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

// Базовый класс для платежных средств (Карты, Кошельки)
class Account {
protected:
    // protected позволяет дочерним классам иметь прямой доступ к полям
    std::string name;  // Уникальное имя счета (например, "Kreditka")
    double balance;    // Текущий баланс на счету
    std::string type;  // Тип счета (Debetovaya / Kreditnaya / Koshelek)

public:
    // Конструктор счета
    Account(std::string nm, double bal, std::string tp);

    // Виртуальный деструктор для корректного удаления объектов при наследовании
    virtual ~Account() = default;

    // Метод для зачисления средств
    void deposit(double amount);

    // Метод для списания средств. Возвращает true, если операция успешна
    bool withdraw(double amount);

    // Константные геттеры для чтения данных
    std::string get_name() const;
    double get_balance() const;
    std::string get_type() const;
};

#endif
