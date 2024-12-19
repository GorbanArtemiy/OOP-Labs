#pragma once
#include "Figure.hpp"

class Triangle : public Figure {
public:
    // Конструкторы
    Triangle() noexcept;
    Triangle(const Triangle& other) noexcept;
    Triangle(const std::initializer_list<std::pair<double, double>>& points);

    // Переопределённые методы
    Triangle& operator=(const Triangle& other);
    
    // Операторы
    friend std::ostream& operator<<(std::ostream& out, const Triangle& t);
    friend std::istream& operator>>(std::istream& in, Triangle& t);
};

// Операторы ввода и вывода
std::ostream& operator<<(std::ostream& out, const Triangle& t);
std::istream& operator>>(std::istream& in, Triangle& t);
