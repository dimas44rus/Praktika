#include "Account.h"

// Конструктор: заполняем имя, стартовый баланс и тип платежного средства
Account::Account(std::string nm, double bal, std::string tp)
    : name(nm), balance(bal), type(tp) {
}

// Пополнение баланса
void Account::deposit(double amount) {
    if (amount > 0) { // Защита: нельзя пополнить счет на отрицательную сумму
        balance += amount;
    }
}

// Списание баланса (оплата)
bool Account::withdraw(double amount) {
    // Проверяем, что сумма корректна и на счету достаточно средств
    if (amount > 0 && balance >= amount) {
        balance -= amount; // Уменьшаем баланс
        return true;       // Сигнализируем об успешном списании
    }
    return false; // Если денег не хватило, транзакция отклоняется
}

// Получить имя счета
std::string Account::get_name() const { return name; }

// Получить текущий остаток
double Account::get_balance() const { return balance; }

// Получить тип (карта/кошелек)
std::string Account::get_type() const { return type; }
