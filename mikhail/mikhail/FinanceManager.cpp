#include "FinanceManager.h"
#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>

// Проверка совпадения дней (с учетом месяца и года)
bool FinanceManager::is_same_day(const Date& d1, const Date& d2) const {
    return d1.day == d2.day && d1.month == d2.month && d1.year == d2.year;
}

// Проверка совпадения номеров недель (с учетом года)
bool FinanceManager::is_same_week(const Date& d1, const Date& d2) const {
    return d1.week_number == d2.week_number && d1.year == d2.year;
}

// Проверка совпадения месяцев (с учетом года)
bool FinanceManager::is_same_month(const Date& d1, const Date& d2) const {
    return d1.month == d2.month && d1.year == d2.year;
}

// Добавление аккаунта в общий вектор
void FinanceManager::add_account(const Account& acc) {
    accounts.push_back(acc);
}

// Пополнение счета по его текстовому имени
void FinanceManager::deposit_account(const std::string& name, double amount) {
    for (auto& acc : accounts) {
        if (acc.get_name() == name) {
            acc.deposit(amount);
            return;
        }
    }
}

// Внесение новой затраты в систему
bool FinanceManager::add_transaction(const std::string& acc_name, double amount, const std::string& category, Date date) {
    for (auto& acc : accounts) {
        if (acc.get_name() == acc_name) {
            if (acc.withdraw(amount)) {
                transactions.push_back(Transaction(amount, category, date));
                return true;
            }
        }
    }
    return false;
}

// Генерация отчета и подсчет рейтингов ТОП-3
std::string FinanceManager::generate_report(Date target_date, const std::string& period) const {
    // Строковый вывод пишется транслитом для стабильности терминала Windows
    std::string report = "=== OTCHET ZA " + period + " (" + target_date.to_string() + ") ===\n";
    double total = 0;

    // Ассоциативный массив для подсчета сумм по категориям
    std::map<std::string, double> cat_totals;
    std::vector<Transaction> filtered;

    // Шаг 1: Фильтрация транзакций по выбранному периоду ("DEN", "NEDELYA", "MESYAC")
    for (const auto& t : transactions) {
        bool match = false;
        if (period == "DEN" && is_same_day(t.get_date(), target_date)) match = true;
        if (period == "NEDELYA" && is_same_week(t.get_date(), target_date)) match = true;
        if (period == "MESYAC" && is_same_month(t.get_date(), target_date)) match = true;

        if (match) {
            filtered.push_back(t);
            total += t.get_amount();
            cat_totals[t.get_category()] += t.get_amount();
        }
    }

    // Шаг 2: Вывод общей суммарной статистики
    report += "Obschie zatraty: " + std::to_string(total) + "\n\nPo kategoriyam:\n";
    for (const auto& pair : cat_totals) {
        report += "  " + pair.first + ": " + std::to_string(pair.second) + "\n";
    }

    // Шаг 3: Вычисление ТОП-3 максимальных одиночных затрат
    report += "\nTOP-3 zatrat:\n";
    auto top_t = filtered;
    // Сортируем по убыванию сумм транзакций с помощью лямбда-функции
    std::sort(top_t.begin(), top_t.end(), [](const Transaction& a, const Transaction& b) {
        return a.get_amount() > b.get_amount();
        });
    // Защита std::min на случай, если расходов было меньше чем 3
    for (size_t i = 0; i < std::min(top_t.size(), size_t(3)); ++i) {
        report += "  " + std::to_string(i + 1) + ". " + top_t[i].get_category() + " - " + std::to_string(top_t[i].get_amount()) + "\n";
    }

    // Шаг 4: Вычисление ТОП-3 самых дорогих категорий
    report += "\nTOP-3 kategoriy:\n";
    std::vector<std::pair<std::string, double>> top_c(cat_totals.begin(), cat_totals.end());
    // Сортируем категории по убыванию общих сумм
    std::sort(top_c.begin(), top_c.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
        });
    for (size_t i = 0; i < std::min(top_c.size(), size_t(3)); ++i) {
        report += "  " + std::to_string(i + 1) + ". " + top_c[i].first + " - " + std::to_string(top_c[i].second) + "\n";
    }

    return report;
}

// Экспорт сформированного отчета в текстовый файл
void FinanceManager::save_report_to_file(const std::string& filename, const std::string& report_data) const {
    // Открываем файл в режиме добавления (std::ios::app), чтобы старые отчеты не стирались
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << report_data << "\n-----------------------------------\n";
        file.close();
        std::cout << "Otchet uspeshno sohranen v fajl: " << filename << "\n";
    }
}
