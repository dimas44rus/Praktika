#include "Transaction.h"

// Реализация конструктора: копируем переданные значения в приватные поля класса
Transaction::Transaction(double am, std::string cat, Date dt)
    : amount(am), category(cat), date(dt) {
}

// Геттер для получения суммы операции
double Transaction::get_amount() const { return amount; }

// Геттер для получения названия категории
std::string Transaction::get_category() const { return category; }

// Геттер для получения объекта даты
Date Transaction::get_date() const { return date; }
