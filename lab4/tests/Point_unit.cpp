#include "gtest/gtest.h"
#include "Point.hpp"
#include <cmath>

// 1. Конструкторы
TEST(PointConstructorTests, SingleArgumentConstructor) {
    Point<double> p(3.0);
    EXPECT_DOUBLE_EQ(p[0], 3.0);
    EXPECT_DOUBLE_EQ(p[1], 3.0);
}

TEST(PointConstructorTests, TwoArgumentConstructor) {
    Point<double> p(2.0, 4.0);
    EXPECT_DOUBLE_EQ(p[0], 2.0);
    EXPECT_DOUBLE_EQ(p[1], 4.0);
}

TEST(PointConstructorTests, PairConstructor) {
    Point<double> p(std::make_pair(1.0, 2.0));
    EXPECT_DOUBLE_EQ(p[0], 1.0);
    EXPECT_DOUBLE_EQ(p[1], 2.0);
}

TEST(PointConstructorTests, CopyConstructor) {
    Point<double> p1(1.0, 2.0);
    Point<double> p2(p1);
    EXPECT_DOUBLE_EQ(p2[0], 1.0);
    EXPECT_DOUBLE_EQ(p2[1], 2.0);
}

// 2. Операторы присваивания
TEST(PointAssignmentTests, CopyAssignment) {
    Point<double> p1(1.0, 2.0);
    Point<double> p2;
    p2 = p1;
    EXPECT_DOUBLE_EQ(p2[0], 1.0);
    EXPECT_DOUBLE_EQ(p2[1], 2.0);
}

TEST(PointAssignmentTests, CopySelfAssignment) {
    Point<double> p1(1.0, 2.0);
    p1 = p1;
    EXPECT_DOUBLE_EQ(p1[0], 1.0);
    EXPECT_DOUBLE_EQ(p1[1], 2.0);
}

// 3. Арифметические операторы
TEST(PointArithmeticTests, AdditionOperator) {
    Point<double> p1(1.0, 2.0);
    Point<double> p2(3.0, 4.0);
    Point<double> p3 = p1 + p2;
    EXPECT_DOUBLE_EQ(p3[0], 4.0);
    EXPECT_DOUBLE_EQ(p3[1], 6.0);
}

TEST(PointArithmeticTests, SubtractionOperator) {
    Point<double> p1(5.0, 6.0);
    Point<double> p2(3.0, 4.0);
    Point<double> p3 = p1 - p2;
    EXPECT_DOUBLE_EQ(p3[0], 2.0);
    EXPECT_DOUBLE_EQ(p3[1], 2.0);
}

TEST(PointArithmeticTests, MultiplicationByScalar) {
    Point<double> p1(1.0, 2.0);
    Point<double> p2 = p1 * 3;
    EXPECT_DOUBLE_EQ(p2[0], 3.0);
    EXPECT_DOUBLE_EQ(p2[1], 6.0);
}

TEST(PointArithmeticTests, DivisionByScalar) {
    Point<double> p1(4.0, 6.0);
    Point<double> p2 = p1 / 2;
    EXPECT_DOUBLE_EQ(p2[0], 2.0);
    EXPECT_DOUBLE_EQ(p2[1], 3.0);
}

TEST(PointArithmeticTests, DivisionByZeroScalar) {
    Point<double> p1(4.0, 6.0);
    EXPECT_THROW(p1 / 0, std::runtime_error);
}

// 4. Операторы присваивания с арифметикой
TEST(PointCompoundAssignmentTests, PlusEqualsOperator) {
    Point<double> p1(1.0, 2.0);
    p1 += Point<double>(2.0, 3.0);
    EXPECT_DOUBLE_EQ(p1[0], 3.0);
    EXPECT_DOUBLE_EQ(p1[1], 5.0);
}

TEST(PointCompoundAssignmentTests, MinusEqualsOperator) {
    Point<double> p1(4.0, 6.0);
    p1 -= Point<double>(1.0, 2.0);
    EXPECT_DOUBLE_EQ(p1[0], 3.0);
    EXPECT_DOUBLE_EQ(p1[1], 4.0);
}

