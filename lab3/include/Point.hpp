#pragma once
#include <utility>
#include <iostream>

// Класс двумерной точки (а вообще радиус вектора)
class Point {
public:
    // Конструкторы
    Point() = default;
    Point(double number) noexcept;
    Point(double x, double y) noexcept;
    Point(const std::pair<double, double>& p) noexcept;
    Point(const Point& other) noexcept;
    Point(Point&& other) noexcept;
    ~Point() = default;

    // Арифметические операторы
    Point operator+(const Point& other) const;
    Point& operator+=(const Point& other);
    Point operator-(const Point& other) const;
    Point& operator-=(const Point& other);
    Point operator*(double scalar) const;
    Point& operator*=(double scalar);
    Point operator/(double scalar) const;
    Point& operator/=(double scalar);

    // Операторы сравнения
    bool operator==(const Point& other) const;
    bool operator<(const Point& other) const;
    bool operator<=(const Point& other) const;
    bool operator>(const Point& other) const;
    bool operator>=(const Point& other) const;

    // Оператор копирования
    Point& operator=(const Point& other);

    // Операторы квадратных скобочек для доступа к координатам
    double& operator[](int index);
    double operator[](int index) const;

    // Оператор приведения к std::pair
    operator std::pair<double, double>() const;

    // Операторы ввода и вывода
    friend std::ostream& operator<<(std::ostream& out, const Point& p);
    friend std::istream& operator>>(std::istream& in, Point& p);

    // Вычисление длины вектора
    double Length() const;

    // Угол между векторами, заметаемый, при вращении вектора *this против часовой стрелки до вектора other
    double AngleToPoint(const Point& other) const;

private:
    double x_ = double{};
    double y_ = double{};
};

// Операторы ввода и вывода
std::ostream& operator<<(std::ostream& out, const Point& p);
std::istream& operator>>(std::istream& in, Point& p);

// Скалярное произведение
double Dot(const Point& u, const Point& v);

// Векторное произведение для Point (то есть z-компонента векторного произведения)
double Cross(const Point& u, const Point& v);

// Расстояние от точки до прямой, заданной двумя точками
double DistanceDotLine(const Point& dot, const Point& first, const Point& second);
