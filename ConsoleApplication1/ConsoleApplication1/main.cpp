#include <iostream> // Подключение библиотеки потокового ввода-вывода (std::cin, std::cout)
#include <vector> // Подключение динамического вектора std::vector для организации единой сети библиотек
#include "Library.h" // Подключение интерфейса класса Library (он автоматически подтянет Book.h и Librarian.h)

int main() { // Точка входа, с которой операционная система начинает выполнение приложения
    // Объявляем вектор (динамический массив) для хранения нашей единой сети из 3-х независимых филиалов библиотек
    std::vector<Library> network;

    // 1. Создаем и добавляем в сеть первый объект филиала — Центральную библиотеку с ее фондом классики
    network.push_back(Library(
        "Centralnaya Klassicheskaya Biblioteka", // Передаем название филиала
        Librarian("Tatiana Vasilievna"), // Создаем объект библиотекаря для этого филиала прямо в аргументе
        { Book("Prestuplenie i nakazanie", "Fyodor Dostoevsky"), // Инициализируем стартовый список книг
          Book("Voina i mir", "Leo Tolstoy"),
          Book("Master i Margarita", "Mikhail Bulgakov") }
    ));

    // 2. Создаем и добавляем в сеть второй филиал — Техническую библиотеку со специализированной IT-литературой
    network.push_back(Library(
        "Gorodskaya Nauchno-Tehnicheskaya Biblioteka",
        Librarian("Innokentiy Petrovich"),
        { Book("Chistiy kod", "Robert Martin"),
          Book("Grokkaem algoritmy", "Aditya Bhargava"),
          Book("Kratkaya istoriya vremeni", "Stephen Hawking") }
    ));

    // 3. Создаем и добавляем в сеть третий филиал — Молодежную фэнтези-библиотеку
    network.push_back(Library(
        "Molodezhnaya Biblioteka Fantasy",
        Librarian("Alena Dmitrievna"),
        { Book("Harry Potter", "J.K. Rowling"),
          Book("Vlastelin Kolec", "J.R.R. Tolkien"),
          Book("Hroniki Narnii", "C.S. Lewis") }
    ));

    // Главный цикл работы программы для отрисовки внешнего меню выбора нужного филиала
    while (true) {
        std::cout << "\n==========================================\n";
        std::cout << "    EDINAYA INFORMACIONNAYA SISTEMA GORODA \n"; // Главный баннер системы
        std::cout << "==========================================\n";
        std::cout << "Выберите biblioteku dlya posesheniya:\n"; // Запрос выбора филиала

        // Циклом обходим весь вектор сети библиотек, чтобы динамически вывести на экран доступные варианты
        for (size_t i = 0; i < network.size(); ++i) {
            std::cout << i + 1 << ". " << network[i].getName() << "\n"; // Нумерация вывода с 1 для удобства человека
        }
        std::cout << "0. Viyti iz sistemi\n"; // Опция корректного закрытия программы
        std::cout << "\nVvedite vash vibor: "; // Приглашение ввести число

        int libraryChoice; // Переменная для записи номера выбранной пользователем библиотеки
        if (!(std::cin >> libraryChoice)) { // Валидация: если пользователь ввел не число, а буквы
            std::cin.clear(); // Экстренно сбрасываем состояние ошибки потока ввода cin
            std::cin.ignore(10000, '\n'); // Полностью вычищаем буфер от мусора до символа конца строки
            std::cout << "Nekorrektniy vvod. Poprobuite eshe raz.\n"; // Выводим сообщение о неверном вводе
            continue; // Прерываем текущую итерацию цикла и возвращаем пользователя на экран главного меню
        }

        if (libraryChoice == 0) break; // Если пользователь выбрал 0, прерываем цикл while — программа успешно завершится

        // Защитная проверка: введенный номер должен строго попадать в диапазон существующих в сети библиотек
        if (libraryChoice < 1 || libraryChoice > static_cast<int>(network.size())) {
            std::cout << "Takoy biblioteki net. Poprobuite eshe raz.\n"; // Сообщаем об отсутствии филиала
            continue; // Перезапускаем цикл меню выбора
        }

        // По номеру извлекаем прямую ссылку на выбранную библиотеку из вектора (индекс смещен на -1)
        Library& currentLibrary = network[libraryChoice - 1];
        bool inLibrary = true; // Выставляем локальный флаг нахождения внутри выбранного филиала

        // Внутренний цикл: управление командами и действиями внутри конкретно посещенного филиала
        while (inLibrary) {
            currentLibrary.showInfo(); // Отрисовываем визитку филиала и узнаем, кто сейчас на смене из библиотекарей
            std::cout << "Dostupnye deistviya:\n"; // Меню доступных клиентоориентированных действий
            std::cout << "1. Naiti knigu (po avtoru ili nazvaniyu)\n";
            std::cout << "2. Vzyat knigu domoy\n";
            std::cout << "3. Vernut knigu\n";
            std::cout << "4. Smenit biblioteku\n"; // Пункт возврата на глобальную карту города
            std::cout << "\nViberite deistvie: "; // Приглашение к выбору операции

            int action; // Переменная для хранения номера операции
            if (!(std::cin >> action)) { // Снова защищаем ввод числового пункта меню от случайного ввода букв
                std::cin.clear(); // Очистка флага падения потока ввода std::cin
                std::cin.ignore(10000, '\n'); // Удаление накопленного мусора из системного буфера
                std::cout << "Nekorrektniy vvod.\n"; // Оповещение об ошибке ввода команды
                continue; // Начинаем текущую итерацию работы в библиотеке заново
            }
            std::cin.ignore(); // Выталкиваем из буфера символ перевода строки '\n', оставшийся после cin >>, чтобы getline работал корректно

            std::string query; // Переменная для записи текстовых параметров (поиск, названия книг)
            switch (action) { // Оператор множественного выбора ветвления switch по коду действия action
            case 1: // Сценарий поиска книги по каталогу
                std::cout << "Vvedite poiskoviy zapros (avtor ili nazvanie): ";
                std::getline(std::cin, query); // Считываем всю строку целиком вместе с пробелами
                currentLibrary.search(query); // Вызываем метод поиска у объекта текущей библиотеки
                break; // Прерывание выполнения текущего кейса switch

            case 2: // Сценарий взятия книги домой
                std::cout << "Vvedite nazvanie knigi, kotoruyu hotite vzyat: ";
                std::getline(std::cin, query); // Считываем точное название книги
                currentLibrary.borrowBook(query); // Вызываем метод выдачи книги у текущей библиотеки
                break;

            case 3: // Сценарий возврата книги в фонд архива
                std::cout << "Vvedite nazvanie vozvrashaemoy knigi: ";
                std::getline(std::cin, query); // Считываем название возвращаемой литературы
                currentLibrary.returnBook(query); // Вызываем метод приема возврата у библиотеки
                break;

            case 4: // Возврат на уровень меню выбора филиалов города
                inLibrary = false; // Сбрасываем флаг, внутренний цикл while(inLibrary) завершится
                break;

            default: // Если ввели число, но не из диапазона от 1 до 4
                std::cout << "Takogo deistviya ne sushestvuet.\n"; // Сообщаем о неверной команде
                break;
            }
        }
    }

    std::cout << "\nProgramma zavershena. Horoshego dnya!\n"; // Финальная вежливая реплика при выходе из системы (0)
    return 0; // Сигнализируем операционной системе об успешном завершении работы приложения
}
