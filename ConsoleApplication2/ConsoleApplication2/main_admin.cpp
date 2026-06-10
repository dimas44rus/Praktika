#include <iostream> // Стандартная библиотека ввода-вывода (cin, cout).
#include <Windows.h> // ПОДКЛЮЧЕНИЕ РУССКОГО ЯЗЫКА: Библиотека управления консолью Windows.
#include "Storage.h" // Подключение логики базы данных.
#include "Logger.h" // Подключение логики логов.

int main() {
    SetConsoleCP(1251); // РУССКИЙ ЯЗЫК: Включаем поддержку ввода кириллицы с клавиатуры.
    SetConsoleOutputCP(1251); // РУССКИЙ ЯЗЫК: Включаем отображение кириллицы на экране консоли.

    int mainChoice; // Переменная для хранения выбора глобальной роли пользователя.

    while (true) { // Главный цикл переключения между интерфейсами системы.
        std::cout << "\n=========================================\n";
        std::cout << "  СИСТЕМА ОБРАБОТКИ ОБРАЩЕНИЙ ГРАЖДАН\n";
        std::cout << "=========================================\n";
        std::cout << "Вход в систему под ролью:\n";
        std::cout << "1. Гражданин (Подать новое обращение)\n";
        std::cout << "2. Сотрудник ведомства (Рассмотреть и ответить)\n";
        std::cout << "3. Администратор (Удаление обращений и аудит)\n";
        std::cout << "0. Выход из программы\n";
        std::cout << "Выберите вашу роль: ";
        std::cin >> mainChoice; // Считываем номер выбранной роли.

        if (std::cin.fail()) { // Если пользователь ввёл буквы вместо цифр:
            std::cin.clear(); // Сбрасываем флаг ошибки потока ввода.
            std::cin.ignore(32767, '\n'); // Полностью вычищаем мусорный ввод из буфера.
            std::cout << "Ошибка! Введите корректный цифровой пункт.\n";
            continue; // Возвращаемся в начало цикла.
        }

        std::cin.ignore(32767, '\n'); // Очищаем остаточный перевод строки из буфера.

        if (mainChoice == 0) { // Если выбран выход:
            std::cout << "Программа успешно завершена. Всего доброго!\n";
            break; // Разрываем бесконечный цикл, закрывая приложение.
        }

        switch (mainChoice) {
        case 1: { // ИНТЕРФЕЙС ГРАЖДАНИНА
            std::cout << "\n--- РАБОЧЕЕ МЕСТО: ГРАЖДАНЫН ---\n";
            std::string name, text;
            std::cout << "Введите ваше ФИО: ";
            std::getline(std::cin, name); // Считываем имя с пробелами.
            std::cout << "Введите текст вашего обращения: ";
            std::getline(std::cin, text); // Считываем текст обращения.

            auto requests = Storage::loadRequests(); // Загружаем базу.
            int newId = Storage::getNextId(); // Берем свободный ID.

            requests.push_back(CitizenRequest(newId, name, text)); // Добавляем новую запись.
            Storage::saveRequests(requests); // Записываем в базу.

            Logger::logAction("Гражданин", "Создано обращение №" + std::to_string(newId)); // Делаем запись в логи.
            std::cout << "Успешно! Номер вашего обращения: " << newId << ". Ожидайте ответа.\n";
            break;
        }
        case 2: { // ИНТЕРФЕЙС СОТРУДНИКА ВЕДОМСТВА
            std::cout << "\n--- РАБОЧЕЕ МЕСТО: СОТРУДНИК ВЕДОМСТВА ---\n";
            auto requests = Storage::loadRequests(); // Подгружаем актуальные данные.

            bool hasNew = false; // Флаг наличия нерассмотренных дел.
            std::cout << "Список нерешенных обращений на сегодня:\n";
            for (const auto& req : requests) {
                if (!req.getStatus()) { // Проверяем, если статус равен "false" (еще нет ответа).
                    std::cout << "[" << req.getId() << "] От: " << req.getCitizenName() << " | Текст: " << req.getText() << "\n";
                    hasNew = true; // Засекли нерешенное обращение.
                }
            }

            if (!hasNew) { // Если все заявки уже обработаны:
                std::cout << "Ура! На текущий момент нерассмотренных обращений нет.\n";
                break; // Возвращаемся в главное меню ролей.
            }

            int targetId;
            std::cout << "\nВведите ID обращения, на которое хотите ответить (или 0 для отмены): ";
            std::cin >> targetId;
            std::cin.ignore(32767, '\n'); // Сбрасываем перенос строки.

            if (targetId == 0) break; // Отмена операции.

            bool found = false;
            for (auto& req : requests) { // Поиск по ссылке для возможности изменения.
                if (req.getId() == targetId && !req.getStatus()) {
                    std::string answer;
                    std::cout << "Введите официальный ответ ведомства: ";
                    std::getline(std::cin, answer); // Принимаем ответ.

                    req.setAnswer(answer); // Прикрепляем ответ к объекту.
                    found = true;
                    Logger::logAction("Сотрудник", "Добавлен ответ на обращение №" + std::to_string(targetId)); // Логируем.
                    break;
                }
            }

            if (found) {
                Storage::saveRequests(requests); // Сохраняем обновленный файл базы.
                std::cout << "Ответ успешно зарегистрирован в системе!\n";
            }
            else {
                std::cout << "Ошибка! Обращение с таким ID не найдено или оно уже решено.\n";
            }
            break;
        }
        case 3: { // ИНТЕРФЕЙС АДМИНИСТРАТОРА
            std::cout << "\n--- РАБОЧЕЕ МЕСТО: АДМИНИСТРАТОР ---\n";
            auto requests = Storage::loadRequests(); // Загружаем архив.

            std::cout << "Архив всех обращений в системе:\n";
            for (const auto& req : requests) {
                std::cout << "[" << req.getId() << "] [" << (req.getStatus() ? "РЕШЕНО" : "НОВОЕ") << "] "
                    << "Автор: " << req.getCitizenName() << " | Ответ: " << req.getAnswer() << "\n";
            }

            int idToDelete;
            std::cout << "\nВведите ID обращения для полного УДАЛЕНИЯ (или 0 для отмены): ";
            std::cin >> idToDelete;

            if (idToDelete == 0) break; // Администратор передумал.

            bool deleted = false;
            for (auto it = requests.begin(); it != requests.end(); ++it) { // Поиск итератором.
                if (it->getId() == idToDelete) {
                    requests.erase(it); // Удаляем запись из памяти.
                    deleted = true;
                    Logger::logAction("Администратор", "Удалено обращение №" + std::to_string(idToDelete)); // Логируем.
                    break; // Выходим из цикла.
                }
            }

            if (deleted) {
                Storage::saveRequests(requests); // Записываем изменения в файл.
                std::cout << "Запись №" << idToDelete << " безвозвратно удалена из базы данных.\n";
            }
            else {
                std::cout << "Ошибка! Запись с указанным ID не обнаружена.\n";
            }
            break;
        }
        default:
            std::cout << "Неверный выбор. Пожалуйста, введите число от 0 до 3.\n";
        }
    }
    return 0; // Конец работы приложения.
}
