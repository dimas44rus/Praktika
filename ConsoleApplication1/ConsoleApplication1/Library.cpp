#include "Library.h" // Подключение заголовочного описания класса Library
#include <iostream> // Подключение библиотеки базового ввода-вывода (std::cout)
#include <algorithm> // Подключение библиотеки алгоритмов для использования std::transform

// Конструктор: копирует параметры в поля класса, заполняя название, библиотекаря и каталог книг
Library::Library(std::string n, Librarian l, std::vector<Book> books)
    : name(n), librarian(l), catalog(books) {
}

// Реализация геттера для получения имени библиотеки
std::string Library::getName() const { return name; }

// Реализация приватного метода перевода букв строки в нижний регистр (регистронезависимость)
std::string Library::toLower(std::string str) const {
    // Алгоритм transform посимвольно обходит строку и преобразует буквы через функцию std::tolower
    std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) {
        return std::tolower(c); // Возвращаем текущий символ в нижнем регистре
        });
    return str; // Возвращаем готовую строчную строку
}

// Реализация метода вывода визитки текущего филиала
void Library::showInfo() const {
    std::cout << "\n=== Dobro pozhalovat v: " << name << " ===\n"; // Печатаем баннер-приветствие
    std::cout << "Vas obsluzhivaet bibliotekar: " << librarian.getName() << "\n"; // Показываем имя сотрудника
    std::cout << "------------------------------------------\n"; // Декоративная черта
}

// Реализация механики поиска книг в каталоге текущего филиала по названию или автору
void Library::search(const std::string& query) const {
    librarian.greet(); // Библиотекарь вежливо здоровается перед началом поиска по каталогу
    std::string lowerQuery = toLower(query); // Переводим поисковый запрос пользователя в нижний регистр
    bool found = false; // Локальный флаг: нашли ли мы хотя бы одно совпадение по каталогу

    std::cout << "\n[Naidennye sovpadeniya]:\n"; // Шапка для списка найденных совпадений
    for (const auto& book : catalog) { // Цикл range-based for: поочередно смотрим каждую книгу в векторе catalog
        // Проверяем: если нижний регистр названия книги ИЛИ нижний регистр автора содержит поисковый запрос
        if (toLower(book.getTitle()).find(lowerQuery) != std::string::npos ||
            toLower(book.getAuthor()).find(lowerQuery) != std::string::npos) {

            std::cout << "  - "; // Форматируем отступ для списка в консоли
            book.printInfo(); // Вызываем метод вывода параметров (название и автор) у самого объекта книги
            // Выводим текущий статус доступности книги на основе тернарного оператора ? :
            std::cout << " | Status: " << (book.getIsAvailable() ? "Dostupna" : "Uzhe vydana") << "\n";
            found = true; // Устанавливаем флаг, сигнализируя об успешном нахождении книги
        }
    }

    if (!found) { // Если цикл завершился, а флаг found остался false (совпадений не обнаружено)
        // Библиотекарь вежливо сообщает, что по такому запросу ничего нет
        librarian.announceError("po zaprosu '" + query + "' nichego ne naideno.");
    }
}

// Реализация логики выдачи книги посетителю на руки
void Library::borrowBook(const std::string& title) {
    std::string lowerTitle = toLower(title); // Приводим запрашиваемое название книги к нижнему регистру

    for (auto& book : catalog) { // Обходим каталог по ссылке auto&, чтобы иметь возможность изменять поля книг
        if (toLower(book.getTitle()) == lowerTitle) { // Если нашли точное совпадение по названию
            if (!book.getIsAvailable()) { // Проверяем поле доступности: если книга найдена, но уже выдана (false)
                // Библиотекарь вежливо сообщает, что книга сейчас у другого читателя
                librarian.announceError("kniga \"" + book.getTitle() + "\" seichas na rukah u drugogo chitatelya.");
                return; // Прерываем выполнение метода
            }
            book.setIsAvailable(false); // Книга была свободна: переключаем её статус в положение "выдана" (false)
            // Библиотекарь подтверждает успешную выдачу книги читателю домой
            librarian.confirmAction("Vi vzyali knigu \"" + book.getTitle() + "\". Pozhaluista, vernite ee v srok.");
            return; // Успешно выходим из метода после завершения транзакции
        }
    }
    // Если цикл завершился, а функция не прервалась — такой книги вообще нет в фонде этого филиала
    librarian.announceError("knigi s nazvaniem \"" + title + "\" net v nashem kataloge.");
}

// Реализация логики возврата книги обратно в библиотеку
void Library::returnBook(const std::string& title) {
    std::string lowerTitle = toLower(title); // Превращаем название возвращаемой книги в нижний регистр для сравнения

    for (auto& book : catalog) { // Итерируемся по всему списку каталога книг
        if (toLower(book.getTitle()) == lowerTitle) { // Книга найдена в инвентарном списке филиала
            if (book.getIsAvailable()) { // Если статус доступности true (она и так на полке, её никто не брал)
                // Библиотекарь фиксирует логическую ошибку возврата
                librarian.announceError("kniga \"" + book.getTitle() + "\" uzhe nahoditsya na polke.");
                return; // Покидаем метод
            }
            book.setIsAvailable(true); // Меняем статус книги обратно в true (теперь она снова доступна для выдачи)
            // Библиотекарь вежливо благодарит читателя за возврат книги в фонд
            librarian.confirmAction("Kniga \"" + book.getTitle() + "\" uspeshno vozvrashena v fond. Spasibo!");
            return; // Завершаем выполнение метода
        }
    }
    // Если человек пытается вернуть книгу, которой никогда не было в инвентаре этого конкретного филиала
    librarian.announceError("kniga \"" + title + "\" ne prinadlezhit nashei biblioteke.");
}
