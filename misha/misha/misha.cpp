#include <iostream>     // для cin, cout, cerr
#include <fstream>      // для ifstream, ofstream
#include <vector>       // для vector
#include <string>       // для string, getline
#include <algorithm>    // для transform
#include <iomanip>      // для setw, left
#include <Windows.h>    // для SetConsoleOutputCP

    class Book
{
public:
    Book() : id(0), title(""), author(""), year(0) {}  // конструктор по умолчанию

    Book(int id, std::string title, std::string author, int year)  // конструктор с параметрами
        : id(id), title(title), author(author), year(year) {
    }

    // Геттеры
    int getId() const { return id; }  // получить ID
    std::string getTitle() const { return title; }  // получить название
    std::string getAuthor() const { return author; }  // получить автора
    int getYear() const { return year; }  // получить год

    // Сеттеры
    void setId(int newId) { id = newId; }  // установить ID
    void setTitle(const std::string& newTitle) { title = newTitle; }  // установить название
    void setAuthor(const std::string& newAuthor) { author = newAuthor; }  // установить автора
    void setYear(int newYear) { year = newYear; }  // установить год

private:
    int id;                 // уникальный идентификатор
    std::string title;      // название книги
    std::string author;     // автор книги
    int year;               // год издания
};

// Перегрузка оператора вывода для книги
std::ostream& operator << (std::ostream& os, const Book& book)
{
    os << book.getId() << "|"          // выводим ID и разделитель
        << book.getTitle() << "|"      // выводим название и разделитель
        << book.getAuthor() << "|"     // выводим автора и разделитель
        << book.getYear();             // выводим год
    return os;  // возвращаем поток для цепочек
}

// Перегрузка оператора ввода для книги
std::istream& operator >> (std::istream& is, Book& book)
{
    int id, year;                       // временные переменные
    std::string title, author;          // временные строки
    char delimiter;                     // для разделителя '|'

    is >> id >> delimiter;              // читаем ID и разделитель
    std::getline(is, title, '|');       // читаем название до '|'
    std::getline(is, author, '|');      // читаем автора до '|'
    is >> year;                         // читаем год

    if (is)  // если чтение успешно
    {
        book.setId(id);                 // устанавливаем ID
        book.setTitle(title);           // устанавливаем название
        book.setAuthor(author);         // устанавливаем автора
        book.setYear(year);             // устанавливаем год
    }

    return is;  // возвращаем поток для цепочек
}

class LibraryCatalog
{
public:
    // Добавление новой книги
    void addBook(const Book& book)
    {
        books.push_back(book);          // добавляем в конец вектора
        std::cout << "Книга успешно добавлена!" << std::endl;  // сообщение
    }

    // Просмотр всех книг
    void displayAllBooks() const
    {
        if (books.empty())  // если каталог пуст
        {
            std::cout << "\nКаталог пуст." << std::endl;  // сообщение
            return;  // выходим из функции
        }

        std::cout << "\n" << std::string(70, '=') << std::endl;  // верхняя граница
        std::cout << std::left  // выравнивание по левому краю
            << std::setw(5) << "ID"       // ширина поля 5 символов
            << std::setw(30) << "Название"  // ширина поля 30 символов
            << std::setw(20) << "Автор"     // ширина поля 20 символов
            << std::setw(10) << "Год" << std::endl;  // ширина поля 10 символов
        std::cout << std::string(70, '-') << std::endl;  // разделитель

        for (const auto& book : books)  // перебираем все книги
        {
            std::cout << std::left  // выравнивание по левому краю
                << std::setw(5) << book.getId()      // ID с шириной 5
                << std::setw(30) << book.getTitle()  // название с шириной 30
                << std::setw(20) << book.getAuthor() // автор с шириной 20
                << std::setw(10) << book.getYear() << std::endl;  // год с шириной 10
        }
        std::cout << std::string(70, '=') << std::endl;  // нижняя граница
        std::cout << "Всего книг: " << books.size() << std::endl;  // количество
    }

    // Поиск книги по названию
    void searchByTitle(const std::string& title) const
    {
        std::vector<Book> results;  // вектор для результатов
        std::string titleLower = toLower(title);  // приводим запрос к нижнему регистру

        for (const auto& book : books)  // перебираем все книги
        {
            if (toLower(book.getTitle()).find(titleLower) != std::string::npos)  // если найдено
            {
                results.push_back(book);  // добавляем в результаты
            }
        }

        displaySearchResults(results, "названию", title);  // выводим результаты
    }

