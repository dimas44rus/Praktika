#include <iostream>
#include <string>
#include <stdexcept>

template <typename T>
class SmartArray {
private:
    T* data;                 // Указатель на динамический массив
    size_t current_size;     // Текущее количество элементов
    size_t capacity;         // Выделенная память (емкость)

    // Вспомогательный метод для изменения размера памяти
    void resize(size_t newCapacity) {
        T* newData = new T[newCapacity];
        for (size_t i = 0; i < current_size; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    // Конструктор по умолчанию: создает пустой массив
    SmartArray() : data(nullptr), current_size(0), capacity(0) {}

    // Конструктор с указанной начальной емкостью
    SmartArray(size_t initialCapacity) : current_size(0), capacity(initialCapacity) {
        data = capacity > 0 ? new T[capacity] : nullptr;
    }

    // Конструктор копирования
    SmartArray(const SmartArray& other) : current_size(other.current_size), capacity(other.capacity) {
        data = capacity > 0 ? new T[capacity] : nullptr;
        for (size_t i = 0; i < current_size; ++i) {
            data[i] = other.data[i];
        }
    }

    // Деструктор
    ~SmartArray() {
        delete[] data;
    }

    // Оператор присваивания
    SmartArray& operator=(const SmartArray& other) {
        if (this != &other) {
            delete[] data;
            current_size = other.current_size;
            capacity = other.capacity;
            data = capacity > 0 ? new T[capacity] : nullptr;
            for (size_t i = 0; i < current_size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    // Доступ по индексу с проверкой границ
    T& operator[](size_t index) {
        if (index >= current_size) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[index];
    }

    // Константная версия оператора доступа по индексу
    const T& operator[](size_t index) const {
        if (index >= current_size) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[index];
    }

    // Добавление элемента в конец
    void push_back(const T& value) {
        if (capacity == 0) {
            resize(1);
        }
        else if (current_size >= capacity) {
            resize(capacity * 2);
        }
        data[current_size++] = value;
    }

    // Удаление последнего элемента
    void pop_back() {
        if (empty()) {
            throw std::underflow_error("Array is empty");
        }
        current_size--;
    }

    // Доступ к последнему элементу
    T& back() {
        if (empty()) {
            throw std::underflow_error("Array is empty");
        }
        return data[current_size - 1];
    }

    // Получение текущего размера
    size_t size() const {
        return current_size;
    }

    // Проверка на пустоту
    bool empty() const {
        return current_size == 0;
    }

    // Очистка массива
    void clear() {
        delete[] data;
        data = nullptr;
        current_size = 0;
        capacity = 0;
    }

    // Вставка элемента по индексу
    void insert(size_t index, const T& value) {
        if (index > current_size) {
            throw std::out_of_range("Index out of bounds");
        }
        if (current_size >= capacity) {
            resize(capacity == 0 ? 1 : capacity * 2);
        }
        for (size_t i = current_size; i > index; --i) {
            data[i] = data[i - 1];
        }
        data[index] = value;
        current_size++;
    }

    // Удаление элемента по индексу
    void erase(size_t index) {
        if (index >= current_size) {
            throw std::out_of_range("Index out of bounds");
        }
        for (size_t i = index; i < current_size - 1; ++i) {
            data[i] = data[i + 1];
        }
        current_size--;
    }

    // Поиск значения (линейный поиск, возвращает индекс или -1)
    int find(const T& value) const {
        for (size_t i = 0; i < current_size; ++i) {
            if (data[i] == value) {
                return static_cast<int>(i);
            }
        }
        return -1;
    }

    // --- Реализация итератора (для продвинутых) ---
    class Iterator {
    private:
        T* ptr;
    public:
        Iterator(T* p) : ptr(p) {}

        T& operator*() { return *ptr; }

        Iterator& operator++() { // Префиксный инкремент
            ptr++;
            return *this;
        }

        Iterator operator++(int) { // Постфиксный инкремент
            Iterator temp = *this;
            ptr++;
            return temp;
        }

        bool operator==(const Iterator& other) const { return ptr == other.ptr; }
        bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
    };

    Iterator begin() { return Iterator(data); }
    Iterator end() { return Iterator(data + current_size); }
};

int main() {
    // Работа с целыми числами
    SmartArray<int> intArray;
    for (int i = 1; i <= 10; i++) {
        intArray.push_back(i * 10);
    }
    std::cout << "Size: " << intArray.size() << std::endl;

    // Поиск элемента
    int index = intArray.find(50);
    if (index != -1) {
        std::cout << "Found 50 at index: " << index << std::endl;
    }

    // Демонстрация работы итератора и range-based for цикла
    std::cout << "Elements: ";
    for (int val : intArray) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // Работа со строками
    SmartArray<std::string> strArray;
    strArray.push_back("Hello");
    strArray.push_back("World");
    strArray.push_back("C++");

    std::cout << "Second string: " << strArray[1] << std::endl;

    return 0;
}
