#include "asdf.h"
#include <iostream>
#include <iomanip>
using namespace std;

asdf::asdf(double w, double h)
{
    if (w > 0)
        width = w;
    else
        width = 1.0;

    if (h > 0)
        height = h;
    else
        height = 1.0;
}

// ЭТОТ МЕТОД ДОЛЖЕН БЫТЬ!
void asdf::printInfo() const
{
    cout << fixed << setprecision(1);
    cout << "Прямоугольник: " << width << " x " << height << endl;
    cout << "Площадь: " << getArea() << endl;
    cout << "Периметр: " << getPerimeter() << endl;

    if (isSquare())
        cout << "Является квадратом: да" << endl;
    else
        cout << "Является квадратом: нет" << endl;
}