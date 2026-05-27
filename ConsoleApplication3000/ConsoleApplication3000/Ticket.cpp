#include "Ticket.h"

// Реализация функции инициализации. Передаем ticket по ссылке (&), чтобы изменить оригинальный объект
void initTicket(Ticket& ticket, int id, const std::string& name, int priority, int h, int m, const std::string& issue) {
    // Присваиваем автоматически сгенерированный ID
    ticket.id = id;

    // Копируем имя клиента в структуру
    ticket.clientName = name;

    // Проверка на корректность приоритета: если передан некорректный код, ставим по умолчанию 1 (низкий)
    if (priority < 1 || priority > 3) {
        ticket.priority = 1;
    }
    else {
        ticket.priority = priority;
    }

    // Проверка корректности времени (валидация диапазона часов и минут)
    ticket.time.hours = (h >= 0 && h < 24) ? h : 0;
    ticket.time.minutes = (m >= 0 && m < 60) ? m : 0;

    // Записываем описание технической проблемы
    ticket.issue = issue;
}
