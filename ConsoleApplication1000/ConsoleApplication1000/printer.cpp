#include "printer.h"
#include <iostream>

// Вывод целочисленного стека
void printStack(const elem<int>* stack) {
    const elem<int>* curr = stack;
    while (curr) {
        const int* val = peek(curr); // слайд 11
        std::cout << *val << " ";
        curr = next_elem(curr);     // слайд 11
    }
    std::cout << std::endl;
}

// Вывод стека пользовательских структур данных
void printStack(const elem<Student>* stack) {
    const elem<Student>* curr = stack;
    while (curr) {
        const Student* stdnt = peek(curr);
        std::cout << "{" << stdnt->name << ": " << stdnt->grade << "} ";
        curr = next_elem(curr);
    }
    std::cout << std::endl;
}
