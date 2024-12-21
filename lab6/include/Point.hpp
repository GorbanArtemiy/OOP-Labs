#pragma once

#include <utility>
#include <iostream>

class Point {
 private:
  double x_ = 0.0;
  double y_ = 0.0;

 public:
  // Конструкторы
  Point() noexcept;
  Point(double x, double y) noexcept;
  explicit Point(double x) noexcept;
  explicit Point(const std::pair<double, double>& point) noexcept;

  // Конструктор копирования и перемещения
  Point(const Point& other) noexcept;
  Point(Point&& other) noexcept;

  // Оператор присваивания
  Point& operator=(const Point& other);
  Point& operator=(Point&& other) noexcept;

  // Управление координатами
  void Set(double x, double y) noexcept;
  std::pair<double, double> Get() const noexcept;
  double GetX() const noexcept;
  double GetY() const noexcept;

  // Арифметика
  double Length() const noexcept;
  Point operator+(const Point& other) const;
  Point operator-(const Point& other) const;
  Point operator*(double number) const;
  friend Point operator/(const Point& point, double number);
  Point& operator+=(const Point& other);
  Point& operator-=(const Point& other);
  Point& operator*=(double number);
  Point& operator/=(double number);

  // Сравнения
  bool operator==(const Point& other) const;
  bool operator!=(const Point& other) const;

  // Ввод-вывод
  friend std::ostream& operator<<(std::ostream& out, const Point& point);
  friend std::istream& operator>>(std::istream& in, Point& point);
};
