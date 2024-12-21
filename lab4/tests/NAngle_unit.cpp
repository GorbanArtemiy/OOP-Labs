#include <gtest/gtest.h>
#include "NAngle.hpp"
#include <stdexcept>
#include <sstream>

// Тестирование конструктора по умолчанию для четырехугольника
TEST(NAngleTest, DefaultConstructorQuadrilateral) {
    Square<double> q;
    EXPECT_EQ(q.GetVerticesNumber(), 4);  // Количество вершин должно быть 4
}

// Тестирование конструктора с использованием списков инициализации для пятиугольника
TEST(NAngleTest, InitializerListConstructorPentagon) {
    NAngle<double, 5> p = { {0.0, 0.0}, {1.0, 0.0}, {1.5, 1.0}, {1.0, 2.0}, {0.0, 2.0} };

    EXPECT_EQ(p.GetVerticesNumber(), 5); // Должно быть 5 вершин
    EXPECT_EQ(p[0], Point(0.0, 0.0));
    EXPECT_EQ(p[1], Point(1.0, 0.0));
    EXPECT_EQ(p[2], Point(1.5, 1.0));
    EXPECT_EQ(p[3], Point(1.0, 2.0));
    EXPECT_EQ(p[4], Point(0.0, 2.0));
}

// Тестирование неправильного конструктора с инициализатором для треугольника
TEST(NAngleTest, WrongInitializerListConstructorTriangle) {
    EXPECT_THROW(Triangle<double> t({{0.0, 1.0}, {1.0, 0.0}}), std::runtime_error);
}

// Тестирование конструктора копирования для шестиугольника
TEST(NAngleTest, CopyConstructorHexagon) {
    NAngle<double, 6> h = { {0.0, 0.0}, {1.0, 0.0}, {1.5, 1.0}, {1.0, 2.0}, {0.0, 2.0}, {-0.5, 1.0} };

    NAngle<double, 6> h2(h); // Копируем
    EXPECT_EQ(h2.GetVerticesNumber(), 6); // Количество вершин должно совпадать
    for (size_t i = 0; i < 6; ++i) {
        EXPECT_EQ(h2[i], h[i]); // Проверяем координаты
    }
}

// Тестирование оператора присваивания для семиугольника
TEST(NAngleTest, CopyAssignmentOperatorHeptagon) {
    NAngle<double, 7> h1 = { {0.0, 0.0}, {1.0, 0.0}, {1.5, 1.0}, {1.0, 2.0}, {0.0, 2.0}, {-0.5, 1.0}, {-1.0, 0.0} };

    NAngle<double, 7> h2; // Создаем новый семиугольник
    h2 = h1; // Присваиваем
    EXPECT_EQ(h2.GetVerticesNumber(), 7); // Количество вершин должно совпадать
    for (size_t i = 0; i < 7; ++i) {
        EXPECT_EQ(h2[i], h1[i]); // Проверяем координаты
    }
}

// Тестирование оператора ввода для восьмиугольника
TEST(NAngleTest, InputOperatorOctagon) {
    std::istringstream input("0.0 0.0\n1.0 0.0\n2.0 1.0\n2.0 2.0\n1.0 3.0\n0.0 3.0\n-1.0 2.0\n-1.0 1.0\n");
    Nangle<double, 8> o;
    input >> o;

    EXPECT_EQ(o.GetVerticesNumber(), 8); // Должно быть 8 вершин
    EXPECT_EQ(o[0], Point(0.0, 0.0));
    EXPECT_EQ(o[1], Point(1.0, 0.0));
    EXPECT_EQ(o[2], Point(2.0, 1.0));
    EXPECT_EQ(o[3], Point(2.0, 2.0));
    EXPECT_EQ(o[4], Point(1.0, 3.0));
    EXPECT_EQ(o[5], Point(0.0, 3.0));
    EXPECT_EQ(o[6], Point(-1.0, 2.0));
    EXPECT_EQ(o[7], Point(-1.0, 1.0));
}

// Тестирование оператора вывода для девятиугольника
TEST(NAngleTest, OutputOperatorNonagon) {
    NAngle<double, 9> n = { {0.0, 0.0}, {1.0, 0.0}, {1.5, 1.0}, {1.0, 2.0}, 
                          {0.0, 2.0}, {-0.5, 1.0}, {-1.0, 0.0}, {-1.0, -1.0}, {-0.5, -2.0} };

    std::ostringstream output;
    output << n;
    EXPECT_EQ(output.str(), "9-angle(Point(0, 0), Point(1, 0), Point(1.5, 1), Point(1, 2), Point(0, 2), Point(-0.5, 1), Point(-1, 0), Point(-1, -1), Point(-0.5, -2))");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
