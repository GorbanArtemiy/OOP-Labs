#include <gtest/gtest.h>
#include "Rectangle.hpp"
#include <stdexcept>

// Тестирование конструктора по умолчанию
TEST(RectangleTest, DefaultConstructor) {
    Rectangle r;
    EXPECT_EQ(r.GetVerticesNumber(), 4);  // Количество вершин должно быть 4
}

// Тестирование конструктора с использованием списков инициализации
TEST(RectangleTest, InitializerListConstructor) {
    Rectangle r = { {0.0, 0.0}, {2.0, 0.0}, {2.0, 1.0}, {0.0, 1.0} };

    EXPECT_EQ(r.GetVerticesNumber(), 4); // Должно быть 4 вершины
    Point* vertices = r.GetVertices();
    EXPECT_EQ(vertices[0], Point(0.0, 0.0));
    EXPECT_EQ(vertices[1], Point(2.0, 0.0));
    EXPECT_EQ(vertices[2], Point(2.0, 1.0));
    EXPECT_EQ(vertices[3], Point(0.0, 1.0));
}

TEST(RectangleTest, WrongInitializerListConstructor) {
    EXPECT_THROW(Rectangle r({{0.0, 1.0}, {1.0, 0.0}}), std::runtime_error);
}

// Тестирование конструктора копирования
TEST(RectangleTest, CopyConstructor) {
    Rectangle r1 = { {0.0, 0.0}, {2.0, 0.0}, {2.0, 1.0}, {0.0, 1.0} };

    Rectangle r2(r1); // Копируем
    EXPECT_EQ(r2.GetVerticesNumber(), 4); // Количество вершин должно совпадать
    for (size_t i = 0; i < 4; ++i) {
        EXPECT_EQ(r2.GetVertices()[i], r1.GetVertices()[i]); // Проверяем координаты
    }
}

// Тестирование оператора присваивания
TEST(RectangleTest, CopyAssignmentOperator) {
    Rectangle r1 = { {0.0, 0.0}, {2.0, 0.0}, {2.0, 1.0}, {0.0, 1.0} };

    Rectangle r2; // Создаем новый прямоугольник
    r2 = r1; // Присваиваем
    EXPECT_EQ(r2.GetVerticesNumber(), 4); // Количество вершин должно совпадать
    for (size_t i = 0; i < 4; ++i) {
        EXPECT_EQ(r2.GetVertices()[i], r1.GetVertices()[i]); // Проверяем координаты
    }
}

// Тестирование оператора ввода
TEST(RectangleTest, InputOperator) {
    std::istringstream input("0.0 0.0\n2.0 0.0\n2.0 1.0\n0.0 1.0\n");
    Rectangle r;
    input >> r;

    EXPECT_EQ(r.GetVerticesNumber(), 4); // Должно быть 4 вершины
    Point* vertices = r.GetVertices();
    EXPECT_EQ(vertices[0], Point(0.0, 0.0));
    EXPECT_EQ(vertices[1], Point(2.0, 0.0));
    EXPECT_EQ(vertices[2], Point(2.0, 1.0));
    EXPECT_EQ(vertices[3], Point(0.0, 1.0));
}

// Тестирование оператора вывода
TEST(RectangleTest, OutputOperator) {
    Rectangle r = { {0.0, 0.0}, {2.0, 0.0}, {2.0, 1.0}, {0.0, 1.0} };

    std::ostringstream output;
    output << r;
    EXPECT_EQ(output.str(), "Rectangle(Point(0, 0), Point(2, 0), Point(2, 1), Point(0, 1))");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}