// ===== ОТКЛЮЧЕНИЕ ПРЕДУПРЕЖДЕНИЙ VS =====
#define NOMINMAX           // Отключает макросы min/max из Windows.h
#pragma warning(disable: 4996)  // Отключает предупреждения о "небезопасных" функциях

// ===== ПОДКЛЮЧЕНИЕ ЗАГОЛОВКОВ =====
#include "PhoneBook.h"
#include <cstring>    // для strcpy, strlen, strcmp
#include <windows.h>  // для русского языка в консоли

// ============================================
// РЕАЛИЗАЦИЯ STRUCT CONTACT (внутренняя структура)
// ============================================

/**
 * Конструктор Contact по умолчанию
 * Использует список инициализации: fullName(nullptr)
 * nullptr означает, что указатель никуда не указывает (память не выделена)
 * Остальные поля - массивы, они инициализируются внутри тела конструктора
 */
PhoneBook::Contact::Contact() : fullName(nullptr) {
    // Обнуляем телефонные массивы (первый символ - завершающий ноль)
    homePhone[0] = '\0';
    workPhone[0] = '\0';
    mobilePhone[0] = '\0';
    additionalInfo[0] = '\0';
}

/**
 * Деструктор Contact
 * ОСВОБОЖДАЕТ ДИНАМИЧЕСКУЮ ПАМЯТЬ!
 * Это критически важно - без этого будут утечки памяти
 * delete[] используется, потому что new[] выделял массив символов
 */
PhoneBook::Contact::~Contact() {
    delete[] fullName;  // Если fullName == nullptr, delete[] безопасен (ничего не делает)
}

/**
 * Конструктор копирования Contact
 * Вызывается при:
 *   Contact c2 = c1;    // копирование при создании
 *   передаче по значению в функцию
 *
 * ВАЖНО: выполняет ГЛУБОКОЕ копирование!
 * Если бы мы просто скопировали указатель (поверхностное копирование),
 * то два объекта указывали бы на одну память, и при удалении одного
 * у второго указатель стал бы висячим (double delete error)
 */
PhoneBook::Contact::Contact(const Contact& other) {
    // Копируем ФИО - выделяем НОВУЮ память
    if (other.fullName) {
        // Вычисляем длину строки + 1 для нуль-терминатора
        fullName = new char[strlen(other.fullName) + 1];
        // Копируем содержимое
        strcpy(fullName, other.fullName);
    }
    else {
        fullName = nullptr;  // Если у другого нет ФИО, у нового тоже не будет
    }

    // Копируем массивы (можно просто присвоить, т.к. это массивы символов)
    strcpy(homePhone, other.homePhone);
    strcpy(workPhone, other.workPhone);
    strcpy(mobilePhone, other.mobilePhone);
    strcpy(additionalInfo, other.additionalInfo);
}

/**
 * Оператор присваивания Contact
 * Вызывается при: c1 = c2; (когда c1 уже существует)
 *
 * Важные моменты:
 * 1. Проверка на самоприсваивание (this != &other)
 * 2. Освобождение старой памяти
 * 3. Выделение новой памяти
 * 4. Возврат *this для цепочечных присваиваний (a = b = c)
 */
PhoneBook::Contact& PhoneBook::Contact::operator=(const Contact& other) {
    // Защита от самоприсваивания: если пытаемся присвоить объект самому себе
    if (this != &other) {
        // 1. Освобождаем старую память
        delete[] fullName;

        // 2. Выделяем новую память и копируем данные
        if (other.fullName) {
            fullName = new char[strlen(other.fullName) + 1];
            strcpy(fullName, other.fullName);
        }
        else {
            fullName = nullptr;
        }

        // 3. Копируем массивы
        strcpy(homePhone, other.homePhone);
        strcpy(workPhone, other.workPhone);
        strcpy(mobilePhone, other.mobilePhone);
        strcpy(additionalInfo, other.additionalInfo);
    }

    // 4. Возвращаем ссылку на текущий объект (для цепочечных присваиваний)
    return *this;
}

