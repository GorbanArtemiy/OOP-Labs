#pragma once
#include "Figure.hpp"

class Rectangle : public Figure {
public:
    // Конструкторы
    Rectangle() noexcept;
    Rectangle(const Rectangle& other) noexcept;
    Rectangle(const std::initializer_list<std::pair<double, double>>& points);

    // Переопределённые методы
    Rectangle& operator=(const Rectangle& other);
    
    // Операторы
    friend std::ostream& operator<<(std::ostream& out, const Rectangle& s);
    friend std::istream& operator>>(std::istream& in, Rectangle& s);
};

// Операторы ввода и вывода
std::ostream& operator<<(std::ostream& out, const Rectangle& s);
std::istream& operator>>(std::istream& in, Rectangle& s);
