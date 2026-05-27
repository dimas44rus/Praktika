#include <iostream>
#include "stack.h"
#include "data_types.h"
#include "printer.h"
#include "tester.h"
#include <Windows.h>

using namespace std;

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // --- ТЕСТ 1: Целочисленный стек (как в презентации) ---
    cout << "--- Тестирование стека <int> ---" << endl;
    elem<int>* myIntStack = nullptr;

    fillDemoIntStack(myIntStack);

    cout << "Элементы стека: ";
    printStack(myIntStack); // Выведет: 9 8 7 6 5 4 3 2 1 0

    int poppedValue;
    if (pop(myIntStack, poppedValue)) {
        cout << "Успешно извлечена вершина: " << poppedValue << endl;
    }

    cout << "Стек после извлечения: ";
    printStack(myIntStack);
    clear(myIntStack);


    // --- ТЕСТ 2: Шаблонный стек со структурой Student ---
    cout << "\n--- Тестирование стека <Student> ---" << endl;
    elem<Student>* myStudentStack = nullptr;

    fillDemoStudentStack(myStudentStack);

    cout << "Элементы стека студентов: ";
    printStack(myStudentStack);

    clear(myStudentStack);
    return 0;
}
