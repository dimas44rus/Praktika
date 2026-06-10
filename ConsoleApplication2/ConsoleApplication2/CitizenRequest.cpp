#include "CitizenRequest.h" // Подключение собственного заголовочного файла с объявлениями полей и методов класса.

CitizenRequest::CitizenRequest(int id, const std::string& citizenName, const std::string& text) // Реализация конструктора класса с передачей параметров по ссылке для экономии памяти.
    : id(id), citizenName(citizenName), text(text), answer("Нет ответа"), isResolved(false) {
} // Список инициализации: присваиваем внутренним полям значения аргументов и задаем дефолтный пустой статус ответа.

int CitizenRequest::getId() const { // Реализация константного геттера для безопасного чтения ID.
    return id; // Возвращаем значение приватного поля id вызывающему коду.
} // Завершение тела метода getId.

std::string CitizenRequest::getCitizenName() const { // Реализация константного геттера имени гражданина.
    return citizenName; // Возвращаем значение приватной строки citizenName.
} // Завершение тела метода getCitizenName.

std::string CitizenRequest::getText() const { // Реализация константного геттера текста обращения.
    return text; // Возвращаем значение приватной строки text.
} // Завершение тела метода getText.

std::string CitizenRequest::getAnswer() const { // Реализация константного геттера ответа сотрудника.
    return answer; // Возвращаем значение приватной строки answer.
} // Завершение тела метода getAnswer.

bool CitizenRequest::getStatus() const { // Реализация константного геттера статуса решения.
    return isResolved; // Возвращаем логическое значение флага завершенности обращения.
} // Завершение тела метода getStatus.

void CitizenRequest::setAnswer(const std::string& officialAnswer) { // Реализация метода для добавления официального ответа.
    answer = officialAnswer; // Перезаписываем дефолтную строку "Нет ответа" переданным аргументом от сотрудника.
    isResolved = true; // Принудительно переключаем флаг решения в состояние true (обращение рассмотрено).
} // Завершение тела метода setAnswer.
