#pragma once
#include "Figure.hpp"

class Square : public Figure {
public:
    // Конструкторы
    Square() noexcept;
    Square(const Square& other) noexcept;
    Square(const std::initializer_list<std::pair<double, double>>& points);

    // Переопределённые методы
    Square& operator=(const Square& other);
    
    // Операторы
    friend std::ostream& operator<<(std::ostream& out, const Square& s);
    friend std::istream& operator>>(std::istream& in, Square& s);
};

// Операторы ввода и вывода
std::ostream& operator<<(std::ostream& out, const Square& s);
std::istream& operator>>(std::istream& in, Square& s);
