#pragma warning(disable: 4996)
#include "Array.h"
#include <algorithm>

int Array::instanceCount = 0;

Array::Array() : size(0), data(nullptr) {
    instanceCount++;
}

Array::Array(size_t s) : size(s) {
    data = new int[size]();
    instanceCount++;
}

Array::Array(const Array& other) : size(other.size) {
    data = new int[size];
    for (size_t i = 0; i < size; i++) {
        data[i] = other.data[i];
    }
    instanceCount++;
}

Array::~Array() {
    delete[] data;
    instanceCount--;
}

void Array::fill() {
    std::cout << "Введите " << size << " элементов: ";
    for (size_t i = 0; i < size; i++) {
        std::cin >> data[i];
    }
}

void Array::display() const {
    std::cout << "Массив: ";
    for (size_t i = 0; i < size; i++) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;
}

void Array::resize(size_t newSize) {
    int* newData = new int[newSize]();
    size_t copySize = (newSize < size) ? newSize : size;
    for (size_t i = 0; i < copySize; i++) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
    size = newSize;
}

void Array::sortArray() {
    std::sort(data, data + size);
}

int Array::getMin() const {
    if (size == 0) return 0;
    int minVal = data[0];
    for (size_t i = 1; i < size; i++) {
        if (data[i] < minVal) minVal = data[i];
    }
    return minVal;
}

int Array::getMax() const {
    if (size == 0) return 0;
    int maxVal = data[0];
    for (size_t i = 1; i < size; i++) {
        if (data[i] > maxVal) maxVal = data[i];
    }
    return maxVal;
}

size_t Array::getSize() const {
    return size;
}

int Array::getInstanceCount() {
    return instanceCount;
}

Array& Array::operator=(const Array& other) {
    if (this != &other) {
        delete[] data;
        size = other.size;
        data = new int[size];
        for (size_t i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }
    return *this;
}

int& Array::operator[](size_t index) {
    return data[index];
}