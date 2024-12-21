#include "../include/Point.hpp"
#include <cmath>

// Конструкторы
Point::Point() noexcept = default;

Point::Point(double x, double y) noexcept : x_(x), y_(y) {}

Point::Point(double x) noexcept : x_(x), y_(0.0) {}

Point::Point(const std::pair<double, double>& point) noexcept
  : x_(point.first), y_(point.second) {}

// Конструктор копирования и перемещения
Point::Point(const Point& other) noexcept = default;

Point::Point(Point&& other) noexcept = default;

// Оператор присваивания
Point& Point::operator=(const Point& other) = default;

Point& Point::operator=(Point&& other) noexcept = default;

// Управление координатами
void Point::Set(double x, double y) noexcept {
    x_ = x;
    y_ = y;
}

std::pair<double, double> Point::Get() const noexcept { return {x_, y_}; }

double Point::GetX() const noexcept { return x_; }

double Point::GetY() const noexcept { return y_; }

// Арифметика
double Point::Length() const noexcept { return std::sqrt(x_ * x_ + y_ * y_); }

Point Point::operator+(const Point& other) const {
    return Point(x_ + other.x_, y_ + other.y_);
}

Point Point::operator-(const Point& other) const {
    return Point(x_ - other.x_, y_ - other.y_);
}

Point Point::operator*(double number) const {
    return Point(x_ * number, y_ * number);
}

Point operator/(const Point& point, double number) {
    return Point(point.x_ / number, point.y_ / number);
}

Point& Point::operator+=(const Point& other) {
    x_ += other.x_;
    y_ += other.y_;
    return *this;
}

Point& Point::operator-=(const Point& other) {
    x_ -= other.x_;
    y_ -= other.y_;
    return *this;
}

Point& Point::operator*=(double number) {
    x_ *= number;
    y_ *= number;
    return *this;
}

Point& Point::operator/=(double number) {
    x_ /= number;
    y_ /= number;
    return *this;
}

// Сравнения
bool Point::operator==(const Point& other) const {
    return this->x_ == other.x_ and this->y_ == other.y_;
}

bool Point::operator!=(const Point& other) const {
    return this->x_ != other.x_ or this->y_ != other.y_;
}

// Ввод-вывод
std::ostream& operator<<(std::ostream& out, const Point& point) {
    out << point.x_ << ' ' << point.y_;
    return out;
}

std::istream& operator>>(std::istream& in, Point& point) {
    in >> point.x_ >> point.y_;
    return in;
}