#include "Figure.hpp"
#include <initializer_list>
#include <cmath>
#include <algorithm>
#include <utility>
#include <iostream>

// Конструкторы и деструктор
Figure::Figure() noexcept
    : vertices_number_(0)
    , points_(nullptr)
{}

Figure::Figure(size_t vertices_number) noexcept
    : vertices_number_(vertices_number)
    , points_(new Point[this->vertices_number_])
{}

Figure::Figure(const std::initializer_list<std::pair<double, double>>& points) noexcept
    : vertices_number_(points.size())
    , points_(new Point[this->vertices_number_]) 
{
    std::copy(points.begin(), points.end(), this->points_);
}

Figure::Figure(const Figure& other) noexcept
    : vertices_number_(other.vertices_number_)
    , points_(new Point[this->vertices_number_])
{
    std::copy(other.points_, other.points_ + other.vertices_number_, this->points_);
}

Figure::Figure(Figure&& other) noexcept
    : vertices_number_(other.vertices_number_)
    , points_(other.points_)
{
    other.vertices_number_ = 0;
    other.points_ = nullptr;
}

Figure::~Figure() noexcept {
    delete[] this->points_;
}

// Геттеры
std::pair<double, double> Figure::GetCenter() const noexcept {
    Point center;
    for (size_t i = 0; i < this->vertices_number_; ++i) {
        center += this->points_[i];
    }
    center /= this->vertices_number_;

    return static_cast<std::pair<double, double>>(center);
}

size_t Figure::GetVerticesNumber() const noexcept {
    return this->vertices_number_;
}

Point* Figure::GetVertices() noexcept {
    return this->points_;
}

// Операторы
Figure::operator double() const noexcept {
    if (this->vertices_number_ < 3) {
        return 0.0;
    }
    double result = 0.0;
    Point first = this->points_[0];
    Point second = this->points_[1];
    for (size_t i = 2; i < this->vertices_number_; ++i) {
        Point third = this->points_[i];
        result += 0.5 * (second - third).Length() * DistanceDotLine(first, second, third);
        second = third;
    }

    return result;
}

Figure& Figure::operator=(const Figure& other) {
    if (this != &other) {
        delete[] this->points_;
        this->vertices_number_ = other.vertices_number_;
        this->points_ = new Point[this->vertices_number_];
        std::copy(other.points_, other.points_ + other.vertices_number_, this->points_);
    }

    return *this;
}

bool Figure::operator==(const Figure& other) const {
    if (this->vertices_number_ != other.vertices_number_) {
        return false;
    }

    Point this_center = Point(this->GetCenter());
    Point other_center = Point(other.GetCenter());

    // Ищем хотя бы одну совпадающую точку
    size_t offset = 0.0;
    for (; offset < this->vertices_number_; ++offset) {
        if (fabs(((this->points_[offset] - this_center) - (other.points_[0] - other_center)).Length()) < 1e-6) {
            break;
        }
    }

    // Проверяем, совпадают ли все точки.
    // Проверяем в обе стороны (против и по часовой стрелке)
    bool flag1 = true;
    bool flag2 = true;
    for (size_t i = 0; i < other.vertices_number_; ++i) {
        size_t j1 = (i + offset) % this->vertices_number_;
        size_t j2 = (offset - i + this->vertices_number_) % this->vertices_number_;
        if (fabs(((other.points_[i] - other_center) - (this->points_[j1] - this_center)).Length()) > 1e-6) {
            flag1 = false;
        }
        if (fabs(((other.points_[i] - other_center) - (this->points_[j2] - this_center)).Length()) > 1e-6) {
            flag2 = false;
        }
    }

    return flag1 or flag2;
}

// Операторы ввода и вывода
std::ostream& operator<<(std::ostream& out, const Figure& f) {
    out << "Figure(";
    for (size_t i = 0; i < f.vertices_number_; ++i) {
        out << f.points_[i];
        if (i < f.vertices_number_ - 1) {
            out << ", ";
        }
    }
    out << ")";
    return out;
}

std::istream& operator>>(std::istream& in, Figure& f) {
    size_t vertices_number;
    in >> vertices_number;
    f = Figure(vertices_number);
    for (size_t i = 0; i < vertices_number; ++i) {
        in >> f.points_[i];
    }
    return in;
}
