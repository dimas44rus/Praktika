#pragma once

class asdf
{
private:
    double width;
    double height;

public:
    asdf(double w, double h);

    double getWidth() const { return width; }
    double getHeight() const { return height; }
    double getArea() const { return width * height; }
    double getPerimeter() const { return 2 * (width + height); }
    bool isSquare() const { return width == height; }

    void printInfo() const;  // Объявление метода
};