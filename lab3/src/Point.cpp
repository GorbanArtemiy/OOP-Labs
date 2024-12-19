#include "Point.hpp"
#include <utility>
#include <cmath>
#include <stdexcept>
#include <iostream>

// Конструкторы
Point::Point(double number) noexcept
  : x_(number)
  , y_(number)
{}

Point::Point(double x, double y) noexcept
  : x_(x)
  , y_(y)
{}

Point::Point(const std::pair<double, double>& p) noexcept
  : x_(p.first)
  , y_(p.second)
{}

Point::Point(const Point& other) noexcept
  : x_(other.x_)
  , y_(other.y_)
{}

Point::Point(Point&& other) noexcept
  : x_(other.x_)
  , y_(other.y_)
{
    other.x_ = 0;
    other.y_ = 0;
}

// Оператор копирования
Point& Point::operator=(const Point& other) {
    this->x_ = other.x_;
    this->y_ = other.y_;
    return *this;
}

// Арифметические операторы
Point Point::operator+(const Point& other) const {
    return Point(this->x_ + other.x_, this->y_ + other.y_);
}

Point& Point::operator+=(const Point& other) {
    this->x_ += other.x_;
    this->y_ += other.y_;
    return *this; 
}

Point Point::operator-(const Point& other) const {
    return Point(this->x_ - other.x_, this->y_ - other.y_);
}

Point& Point::operator-=(const Point& other) {
    this->x_ -= other.x_;
    this->y_ -= other.y_;
    return *this;
}

Point Point::operator*(double scalar) const {
    return Point(this->x_ * scalar, this->y_ * scalar);
}

Point& Point::operator*=(double scalar) {
    this->x_ *= scalar;
    this->y_ *= scalar;
    return *this;
}

Point Point::operator/(double scalar) const {
    if (scalar == 0.0) {
        throw std::runtime_error("Division Point by zero.");
    }
    return Point(this->x_ / scalar, this->y_ / scalar);
}

Point& Point::operator/=(double scalar) {
    if (scalar == 0.0) {
        throw std::runtime_error("Division Point by zero.");
    }
    this->x_ /= scalar;
    this->y_ /= scalar;
    return *this;
}

// Операторы сравнения
bool Point::operator==(const Point& other) const {
    return this->x_ == other.x_ and this->y_ == other.y_;
}

bool Point::operator<(const Point& other) const {
    return this->x_ < other.x_ and this->y_ < other.y_;
}

bool Point::operator<=(const Point& other) const {
    return this->x_ <= other.x_ and this->y_ <= other.y_;
}

bool Point::operator>(const Point& other) const {
    return this->x_ > other.x_ and this->y_ > other.y_;
}

bool Point::operator>=(const Point& other) const {
    return this->x_ >= other.x_ and this->y_ >= other.y_;
}

// Скалярное произведение
double Dot(const Point& u, const Point& v) {
    return u[0] * v[0] + u[1] * v[1];
}

// Векторное произведение для Point (то есть z-компонента векторного произведения)
double Cross(const Point& u, const Point& v) {
    return u[0] * v[1] - u[1] * v[0];
}

// Операторы квадратных скобочек для доступа к координатам
double& Point::operator[](int index) {
    if (index == 0) return x_;
    if (index == 1) return y_;
    throw std::out_of_range("Index out of range");
}

double Point::operator[](int index) const {
    if (index == 0) return x_;
    if (index == 1) return y_;
    throw std::out_of_range("Index out of range");
}

// Вычисление длины вектора
double Point::Length() const {
    return std::sqrt(Dot(*this, *this));
}

// Угол между векторами, заметаемый, при вращении вектора *this против часовой стрелки до вектора other
double Point::AngleToPoint(const Point& other) const {
    double cos_theta = Dot(*this, other) / (this->Length() * other.Length());
    double theta = std::acos(cos_theta);

    if (Cross(*this, other) < 0) {
        theta = 2 * M_PI - theta;
    }

    return theta;
}

// Оператор приведения к std::pair
Point::operator std::pair<double, double>() const {
    return std::pair<double, double>{x_, y_};
}

// Операторы ввода и вывода
std::ostream& operator<<(std::ostream& out, const Point& p) {
    out << "Point(" << p[0] << ", " << p[1] << ")";
    return out;
}

std::istream& operator>>(std::istream& in, Point& p) {
    in >> p.x_ >> p.y_;
    return in;
}

double DistanceDotLine(const Point& Dot, const Point& first, const Point& second) {
    return fabs(Cross(first - Dot, second - Dot)) / (first - second).Length();
}