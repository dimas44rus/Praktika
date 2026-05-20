#ifndef STRING_MEMORY_H
#define STRING_MEMORY_H

#include <string>

class StringMemory {
private:
    std::string buffer; // Внутренний строковый буфер

public:
    void buildAndShrink(); // Метод для Задачи 7 (push/pop_back)
    void clearAndVerify(); // Метод для Задачи 9 (.clear, .empty)
};

#endif