// ============================================
// РЕАЛИЗАЦИЯ PHONEBOOK
// ============================================

/**
 * Конструктор PhoneBook
 * Список инициализации не требуется, т.к. вектор contacts
 * инициализируется конструктором по умолчанию автоматически
 */
PhoneBook::PhoneBook() {
    std::cout << "Телефонная книга создана!\n";
}

/**
 * Деструктор PhoneBook
 * contacts уничтожается автоматически, что вызывает деструкторы всех Contact
 * А те, в свою очередь, освобождают память под ФИО
 * Это пример РАИИ (Resource Acquisition Is Initialization)
 */
PhoneBook::~PhoneBook() {
    std::cout << "Телефонная книга удалена!\n";
}

/**
 * Вспомогательная функция: создание строки ФИО
 * Динамически выделяет память под строку формата "Фамилия Имя Отчество"
 *
 * @param surname фамилия
 * @param name имя
 * @param patronymic отчество
 * @return указатель на новую строку в куче
 */
char* PhoneBook::createFullName(const char* surname, const char* name, const char* patronymic) {
    // Вычисляем необходимый размер: длины всех частей + 2 пробела + 1 завершающий ноль
    size_t len = strlen(surname) + strlen(name) + strlen(patronymic) + 3;

    // Выделяем память в куче (динамическая память!)
    char* result = new char[len];

    // Формируем строку: "фамилия имя отчество"
    // sprintf безопаснее, чем ручное копирование, но требует достаточно места
    sprintf(result, "%s %s %s", surname, name, patronymic);

    return result;
}

/**
 * Вспомогательная функция для ввода строки с подсказкой
 * Упрощает код и уменьшает дублирование
 */
void PhoneBook::inputString(char* buffer, int size, const char* prompt) {
    std::cout << prompt;
    std::cin.getline(buffer, size);  // getline читает всю строку, включая пробелы
}

/**
 * ДОБАВЛЕНИЕ КОНТАКТА
 *
 * Алгоритм:
 * 1. Очищаем буфер ввода (cin.ignore)
 * 2. Создаём временный объект Contact
 * 3. Запрашиваем у пользователя ФИО по частям
 * 4. Создаём строку ФИО в динамической памяти
 * 5. Запрашиваем телефоны и доп. информацию
 * 6. Добавляем контакт в вектор (при этом вызывается конструктор копирования)
 * 7. Временный объект уничтожается, но данные скопированы в вектор
 */
void PhoneBook::addContact() {
    Contact newContact;  // Создаём временный контакт (fullName = nullptr)
    char surname[50], name[50], patronymic[50];

    // Очищаем буфер ввода от предыдущего символа новой строки
    std::cin.ignore();

    std::cout << "\n========== ДОБАВЛЕНИЕ КОНТАКТА ==========\n";

    // Ввод ФИО по частям
    std::cout << "Введите фамилию: ";
    std::cin.getline(surname, 50);

    std::cout << "Введите имя: ";
    std::cin.getline(name, 50);

    std::cout << "Введите отчество: ";
    std::cin.getline(patronymic, 50);

    // ДИНАМИЧЕСКАЯ ПАМЯТЬ: создаём строку ФИО в куче
    newContact.fullName = createFullName(surname, name, patronymic);

    // Ввод телефонов и доп. информации
    std::cout << "Введите домашний телефон: ";
    std::cin.getline(newContact.homePhone, 20);

    std::cout << "Введите рабочий телефон: ";
    std::cin.getline(newContact.workPhone, 20);

    std::cout << "Введите мобильный телефон: ";
    std::cin.getline(newContact.mobilePhone, 20);

    std::cout << "Введите дополнительную информацию: ";
    std::cin.getline(newContact.additionalInfo, 200);

    // Добавляем в вектор
    // Здесь вызывается конструктор копирования Contact!
    // Поэтому данные будут скопированы, а не просто сохранён указатель
    contacts.push_back(newContact);

    std::cout << "\n✓ Контакт успешно добавлен!\n";
    std::cout << "Всего контактов в книге: " << contacts.size() << "\n";
}