TEST(PointCompoundAssignmentTests, MultiplyEqualsOperator) {
    Point<double> p1(2.0, 3.0);
    p1 *= 2;
    EXPECT_DOUBLE_EQ(p1[0], 4.0);
    EXPECT_DOUBLE_EQ(p1[1], 6.0);
}

TEST(PointCompoundAssignmentTests, DivideEqualsOperator) {
    Point<double> p1(6.0, 8.0);
    p1 /= 2;
    EXPECT_DOUBLE_EQ(p1[0], 3.0);
    EXPECT_DOUBLE_EQ(p1[1], 4.0);
}

// 5. Операторы индексации
TEST(PointIndexOperatorTests, ValidIndexAccess) {
    Point<double> p(3.0, 4.0);
    EXPECT_DOUBLE_EQ(p[0], 3.0);
    EXPECT_DOUBLE_EQ(p[1], 4.0);
}

TEST(PointIndexOperatorTests, InvalidIndexAccess) {
    Point<double> p(3.0, 4.0);
    EXPECT_THROW(p[2], std::out_of_range);
}

// 6. Функции для работы с векторами
TEST(PointVectorFunctionsTests, DotProduct) {
    Point<double> p1(1.0, 0.0);
    Point<double> p2(0.0, 1.0);
    EXPECT_DOUBLE_EQ(Dot(p1, p2), 0.0);
}

TEST(PointVectorFunctionsTests, CrossProduct) {
    Point<double> p1(1.0, 0.0);
    Point<double> p2(0.0, 1.0);
    EXPECT_DOUBLE_EQ(Cross(p1, p2), 1.0);
}

TEST(PointVectorFunctionsTests, LengthCalculation) {
    Point<double> p(3.0, 4.0);
    EXPECT_DOUBLE_EQ(p.Length(), 5.0);
}

TEST(PointVectorFunctionsTests, AngleBetweenVectors) {
    Point<double> p1(1.0, 0.0);
    Point<double> p2(0.0, 1.0);
    EXPECT_DOUBLE_EQ(p1.AngleToPoint(p2), M_PI / 2);
}

// 7. Операторы приведения типов
TEST(PointTypeConversionTests, ToPairConversion) {
    Point<double> p(1.0, 2.0);
    std::pair<double, double> pair = static_cast<std::pair<double, double>>(p);
    EXPECT_DOUBLE_EQ(pair.first, 1.0);
    EXPECT_DOUBLE_EQ(pair.second, 2.0);
}

// 8. Операторы ввода и вывода
TEST(PointIOTests, OutputOperator) {
    Point<double> p(1.0, 2.0);
    std::stringstream ss;
    ss << p;
    EXPECT_EQ(ss.str(), "Point(1, 2)");
}

TEST(PointIOTests, InputOperator) {
    std::stringstream ss("1.0 2.0");
    Point<double> p;
    ss >> p;
    EXPECT_DOUBLE_EQ(p[0], 1.0);
    EXPECT_DOUBLE_EQ(p[1], 2.0);
}

// 9. Дополнительные функции
TEST(PointDistanceTests, DistanceToLine) {
    Point<double> p(1, 2);
    Point<double> line_start(0, 0);
    Point<double> line_end(3, 0);
    EXPECT_DOUBLE_EQ(DistanceDotLine(p, line_start, line_end), 2.0);
}

// 10. Граничные и особые случаи
TEST(PointEdgeCasesTests, ZeroVectorLength) {
    Point<double> p(0.0, 0.0);
    EXPECT_DOUBLE_EQ(p.Length(), 0.0);
}

TEST(PointEdgeCasesTests, SmallNumberPrecision) {
    Point<double> p(DBL_MIN, DBL_MIN);
    EXPECT_NEAR(p.Length(), std::sqrt(2) * DBL_MIN, 1e-12);
}

TEST(PointEdgeCasesTests, DivisionByZeroEdgeCase) {
    Point<double> p1(1.0, 2.0);
    EXPECT_THROW(p1 /= 0, std::runtime_error);
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}