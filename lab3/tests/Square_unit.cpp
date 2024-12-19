#include <gtest/gtest.h>
#include "Square.hpp"
#include <stdexcept>

// Тестирование конструктора по умолчанию
TEST(SquareTest, DefaultConstructor) {
    Square s;
    EXPECT_EQ(s.GetVerticesNumber(), 4);  // Количество вершин должно быть 4
}

// Тестирование конструктора с использованием списков инициализации
TEST(SquareTest, InitializerListConstructor) {
    Square s = { {0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0} };

    EXPECT_EQ(s.GetVerticesNumber(), 4); // Должно быть 4 вершины
    Point* vertices = s.GetVertices();
    EXPECT_EQ(vertices[0], Point(0.0, 0.0));
    EXPECT_EQ(vertices[1], Point(1.0, 0.0));
    EXPECT_EQ(vertices[2], Point(1.0, 1.0));
    EXPECT_EQ(vertices[3], Point(0.0, 1.0));
}

TEST(SquareTest, WrongInitializerListConstructor) {
    EXPECT_THROW(Square s({{0.0, 1.0}, {1.0, 0.0}}), std::runtime_error);
}

// Тестирование конструктора копирования
TEST(SquareTest, CopyConstructor) {
    Square s1 = { {0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0} };

    Square s2(s1); // Копируем
    EXPECT_EQ(s2.GetVerticesNumber(), 4); // Количество вершин должно совпадать
    for (size_t i = 0; i < 4; ++i) {
        EXPECT_EQ(s2.GetVertices()[i], s1.GetVertices()[i]); // Проверяем координаты
    }
}

// Тестирование оператора присваивания
TEST(SquareTest, CopyAssignmentOperator) {
    Square s1 = { {0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0} };

    Square s2; // Создаем новый квадрат
    s2 = s1; // Присваиваем
    EXPECT_EQ(s2.GetVerticesNumber(), 4); // Количество вершин должно совпадать
    for (size_t i = 0; i < 4; ++i) {
        EXPECT_EQ(s2.GetVertices()[i], s1.GetVertices()[i]); // Проверяем координаты
    }
}

// Тестирование оператора ввода
TEST(SquareTest, InputOperator) {
    std::istringstream input("0.0 0.0\n1.0 0.0\n1.0 1.0\n0.0 1.0\n");
    Square s;
    input >> s;

    EXPECT_EQ(s.GetVerticesNumber(), 4); // Должно быть 4 вершины
    Point* vertices = s.GetVertices();
    EXPECT_EQ(vertices[0], Point(0.0, 0.0));
    EXPECT_EQ(vertices[1], Point(1.0, 0.0));
    EXPECT_EQ(vertices[2], Point(1.0, 1.0));
    EXPECT_EQ(vertices[3], Point(0.0, 1.0));
}

// Тестирование оператора вывода
TEST(SquareTest, OutputOperator) {
    Square s = { {0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0} };

    std::ostringstream output;
    output << s;
    EXPECT_EQ(output.str(), "Square(Point(0, 0), Point(1, 0), Point(1, 1), Point(0, 1))");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