/**
 * УДАЛЕНИЕ КОНТАКТА
 *
 * Алгоритм:
 * 1. Проверяем, не пуста ли книга
 * 2. Запрашиваем ФИО для удаления
 * 3. Ищем контакт с таким ФИО (сравнение строк)
 * 4. Удаляем из вектора методом erase
 * 5. vector автоматически вызывает деструктор Contact, который освободит память
 */
void PhoneBook::removeContact() {
    // Проверка на пустоту
    if (contacts.empty()) {
        std::cout << "\n✗ Телефонная книга пуста! Нечего удалять.\n";
        return;
    }

    char searchName[100];
    std::cin.ignore();  // Очищаем буфер

    std::cout << "\n========== УДАЛЕНИЕ КОНТАКТА ==========\n";
    std::cout << "Введите полное ФИО для удаления: ";
    std::cin.getline(searchName, 100);

    // Линейный поиск по всем контактам
    for (size_t i = 0; i < contacts.size(); i++) {
        // strcmp возвращает 0, если строки равны
        if (strcmp(contacts[i].fullName, searchName) == 0) {
            // Выводим информацию об удаляемом контакте
            std::cout << "\nКонтакт найден:\n";
            std::cout << "ФИО: " << contacts[i].fullName << std::endl;
            std::cout << "Телефон: " << contacts[i].homePhone << std::endl;

            // Удаляем элемент из вектора
            // erase вызывает деструктор Contact, который освободит fullName
            contacts.erase(contacts.begin() + i);

            std::cout << "\n✓ Контакт успешно удалён!\n";
            std::cout << "Осталось контактов: " << contacts.size() << "\n";
            return;
        }
    }

    std::cout << "\n✗ Контакт с ФИО \"" << searchName << "\" не найден!\n";
}

/**
 * ПОИСК КОНТАКТА ПО ФИО
 *
 * Алгоритм:
 * 1. Проверка на пустоту
 * 2. Запрос ФИО для поиска
 * 3. Линейный поиск по всем контактам
 * 4. Вывод информации при нахождении
 */
void PhoneBook::searchByName() {
    if (contacts.empty()) {
        std::cout << "\n✗ Телефонная книга пуста! Нет контактов для поиска.\n";
        return;
    }

    char searchName[100];
    std::cin.ignore();

    std::cout << "\n========== ПОИСК КОНТАКТА ==========\n";
    std::cout << "Введите ФИО для поиска: ";
    std::cin.getline(searchName, 100);

    // Поиск
    bool found = false;
    for (size_t i = 0; i < contacts.size(); i++) {
        if (strcmp(contacts[i].fullName, searchName) == 0) {
            // Красивый вывод найденного контакта
            std::cout << "\n╔════════════════════════════════════════╗\n";
            std::cout << "║           КОНТАКТ НАЙДЕН              ║\n";
            std::cout << "╚════════════════════════════════════════╝\n";
            std::cout << "ФИО: " << contacts[i].fullName << std::endl;
            std::cout << "Домашний телефон: " << contacts[i].homePhone << std::endl;
            std::cout << "Рабочий телефон: " << contacts[i].workPhone << std::endl;
            std::cout << "Мобильный телефон: " << contacts[i].mobilePhone << std::endl;
            std::cout << "Дополнительная информация: " << contacts[i].additionalInfo << std::endl;
            found = true;
            break;
        }
    }

    if (!found) {
        std::cout << "\n✗ Контакт с ФИО \"" << searchName << "\" не найден!\n";
    }
}

/**
 * ВЫВОД ВСЕХ КОНТАКТОВ
 *
 * Красивый табличный вывод с рамками
 * Проходит по всем элементам вектора и выводит их
 */
