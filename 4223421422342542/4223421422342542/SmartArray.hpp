#pragma once
#include <stdexcept>
#include <cstddef>

template <typename T>
class SmartArray {
private:
    T* data;                 // Указатель на динамический массив
    size_t currentSize;      // Текущее количество элементов
    size_t capacity;         // Вместимость выделенной памяти

    // Вспомогательный метод для изменения размера памяти при переполнении
    void resize(size_t newCapacity) {
        T* newData = new T[newCapacity];
        for (size_t i = 0; i < currentSize; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    // --- Конструкторы и деструктор ---

    // Создает пустой массив
    SmartArray() : data(nullptr), currentSize(0), capacity(0) {}

    // Создает массив с указанной начальной емкостью
    SmartArray(size_t initialCapacity) : currentSize(0), capacity(initialCapacity) {
        data = (capacity > 0) ? new T[capacity] : nullptr;
    }

    // Конструктор копирования
    SmartArray(const SmartArray& other) : currentSize(other.currentSize), capacity(other.capacity) {
        data = (capacity > 0) ? new T[capacity] : nullptr;
        for (size_t i = 0; i < currentSize; ++i) {
            data[i] = other.data[i];
        }
    }

    // Деструктор
    ~SmartArray() {
        delete[] data;
    }

    // --- Операторы ---

    // Доступ по индексу с проверкой границ
    T& operator[](size_t index) {
        if (index >= currentSize) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[index];
    }

    // Константная версия оператора доступа для read-only объектов
    const T& operator[](size_t index) const {
        if (index >= currentSize) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[index];
    }

    // Оператор присваивания
    SmartArray& operator=(const SmartArray& other) {
        if (this != &other) {
            delete[] data;
            currentSize = other.currentSize;
            capacity = other.capacity;
            data = (capacity > 0) ? new T[capacity] : nullptr;
            for (size_t i = 0; i < currentSize; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    // --- Основные методы ---

    // Добавление элемента в конец
    void push_back(const T& value) {
        if (currentSize >= capacity) {
            size_t newCapacity = (capacity == 0) ? 4 : capacity * 2;
            resize(newCapacity);
        }
        data[currentSize++] = value;
    }

    // Удаление последнего элемента
    void pop_back() {
        if (currentSize > 0) {
            currentSize--;
        }
    }

    // Доступ к последнему элементу
    T& back() {
        if (currentSize == 0) {
            throw std::underflow_error("Array is empty");
        }
        return data[currentSize - 1];
    }

    // Получение текущего размера
    size_t size() const {
        return currentSize;
    }

    // Проверка на пустоту
    bool empty() const {
        return currentSize == 0;
    }

    // Очистка массива
    void clear() {
        currentSize = 0;
    }

    // --- Расширенные методы ---

    // Вставка элемента по индексу
    void insert(size_t index, const T& value) {
        if (index > currentSize) {
            throw std::out_of_range("Index out of bounds");
        }
        if (currentSize >= capacity) {
            size_t newCapacity = (capacity == 0) ? 4 : capacity * 2;
            resize(newCapacity);
        }
        for (size_t i = currentSize; i > index; --i) {
            data[i] = data[i - 1];
        }
        data[index] = value;
        currentSize++;
    }

    // Удаление элемента по индексу
    void erase(size_t index) {
        if (index >= currentSize) {
            throw std::out_of_range("Index out of bounds");
        }
        for (size_t i = index; i < currentSize - 1; ++i) {
            data[i] = data[i + 1];
        }
        currentSize--;
    }

    // --- Алгоритмы поиска ---

    // Поиск значения (возвращает индекс или -1)
    int find(const T& value) {
        for (size_t i = 0; i < currentSize; ++i) {
            if (data[i] == value) {
                return static_cast<int>(i);
            }
        }
        return -1;
    }

    // --- Итераторы (простая реализация на указателях) ---
    T* begin() { return data; }
    T* end() { return data + currentSize; }
    const T* begin() const { return data; }
    const T* end() const { return data + currentSize; }
};
