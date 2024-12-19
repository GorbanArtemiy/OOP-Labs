#include <gtest/gtest.h>
#include "Triangle.hpp"
#include <stdexcept>

// Тестирование конструктора по умолчанию
TEST(TriangleTest, DefaultConstructor) {
    Triangle t;
    EXPECT_EQ(t.GetVerticesNumber(), 3);  // Количество вершин должно быть 3
}

// Тестирование конструктора с использованием списков инициализации
TEST(TriangleTest, InitializerListConstructor) {
    Triangle t = { {0.0, 0.0}, {1.0, 0.0}, {0.5, 1.0} };

    EXPECT_EQ(t.GetVerticesNumber(), 3); // Должно быть 3 вершины
    Point* vertices = t.GetVertices();
    EXPECT_EQ(vertices[0], Point(0.0, 0.0));
    EXPECT_EQ(vertices[1], Point(1.0, 0.0));
    EXPECT_EQ(vertices[2], Point(0.5, 1.0));
}

TEST(TriangleTest, WrongInitializerListConstructor) {
    EXPECT_THROW(Triangle t({{0.0, 1.0}, {1.0, 0.0}}), std::runtime_error);
}

// Тестирование конструктора копирования
TEST(TriangleTest, CopyConstructor) {
    Triangle t1 = { {0.0, 0.0}, {1.0, 0.0}, {0.5, 1.0} };

    Triangle t2(t1); // Копируем
    EXPECT_EQ(t2.GetVerticesNumber(), 3); // Количество вершин должно совпадать
    for (size_t i = 0; i < 3; ++i) {
        EXPECT_EQ(t2.GetVertices()[i], t1.GetVertices()[i]); // Проверяем координаты
    }
}

// Тестирование оператора присваивания
TEST(TriangleTest, CopyAssignmentOperator) {
    Triangle t1 = { {0.0, 0.0}, {1.0, 0.0}, {0.5, 1.0} };

    Triangle t2; // Создаем новый треугольник
    t2 = t1; // Присваиваем
    EXPECT_EQ(t2.GetVerticesNumber(), 3); // Количество вершин должно совпадать
    for (size_t i = 0; i < 3; ++i) {
        EXPECT_EQ(t2.GetVertices()[i], t1.GetVertices()[i]); // Проверяем координаты
    }
}

// Тестирование оператора ввода
TEST(TriangleTest, InputOperator) {
    std::istringstream input("0.0 0.0\n1.0 0.0\n0.5 1.0\n");
    Triangle t;
    input >> t;

    EXPECT_EQ(t.GetVerticesNumber(), 3); // Должно быть 3 вершины
    Point* vertices = t.GetVertices();
    EXPECT_EQ(vertices[0], Point(0.0, 0.0));
    EXPECT_EQ(vertices[1], Point(1.0, 0.0));
    EXPECT_EQ(vertices[2], Point(0.5, 1.0));
}

// Тестирование оператора вывода
TEST(TriangleTest, OutputOperator) {
    Triangle t = { {0.0, 0.0}, {1.0, 0.0}, {0.5, 1.0} };

    std::ostringstream output;
    output << t;
    EXPECT_EQ(output.str(), "Triangle(Point(0, 0), Point(1, 0), Point(0.5, 1))");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