    // Поиск книги по автору
    void searchByAuthor(const std::string& author) const
    {
        std::vector<Book> results;  // вектор для результатов
        std::string authorLower = toLower(author);  // приводим запрос к нижнему регистру

        for (const auto& book : books)  // перебираем все книги
        {
            if (toLower(book.getAuthor()).find(authorLower) != std::string::npos)  // если найдено
            {
                results.push_back(book);  // добавляем в результаты
            }
        }

        displaySearchResults(results, "автору", author);  // выводим результаты
    }

    // Сохранение данных в файл
    bool saveToFile(const std::string& filename) const
    {
        std::ofstream outFile(filename);  // создаём выходной поток

        if (!outFile.is_open())  // если не открылся
        {
            std::cerr << "Ошибка: Не удалось открыть файл для записи!" << std::endl;  // ошибка
            return false;  // возвращаем false
        }

        for (const auto& book : books)  // перебираем все книги
        {
            outFile << book << std::endl;  // записываем книгу в файл
        }

        outFile.close();  // закрываем файл
        std::cout << "Данные успешно сохранены в файл '" << filename << "'" << std::endl;  // сообщение
        return true;  // возвращаем true
    }

    // Загрузка данных из файла
    bool loadFromFile(const std::string& filename)
    {
        std::ifstream inFile(filename);  // создаём входной поток

        if (!inFile.is_open())  // если не открылся
        {
            std::cerr << "Ошибка: Не удалось открыть файл для чтения!" << std::endl;  // ошибка
            return false;  // возвращаем false
        }

        books.clear();  // очищаем текущий каталог
        Book book;  // временная переменная

        while (inFile >> book)  // читаем книги из файла
        {
            books.push_back(book);  // добавляем в каталог
        }

        inFile.close();  // закрываем файл
        std::cout << "Данные успешно загружены из файла '" << filename << "'" << std::endl;  // сообщение
        std::cout << "Загружено книг: " << books.size() << std::endl;  // количество
        return true;  // возвращаем true
    }

    // Получение следующего доступного ID
    int getNextId() const
    {
        if (books.empty())  // если каталог пуст
            return 1;  // начинаем с 1

        int maxId = 0;  // переменная для максимального ID
        for (const auto& book : books)  // перебираем все книги
        {
            if (book.getId() > maxId)  // если нашли больше
                maxId = book.getId();  // обновляем максимум
        }
        return maxId + 1;  // возвращаем следующий ID
    }

    // Проверка, пуст ли каталог
    bool isEmpty() const
    {
        return books.empty();  // true если пуст, false если нет
    }

private:
    std::vector<Book> books;  // вектор для хранения книг

    // Вспомогательная функция для приведения строки к нижнему регистру
    static std::string toLower(const std::string& str)
    {
        std::string result = str;  // копируем строку
        std::transform(result.begin(), result.end(), result.begin(), ::tolower);  // преобразуем
        return result;  // возвращаем результат
    }

    // Отображение результатов поиска
    void displaySearchResults(const std::vector<Book>& results,
        const std::string& searchType,
        const std::string& query) const
    {
        if (results.empty())  // если ничего не найдено
        {
            std::cout << "\nКниги по " << searchType << " \"" << query << "\" не найдены." << std::endl;  // сообщение
            return;  // выходим
        }

        std::cout << "\n" << std::string(70, '=') << std::endl;  // верхняя граница
        std::cout << "Результаты поиска по " << searchType << ": \"" << query << "\"" << std::endl;  // заголовок
        std::cout << std::string(70, '-') << std::endl;  // разделитель

        for (const auto& book : results)  // перебираем результаты
        {
            std::cout << "ID: " << book.getId() << std::endl;  // выводим ID
            std::cout << "Название: " << book.getTitle() << std::endl;  // выводим название
            std::cout << "Автор: " << book.getAuthor() << std::endl;  // выводим автора
            std::cout << "Год: " << book.getYear() << std::endl;  // выводим год
            std::cout << std::string(40, '-') << std::endl;  // разделитель между книгами
        }
        std::cout << "Найдено книг: " << results.size() << std::endl;  // количество найденных
        std::cout << std::string(70, '=') << std::endl;  // нижняя граница
    }
};

// Функция для ввода целого числа с проверкой
int inputInt(const std::string& prompt)
{
    int value;  // переменная для значения
    std::cout << prompt;  // выводим приглашение
    std::cin >> value;  // читаем значение

    while (std::cin.fail())  // пока ввод некорректен
    {
        std::cin.clear();  // сбрасываем флаг ошибки
        std::cin.ignore(10000, '\n');  // очищаем буфер
        std::cout << "Ошибка: Введите целое число!" << std::endl;  // сообщение об ошибке
        std::cout << prompt;  // выводим приглашение снова
        std::cin >> value;  // читаем снова
    }

    std::cin.ignore(10000, '\n');  // очищаем буфер
    return value;  // возвращаем значение
}

