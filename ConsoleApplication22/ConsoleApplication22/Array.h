#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>

class Array {
private:
    int* data;
    size_t size;
    static int instanceCount;

public:
    Array();
    explicit Array(size_t s);
    Array(const Array& other);
    ~Array();

    void fill();
    void display() const;
    void resize(size_t newSize);
    void sortArray();                    // переименовано (было sort)
    int getMin() const;                  // переименовано (было min)
    int getMax() const;                  // переименовано (было max)

    size_t getSize() const;
    static int getInstanceCount();
    Array& operator=(const Array& other);
    int& operator[](size_t index);
};

#endif