#pragma once
#include "Point.hpp"
#include <initializer_list>
#include <utility>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <memory>

// Класс Figure
template <Scalar T>
class Figure {
    // Конструкторы и деструктор
protected:
    size_t vertices_number_;
    std::unique_ptr<Point<T>[]> points_;

    Figure(size_t vertices_number) noexcept
        : vertices_number_(vertices_number)
        , points_(std::make_unique<Point<T>[]>(vertices_number))
    {}

public:
    Figure() noexcept
        : vertices_number_(0)
        , points_(nullptr)
    {}

    Figure(const std::initializer_list<std::pair<T, T>>& points) noexcept
        : Figure<T>(points.size())
    {
        size_t i = 0;
        for (auto point : points) {
            this->points_[i] = point;
            ++i;
        }
    }

    Figure(const Figure<T>& other) noexcept
        : Figure<T>(other.vertices_number_)
    {
        for (size_t i = 0; i < other.vertices_number_; ++i) {
            this->points_[i] = other.points_[i];
        }
    }

    Figure(Figure<T>&& other) noexcept
        : vertices_number_(other.vertices_number_)
        , points_(std::move(other.points_))
    {
        other.vertices_number_ = 0;
        other.points_ = nullptr;
    }

    ~Figure() noexcept = default;

    // Геттеры
    std::pair<T, T> GetCenter() const noexcept {
        Point<T> center;
        for (size_t i = 0; i < vertices_number_; ++i) {
            center += points_[i];
        }
        center /= vertices_number_;

        return static_cast<std::pair<T, T>>(center);
    }

    size_t GetVerticesNumber() const noexcept {
        return vertices_number_;
    }

    // Доступ к точкам
    Point<T>& operator[](int index) {
        if (index < 0 or index >= this->vertices_number_) {
            throw std::out_of_range("Index out of range.");
        }

        return this->points_[index];
    }

    Point<T> operator[](int index) const {
        if (index < 0 or index >= this->vertices_number_) {
            throw std::out_of_range("Index out of range.");
        }

        return this->points_[index];
    }

    // Операторы
    explicit operator double() const noexcept {
        if (vertices_number_ < 3) {
            return 0.0;
        }
        double result = 0.0;
        Point<T> first = points_[0];
        Point<T> second = points_[1];
        for (size_t i = 2; i < vertices_number_; ++i) {
            Point<T> third = points_[i];
            result += 0.5 * (second - third).Length() * DistanceDotLine(first, second, third);
            second = third;
        }

        return result;
    }

    Figure<T>& operator=(const Figure<T>& other) {
        if (this != &other) {
            this->vertices_number_ = other.vertices_number_;
            points_ = std::make_unique<Point<T>[]>(other.vertices_number_);
            std::copy(other.points_.get(), other.points_.get() + other.vertices_number_, points_.get());
        }

        return *this;
    }

    bool operator==(const Figure<T>& other) const {
        if (vertices_number_ != other.vertices_number_) {
            return false;
        }

        Point<T> this_center = Point<T>(GetCenter());
        Point<T> other_center = Point<T>(other.GetCenter());

        size_t offset = 0.0;
        for (; offset < vertices_number_; ++offset) {
            if (fabs(((points_[offset] - this_center) - (other.points_[0] - other_center)).Length()) < 1e-6) {
                break;
            }
        }

        bool flag1 = true;
        bool flag2 = true;
        for (size_t i = 0; i < other.vertices_number_; ++i) {
            size_t j1 = (i + offset) % vertices_number_;
            size_t j2 = (offset - i + vertices_number_) % vertices_number_;
            if (fabs(((other.points_[i] - other_center) - (points_[j1] - this_center)).Length()) > 1e-6) {
                flag1 = false;
            }
            if (fabs(((other.points_[i] - other_center) - (points_[j2] - this_center)).Length()) > 1e-6) {
                flag2 = false;
            }
        }

        return flag1 or flag2;
    }

    // Операторы ввода и вывода
    friend std::ostream& operator<<(std::ostream& out, const Figure<T>& f) {
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

    friend std::istream& operator>>(std::istream& in, Figure<T>& f) {
        size_t vertices_number;
        in >> vertices_number;
        f = Figure<T>(vertices_number);
        for (size_t i = 0; i < vertices_number; ++i) {
            in >> f.points_[i];
        }
        return in;
    }
};