void PhoneBook::showAllContacts() {
    if (contacts.empty()) {
        std::cout << "\n╔════════════════════════════════════════╗\n";
        std::cout << "║     ТЕЛЕФОННАЯ КНИГА ПУСТА            ║\n";
        std::cout << "╚════════════════════════════════════════╝\n";
        return;
    }

    // Заголовок
    std::cout << "\n╔════════════════════════════════════════════════════════════════╗\n";
    std::cout << "║                    СПИСОК ВСЕХ КОНТАКТОВ                       ║\n";
    std::cout << "╚════════════════════════════════════════════════════════════════╝\n";
    std::cout << "Всего контактов в книге: " << contacts.size() << "\n\n";

    // Вывод каждого контакта
    for (size_t i = 0; i < contacts.size(); i++) {
        std::cout << "╔══════════════════════════════════════════════════════════════╗\n";
        std::cout << "║ Контакт #" << i + 1 << "\n";
        std::cout << "╠══════════════════════════════════════════════════════════════╣\n";
        std::cout << "║ ФИО: " << contacts[i].fullName << "\n";
        std::cout << "║ Домашний: " << contacts[i].homePhone << "\n";
        std::cout << "║ Рабочий: " << contacts[i].workPhone << "\n";
        std::cout << "║ Мобильный: " << contacts[i].mobilePhone << "\n";
        std::cout << "║ Доп. инфо: " << contacts[i].additionalInfo << "\n";
        std::cout << "╚══════════════════════════════════════════════════════════════╝\n";
        std::cout << std::endl;
    }
}

/**
 * ОЧИСТКА ВСЕЙ ТЕЛЕФОННОЙ КНИГИ
 * Метод clear() вектора удаляет все элементы
 * При этом вызываются деструкторы Contact, освобождающие память
 */
void PhoneBook::clearAll() {
    if (!contacts.empty()) {
        contacts.clear();  // Очищаем вектор
        std::cout << "\n✓ Все контакты удалены!\n";
    }
    else {
        std::cout << "\n✗ Телефонная книга уже пуста!\n";
    }
}

/**
 * ГЛАВНОЕ МЕНЮ
 *
 * Реализует основной цикл программы:
 * - Отображает меню
 * - Принимает выбор пользователя
 * - Вызывает соответствующие методы
 * - Завершается при выборе пункта 0
 */
void PhoneBook::menu() {
    int choice;  // Переменная для хранения выбора пользователя

    do {
        // Визуальное оформление меню
        std::cout << "\n";
        std::cout << "╔════════════════════════════════════════════════════════════╗\n";
        std::cout << "║                    ТЕЛЕФОННАЯ КНИГА                        ║\n";
        std::cout << "╠════════════════════════════════════════════════════════════╣\n";
        std::cout << "║  1. Добавить контакт                                      ║\n";
        std::cout << "║  2. Удалить контакт                                       ║\n";
        std::cout << "║  3. Найти контакт по ФИО                                  ║\n";
        std::cout << "║  4. Показать всех абонентов                               ║\n";
        std::cout << "║  5. Количество контактов                                  ║\n";
        std::cout << "║  6. Очистить всю книгу                                    ║\n";
        std::cout << "║  0. Выход                                                ║\n";
        std::cout << "╚════════════════════════════════════════════════════════════╝\n";
        std::cout << "Выберите действие: ";
        std::cin >> choice;

        // Обработка выбора (switch-case конструкция)
        switch (choice) {
        case 1:
            addContact();        // Добавление
            break;
        case 2:
            removeContact();     // Удаление
            break;
        case 3:
            searchByName();      // Поиск
            break;
        case 4:
            showAllContacts();   // Показать всех
            break;
        case 5:
            // Inline-геттер: количество контактов
            std::cout << "\nВсего контактов: " << getContactCount() << "\n";
            break;
        case 6:
            clearAll();          // Очистка
            break;
        case 0:
            // Выход из программы
            std::cout << "\n╔════════════════════════════════════════╗\n";
            std::cout << "║     До свидания! Заходите ещё!        ║\n";
            std::cout << "╚════════════════════════════════════════╝\n";
            break;
        default:
            // Обработка неверного ввода
            std::cout << "\n✗ Неверный выбор! Попробуйте снова.\n";
            break;
        }
    } while (choice != 0);  // Продолжаем, пока не выбран выход
}