// Функция для ввода строки
std::string inputString(const std::string& prompt)
{
    std::string value;  // переменная для строки
    std::cout << prompt;  // выводим приглашение
    std::getline(std::cin, value);  // читаем строку (с пробелами)
    return value;  // возвращаем строку
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);  // устанавливаем кодировку вывода UTF-8
    SetConsoleCP(CP_UTF8);  // устанавливаем кодировку ввода UTF-8
    LibraryCatalog catalog;  // создаём объект каталога
    const std::string dataFile = "library_catalog.txt";  // имя файла для хранения

    // Пытаемся загрузить существующие данные
    std::cout << "Загрузка каталога..." << std::endl;  // сообщение
    catalog.loadFromFile(dataFile);  // загружаем из файла

    int choice;  // переменная для выбора

    do  // цикл меню
    {
        // Отображение меню
        std::cout << "\n" << std::string(50, '=') << std::endl;  // верхняя граница
        std::cout << "    СИСТЕМА УПРАВЛЕНИЯ БИБЛИОТЕКОЙ" << std::endl;  // заголовок
        std::cout << std::string(50, '=') << std::endl;  // разделитель
        std::cout << "1. Добавить новую книгу" << std::endl;  // пункт 1
        std::cout << "2. Просмотреть все книги" << std::endl;  // пункт 2
        std::cout << "3. Найти книгу по названию" << std::endl;  // пункт 3
        std::cout << "4. Найти книгу по автору" << std::endl;  // пункт 4
        std::cout << "5. Сохранить данные в файл" << std::endl;  // пункт 5
        std::cout << "6. Загрузить данные из файла" << std::endl;  // пункт 6
        std::cout << "0. Выход" << std::endl;  // пункт 0
        std::cout << std::string(50, '-') << std::endl;  // разделитель

        choice = inputInt("Выберите действие: ");  // получаем выбор

        switch (choice)  // обрабатываем выбор
        {
        case 1: // Добавление книги
        {
            std::cout << "\n--- Добавление новой книги ---" << std::endl;  // заголовок
            std::string title = inputString("Введите название: ");  // ввод названия
            std::string author = inputString("Введите автора: ");  // ввод автора
            int year = inputInt("Введите год издания: ");  // ввод года

            Book newBook(catalog.getNextId(), title, author, year);  // создаём книгу
            catalog.addBook(newBook);  // добавляем в каталог
            break;  // выходим из switch
        }

        case 2: // Просмотр всех книг
            catalog.displayAllBooks();  // выводим все книги
            break;  // выходим из switch

        case 3: // Поиск по названию
        {
            if (catalog.isEmpty())  // если каталог пуст
            {
                std::cout << "\nКаталог пуст. Сначала добавьте книги." << std::endl;  // сообщение
                break;  // выходим из switch
            }
            std::string title = inputString("\nВведите название для поиска: ");  // ввод названия
            catalog.searchByTitle(title);  // ищем по названию
            break;  // выходим из switch
        }

        case 4: // Поиск по автору
        {
            if (catalog.isEmpty())  // если каталог пуст
            {
                std::cout << "\nКаталог пуст. Сначала добавьте книги." << std::endl;  // сообщение
                break;  // выходим из switch
            }
            std::string author = inputString("\nВведите автора для поиска: ");  // ввод автора
            catalog.searchByAuthor(author);  // ищем по автору
            break;  // выходим из switch
        }

        case 5: // Сохранение в файл
            catalog.saveToFile(dataFile);  // сохраняем в файл
            break;  // выходим из switch

        case 6: // Загрузка из файла
            catalog.loadFromFile(dataFile);  // загружаем из файла
            break;  // выходим из switch

        case 0: // Выход
        {
            std::cout << "\nЗавершение работы..." << std::endl;  // сообщение
            char save = '\0';  // переменная для ответа
            std::cout << "Сохранить изменения перед выходом? (y/n): ";  // вопрос
            std::cin >> save;  // читаем ответ

            if (save == 'y' || save == 'Y')  // если ответ 'y' или 'Y'
            {
                catalog.saveToFile(dataFile);  // сохраняем
            }
            std::cout << "До свидания!" << std::endl;  // прощание
            break;  // выходим из switch
        }

        default:  // неверный выбор
            std::cout << "\nОшибка: Неверный выбор! Попробуйте снова." << std::endl;  // сообщение
            break;  // выходим из switch
        }

    } while (choice != 0);  // повторяем пока choice не 0

    return 0;  // успешное завершение
}
