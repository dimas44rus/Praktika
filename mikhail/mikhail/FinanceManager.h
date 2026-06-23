#ifndef FINANCEMANAGER_H
#define FINANCEMANAGER_H

#include <vector>
#include <string>
#include "Account.h"
#include "Transaction.h"

// Главный управляющий класс системы (Ядро приложения)
class FinanceManager {
private:
    std::vector<Account> accounts;         // Хранилище всех созданных карт и кошельков
    std::vector<Transaction> transactions; // Единый журнал всех совершенных расходов

    // Вспомогательные приватные методы для фильтрации дат
    bool is_same_day(const Date& d1, const Date& d2) const;
    bool is_same_week(const Date& d1, const Date& d2) const;
    bool is_same_month(const Date& d1, const Date& d2) const;

public:
    // Добавление нового кошелька или карты в систему
    void add_account(const Account& acc);

    // Пополнение конкретного счета по его имени
    void deposit_account(const std::string& name, double amount);

    // Проведение расхода: списывает деньги со счета и заносит в журнал
    bool add_transaction(const std::string& acc_name, double amount, const std::string& category, Date date);

    // Формирование текстового отчета со статистикой и рейтингами ТОП-3
    std::string generate_report(Date target_date, const std::string& period) const;

    // Экспорт сформированного отчета в текстовый файл
    void save_report_to_file(const std::string& filename, const std::string& report_data) const;
};

#endif
