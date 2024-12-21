#pragma once
#include <iostream>
#include <type_traits>
#include <cmath>
#include <stdexcept>

// Concept для проверки, что тип является скалярным
template <typename T>
concept Scalar = std::is_arithmetic_v<T>;

// Шаблонный класс Point с проверкой, что T — это скалярный тип
template <Scalar T>
class Point {
public:
    // Конструкторы
    Point() = default;

    Point(T number) noexcept
        : x_(number), y_(number) {}

    Point(T x, T y) noexcept
        : x_(x), y_(y) {}

    Point(const std::pair<T, T>& p) noexcept
        : x_(p.first), y_(p.second) {}

    Point(const Point<T>& other) noexcept
        : x_(other.x_), y_(other.y_) {}

    Point(Point<T>&& other) noexcept
        : x_(other.x_), y_(other.y_) {
        other.x_ = T{};
        other.y_ = T{};
    }

    ~Point() = default;

    // Оператор копирования
    Point<T>& operator=(const Point<T>& other) {
        x_ = other.x_;
        y_ = other.y_;
        return *this;
    }

    // Арифметические операторы
    Point<T> operator+(const Point<T>& other) const {
        return Point(x_ + other.x_, y_ + other.y_);
    }

    Point<T>& operator+=(const Point<T>& other) {
        x_ += other.x_;
        y_ += other.y_;
        return *this;
    }

    Point<T> operator-(const Point<T>& other) const {
        return Point<T>(x_ - other.x_, y_ - other.y_);
    }

    Point<T>& operator-=(const Point<T>& other) {
        x_ -= other.x_;
        y_ -= other.y_;
        return *this;
    }

    Point<T> operator*(T scalar) const {
        return Point<T>(x_ * scalar, y_ * scalar);
    }

    Point<T>& operator*=(T scalar) {
        x_ *= scalar;
        y_ *= scalar;
        return *this;
    }

    Point<T> operator/(T scalar) const {
        if (scalar == 0.0) {
            throw std::runtime_error("Division Point by zero.");
        }
        return Point<T>(x_ / scalar, y_ / scalar);
    }

    Point<T>& operator/=(T scalar) {
        if (scalar == 0.0) {
            throw std::runtime_error("Division Point by zero.");
        }
        x_ /= scalar;
        y_ /= scalar;
        return *this;
    }

    // Операторы сравнения
    bool operator==(const Point<T>& other) const {
        return x_ == other.x_ && y_ == other.y_;
    }

    bool operator<(const Point<T>& other) const {
        return x_ < other.x_ && y_ < other.y_;
    }

    bool operator<=(const Point<T>& other) const {
        return x_ <= other.x_ && y_ <= other.y_;
    }

    bool operator>(const Point<T>& other) const {
        return x_ > other.x_ && y_ > other.y_;
    }

    bool operator>=(const Point<T>& other) const {
        return x_ >= other.x_ && y_ >= other.y_;
    }

    // Операторы квадратных скобок для доступа к координатам
    T& operator[](int index) {
        if (index == 0) return x_;
        if (index == 1) return y_;
        throw std::out_of_range("Index out of range");
    }

    T operator[](int index) const {
        if (index == 0) return x_;
        if (index == 1) return y_;
        throw std::out_of_range("Index out of range");
    }

    // Вычисление длины вектора
    T Length() const {
        return std::sqrt(Dot(*this, *this));
    }

    // Угол между векторами
    T AngleToPoint(const Point<T>& other) const {
        T cos_theta = Dot(*this, other) / (this->Length() * other.Length());
        T theta = std::acos(cos_theta);

        if (Cross(*this, other) < 0) {
            theta = 2 * M_PI - theta;
        }

        return theta;
    }

    // Оператор приведения к std::pair
    operator std::pair<T, T>() const {
        return std::pair<T, T>{x_, y_};
    }

    // Операторы ввода и вывода
    friend std::ostream& operator<<(std::ostream& out, const Point<T>& p) {
        out << "Point(" << p[0] << ", " << p[1] << ")";
        return out;
    }
    friend std::istream& operator>>(std::istream& in, Point<T>& p) {
        in >> p.x_ >> p.y_;
        return in;
    }

private:
    T x_ = T{};
    T y_ = T{};
};

// Скалярное произведение
template <Scalar T>
T Dot(const Point<T>& u, const Point<T>& v) {
    return u[0] * v[0] + u[1] * v[1];
}

// Векторное произведение для Point (z-компонента векторного произведения)
template <Scalar T>
T Cross(const Point<T>& u, const Point<T>& v) {
    return u[0] * v[1] - u[1] * v[0];
}

// Расстояние от точки до прямой, заданной двумя точками
template <Scalar T>
T DistanceDotLine(const Point<T>& Dot, const Point<T>& first, const Point<T>& second) {
    return std::fabs(Cross(first - Dot, second - Dot)) / (first - second).Length();
}
