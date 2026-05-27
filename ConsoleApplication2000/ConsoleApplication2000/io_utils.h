#pragma once
#include "stack.h"
#include "data_types.h"

// Прототип функции автоматической генерации случайных чисел и добавления их в стек
void generatePairStack(elem<IntPair>*& stack, int count);

// Прототип функции безопасного вывода всего содержимого стека на экран
void printPairStack(const elem<IntPair>* stack);
