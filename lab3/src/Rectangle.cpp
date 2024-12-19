#include "Rectangle.hpp"
#include <iostream>
#include <stdexcept>

// Конструкторы
Rectangle::Rectangle() noexcept : Figure(4) {}

Rectangle::Rectangle(const Rectangle& other) noexcept : Figure(other) {
    for (size_t i = 0; i < vertices_number_; ++i) {
        points_[i] = other.points_[i];
    }
}

Rectangle::Rectangle(const std::initializer_list<std::pair<double, double>>& points) : Rectangle() {
    if (points.size() != 4) {
        throw std::runtime_error("Trying initialize Rectangle with not 4 points.");
    }
    std::copy(points.begin(), points.end(), this->points_);
}

// Переопределённый оператор присваивания
Rectangle& Rectangle::operator=(const Rectangle& other) {
    if (this != &other) {
        std::copy(other.points_, other.points_ + other.vertices_number_, this->points_);
    }
    return *this;
}

// Операторы ввода/вывода
std::ostream& operator<<(std::ostream& out, const Rectangle& o) {
    out << "Rectangle(";
    for (size_t i = 0; i < o.vertices_number_; ++i) {
        out << o.points_[i];
        if (i < o.vertices_number_ - 1) {
            out << ", ";
        }
    }
    out << ")";
    return out;
}

std::istream& operator>>(std::istream& in, Rectangle& o) {
    for (size_t i = 0; i < o.vertices_number_; ++i) {
        in >> o.points_[i];
    }
    return in;
}
