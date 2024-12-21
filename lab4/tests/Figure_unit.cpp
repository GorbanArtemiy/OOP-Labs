#include <gtest/gtest.h>
#include "Figure.hpp"
#include <memory>

// Тестирование конструктора по умолчанию
TEST(FigureTest, DefaultConstructor) {
    Figure<double> f;
    EXPECT_EQ(f.GetVerticesNumber(), 0);  // Количество вершин должно быть 0
}

// Тестирование конструктора с initializer_list
TEST(FigureTest, ConstructorWithInitializerList) {
    Figure<double> f{{1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0}};
    EXPECT_EQ(f.GetVerticesNumber(), 3);  // Количество вершин должно быть 3
    EXPECT_EQ(f[0], Point<double>(1.0, 2.0));
    EXPECT_EQ(f[1], Point<double>(3.0, 4.0));
    EXPECT_EQ(f[2], Point<double>(5.0, 6.0));
}

// Тестирование конструктора копирования
TEST(FigureTest, CopyConstructor) {
    Figure<double> f1{{1.0, 2.0}, {3.0, 4.0}};
    Figure<double> f2(f1);
    EXPECT_EQ(f2.GetVerticesNumber(), 2);  // Количество вершин должно быть 2
    EXPECT_EQ(f2[0], Point<double>(1.0, 2.0));
    EXPECT_EQ(f2[1], Point<double>(3.0, 4.0));
}

// Тестирование конструктора перемещения
TEST(FigureTest, MoveConstructor) {
    Figure<double> f1{{1.0, 2.0}, {3.0, 4.0}};
    Figure<double> f2(std::move(f1));
    EXPECT_EQ(f2.GetVerticesNumber(), 2);  // В f2 должно быть 2 вершины
    EXPECT_EQ(f1.GetVerticesNumber(), 0);  // В f1 не должно остаться вершин
    EXPECT_EQ(f2[0], Point<double>(1.0, 2.0));
}

// Тестирование метода GetCenter для простой фигуры (треугольник)
TEST(FigureTest, GetCenter) {
    Figure<double> f{{0.0, 0.0}, {4.0, 0.0}, {2.0, 3.0}};
    std::pair<double, double> center = f.GetCenter();
    EXPECT_NEAR(center.first, 2.0, 1e-5);  // Центр x должен быть около 2.0
    EXPECT_NEAR(center.second, 1.0, 1e-5); // Центр y должен быть около 1.0
}

// Тестирование метода GetVerticesNumber
TEST(FigureTest, GetVerticesNumber) {
    Figure<double> f{{1.0, 2.0}, {3.0, 4.0}};
    EXPECT_EQ(f.GetVerticesNumber(), 2);  // Должно вернуть 2
}

// Тестирование оператора приведения к double (вычисление площади)
TEST(FigureTest, CastToDoubleAreaCalculation) {
    Figure<double> f{{0.0, 0.0}, {4.0, 0.0}, {0.0, 3.0}};
    double area = static_cast<double>(f);
    EXPECT_NEAR(area, 6.0, 1e-5);  // Площадь треугольника должна быть 6.0
}

// Тестирование оператора присваивания (копирование)
TEST(FigureTest, CopyAssignmentOperator) {
    Figure<double> f1{{1.0, 2.0}, {3.0, 4.0}};
    Figure<double> f2 = f1;
    EXPECT_EQ(f2.GetVerticesNumber(), 2);  // Количество вершин должно совпадать
    EXPECT_EQ(f2[0], Point<double>(1.0, 2.0));
}

// Тестирование оператора сравнения (==)
TEST(FigureTest, EqualityOperator) {
    Figure<double> f1{{0.0, 0.0}, {1.0, 0.0}, {0.0, 1.0}};
    Figure<double> f2{{0.0, 1.0}, {0.0, 0.0}, {1.0, 0.0}};
    EXPECT_TRUE(f1 == f2);  // Фигуры должны быть равны
}

// Тестирование оператора ввода
TEST(FigureTest, InputOperator) {
    std::istringstream input("3\n0 0\n1 0\n0 1\n");
    Figure<double> f;
    input >> f;
    EXPECT_EQ(f.GetVerticesNumber(), 3);  // Должно быть 3 вершины
    EXPECT_EQ(f[0], Point<double>(0.0, 0.0));
    EXPECT_EQ(f[1], Point<double>(1.0, 0.0));
    EXPECT_EQ(f[2], Point<double>(0.0, 1.0));
}

// Тестирование оператора вывода
TEST(FigureTest, OutputOperator) {
    Figure<double> f1{{1.0, 2.0}, {3.0, 4.0}};
    std::ostringstream output1;
    output1 << f1;
    EXPECT_EQ(output1.str(), "Figure(Point(1, 2), Point(3, 4))");

    Figure<double> f2{{1.5, 2.1}, {3.3, 4.9}};
    std::ostringstream output2;
    output2 << f2;
    EXPECT_EQ(output2.str(), "Figure(Point(1.5, 2.1), Point(3.3, 4.9))");
}

// Тестирование фигуры с одной вершиной
TEST(FigureTest, SingleVertexFigure) {
    Figure<double> f{{0.0, 0.0}};
    EXPECT_EQ(f.GetVerticesNumber(), 1);
    EXPECT_EQ(static_cast<double>(f), 0.0);  // Площадь должна быть 0.0
    EXPECT_EQ(f.GetCenter(), std::make_pair(0.0, 0.0));  // Центр совпадает с единственной вершиной
}

// Тестирование фигуры без вершин
TEST(FigureTest, EmptyFigure) {
    Figure<double> f;
    EXPECT_EQ(f.GetVerticesNumber(), 0);  // Количество вершин должно быть 0
    EXPECT_EQ(static_cast<double>(f), 0.0);  // Площадь должна быть 0.0
}

// Тестирование фигуры с точками на одной линии
TEST(FigureTest, CollinearPointsFigure) {
    Figure<double> f{{0.0, 0.0}, {2.0, 0.0}, {4.0, 0.0}};
    EXPECT_EQ(static_cast<double>(f), 0.0);  // Площадь должна быть 0.0, так как точки на одной линии
}

// Тестирование правильного треугольника
TEST(FigureTest, RegularTriangle) {
    Figure<double> f{{0.0, 0.0}, {4.0, 0.0}, {2.0, 3.464}};
    EXPECT_NEAR(static_cast<double>(f), 6.928, 1e-3);  // Площадь правильного треугольника
}

// Тестирование квадрата
TEST(FigureTest, Square) {
    Figure<double> f{{0.0, 0.0}, {0.0, 2.0}, {2.0, 2.0}, {2.0, 0.0}};
    EXPECT_NEAR(static_cast<double>(f), 4.0, 1e-5);  // Площадь квадрата 4.0
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}