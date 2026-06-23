#ifndef DATE_H
#define DATE_H

#include <string>

// Структура для представления даты транзакции
struct Date {
    int day;         // День месяца (1-31)
    int month;       // Номер месяца (1-12)
    int year;        // Год (например, 2026)
    int week_number; // Порядковый номер недели в году (1-53) для недельных отчетов

    // Конвертирует числовую дату в строковый формат "DD.MM.YYYY"
    std::string to_string() const {
        return std::to_string(day) + "." + std::to_string(month) + "." + std::to_string(year);
    }
};

#endif
