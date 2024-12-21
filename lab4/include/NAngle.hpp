#pragma once
#include "Figure.hpp"
#include <string>

template<Scalar T, size_t N>
class NAngle : public Figure<T> {
public:
    // Конструкторы
    NAngle() noexcept : Figure<T>(N) {}
    NAngle(const NAngle& other) noexcept : Figure<T>(other) {}
    NAngle(const std::initializer_list<std::pair<double, double>>& points) : NAngle<T, N>() {
        if (points.size() != N) {
            throw std::runtime_error("Trying initialize " + std::to_string(N) + "-angle with different count of points.");
        }
        size_t i = 0;
        for (auto point : points) {
            this->points_[i] = point;
            ++i;
        }
    }

    // Переопределённые методы
    NAngle& operator=(const NAngle& other) {
        if (this != &other) {
            for (size_t i = 0; i < other.vertices_number_; ++i) {
                this->points_[i] = other.points_[i];
            }
        }
        return *this;
    }
    
    // Операторы
    friend std::ostream& operator<<(std::ostream& out, const NAngle<T, N>& f) {
        out << N << "-angle(";
        for (size_t i = 0; i < f.vertices_number_; ++i) {
            out << f.points_[i];
            if (i < f.vertices_number_ - 1) {
                out << ", ";
            }
        }
        out << ")";
        return out;
    }
    friend std::istream& operator>>(std::istream& in, NAngle<T, N>& f) {
        for (size_t i = 0; i < f.vertices_number_; ++i) {
            in >> f.points_[i];
        }
        return in;
    }
};

template<Scalar T>
using Rectangle = NAngle<T, 4>;

template<Scalar T>
using Triangle = NAngle<T, 3>;

template<Scalar T>
using Square = NAngle<T, 4>;
