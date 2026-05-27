#pragma once
#include "stack.h"
#include "data_types.h"

// Прототип функции, реализующей главную бизнес-логику Задачи №2.
// Передаем указатель на стек по значению (elem<IntPair>*), так как саму вершину мы двигать не будем,
// а будем лишь перемещаться по элементам для их проверки и модификации.
void resetPairsBySum(elem<IntPair>* stack, int targetSum);
