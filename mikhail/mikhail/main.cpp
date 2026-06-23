#include <iostream>
#include "FinanceManager.h"

int main() {
    // Создаем объект менеджера финансов (наша главная система)
    FinanceManager fm;

    // 1. Наполняем систему стартовыми кошельками и картами (все названия на транслите)
    fm.add_account(Account("Osnovnaya Karta", 50000, "Debetovaya"));
    fm.add_account(Account("Kreditka", 10000, "Kreditnaya"));
    fm.add_account(Account("Nalichnye", 5000, "Koshelek"));

    // 2. Демонстрация работы пополнения: добавляем 2000 к наличным
    fm.deposit_account("Nalichnye", 2000);

    // Создаем искусственные даты для тестирования (День, Месяц, Год, Номер недели в году)
    Date d1 = { 23, 6, 2026, 26 }; // 26-я неделя года
    Date d2 = { 24, 6, 2026, 26 };

    // 3. Заполняем историю затрат покупками по разным кошелькам и категориям
    fm.add_transaction("Osnovnaya Karta", 1500, "Produkty", d1);
    fm.add_transaction("Osnovnaya Karta", 3000, "Odezhda", d1);
    fm.add_transaction("Nalichnye", 400, "Kafe", d1);
    fm.add_transaction("Kreditka", 8000, "Elektronika", d2);
    fm.add_transaction("Osnovnaya Karta", 500, "Produkty", d2);

    // 4. Запрашиваем формирование отчета за НЕДЕЛЮ, привязанного к дате d1
    // Доступные периоды для запроса: "DEN", "NEDELYA" или "MESYAC"
    std::string report = fm.generate_report(d1, "NEDELYA");

    // Вывод готового строкового результата работы алгоритмов в консоль (без кракозябр)
    std::cout << report;

    // 5. Дублируем этот же отчет в текстовый файл "finance_report.txt"
    fm.save_report_to_file("finance_report.txt", report);

    return 0; // Успешное завершение программы
}
