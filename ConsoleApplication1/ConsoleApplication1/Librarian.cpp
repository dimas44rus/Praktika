#include "Librarian.h" // Подключение собственного заголовочного файла с прототипами класса
#include <iostream> // Подключение библиотеки потоков ввода-вывода (для std::cout)

// Конструктор: инициализирует имя библиотекаря строкой n с помощью списка инициализации
Librarian::Librarian(std::string n) : name(n) {}

// Реализация геттера для чтения приватной переменной имени
std::string Librarian::getName() const {
    return name; // Возвращаем строку name внешнему коду
}

// Реализация приветствия от лица библиотекаря (элемент клиентоориентированности)
void Librarian::greet() const {
    // Печатаем в консоль приветствие, используя имя конкретного библиотекаря
    std::cout << "[Bibliotekar " << name << "]: Zdravstvuite! Kakuyu knigu vi ishete?\n";
}

// Реализация метода для вывода вежливого сообщения об ошибке
void Librarian::announceError(const std::string& message) const {
    // Сообщаем причину неудачи, переданную в константной строке message
    std::cout << "[Bibliotekar " << name << "]: K sozhaleniyu, " << message << "\n";
}

// Реализация метода для вывода успешного подтверждения операции
void Librarian::confirmAction(const std::string& message) const {
    // Сообщаем об успешном выполнении действия (выдача или возврат книги)
    std::cout << "[Bibliotekar " << name << "]: Gotovo! " << message << "\n";
}
