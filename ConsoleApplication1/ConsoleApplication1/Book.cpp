#include "Book.h" // Подключение собственного заголовочного файла класса Book
#include <iostream> // Подключение библиотеки для работы с потоком вывода (std::cout)

// Реализация конструктора через список инициализации (по умолчанию книга доступна: true)
Book::Book(std::string t, std::string a) : title(t), author(a), isAvailable(true) {}

// Реализация геттера для получения названия книги
std::string Book::getTitle() const {
    return title; // Возвращаем скрытое значение поля title
}

// Реализация геттера для получения автора книги
std::string Book::getAuthor() const {
    return author; // Возвращаем скрытое значение поля author
}

// Реализация геттера для проверки, свободна ли книга
bool Book::getIsAvailable() const {
    return isAvailable; // Возвращаем логическое значение поля isAvailable
}

// Реализация сеттера для переключения доступности книги
void Book::setIsAvailable(bool status) {
    isAvailable = status; // Присваиваем новое значение из параметра status полю isAvailable
}

// Реализация метода вывода карточки книги
void Book::printInfo() const {
    // Печатаем название книги в кавычках и автора в круглых скобках
    std::cout << "\"" << title << "\" (Avtor: " << author << ")";
}
