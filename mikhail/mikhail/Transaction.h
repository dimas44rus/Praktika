#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include "Date.h"

// Класс, представляющий одиночную запись о расходе
class Transaction {
private:
    double amount;        // Сумма затраты
    std::string category; // Категория затраты (например, "Produkty")
    Date date;            // Дата совершения платежа

public:
    // Конструктор для инициализации всех параметров затраты
    Transaction(double am, std::string cat, Date dt);

    // Геттеры для безопасного чтения приватных данных (Инкапсуляция)
    double get_amount() const;
    std::string get_category() const;
    Date get_date() const;
};

#endif
