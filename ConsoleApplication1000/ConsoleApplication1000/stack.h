#pragma once

// Шаблонный узел стека на основе слайда 8
template <typename T>
struct elem {
    T value;                 // информационное поле стека
    elem<T>* next = nullptr; // адресное поле стека
};

// --- РЕАЛИЗАЦИЯ ФУНКЦИЙ ПРЯМО В ЗАГОЛОВКЕ ---

// Добавление элемента в стек (слайд 9)
template <typename T>
void push(elem<T>*& stack, T value) {
    elem<T>* newel = new elem<T>;
    newel->value = value;

    if (!stack) {
        stack = newel;
    }
    else {
        newel->next = stack;
        stack = newel;
    }
}

// Удаление элемента из стека с возвратом хранимого значения (слайд 9)
template <typename T>
bool pop(elem<T>*& stack, T& value) {
    if (!stack) return false;

    elem<T>* rem = stack;
    value = stack->value;
    stack = stack->next;
    delete rem;
    return true;
}

// Получение значения с вершины стека без удаления (слайд 10)
template <typename T>
const T* peek(const elem<T>* stack) {
    if (!stack) return nullptr;
    return &stack->value;
}

// Получаем следующий элемент стека (слайд 10)
template <typename T>
elem<T>* next_elem(const elem<T>* el) {
    if (el) return el->next;
    return nullptr;
}

// Удаление всего стека (слайд 10)
template <typename T>
void clear(elem<T>*& stack) {
    while (stack) {
        elem<T>* rem = stack;
        stack = stack->next;
        delete rem;
    }
}
