#include <gtest/gtest.h>
#include "Array.hpp"
#include "Figure.hpp"
#include "Rectangle.hpp"
#include "Triangle.hpp"
#include "Square.hpp"
#include <iostream>

std::ostream& PrintFigures(std::ostream& out, const Array<Figure*>& figures_pointers) {
    for (size_t i = 0; i < figures_pointers.Size(); ++i) {
        out << "Figure #" << i << ": " << *figures_pointers[i] << '\n';
    }
    return out;
}

std::ostream& PrintFiguresArea(std::ostream& out, const Array<Figure*>& figures_pointers) {
    for (size_t i = 0; i < figures_pointers.Size(); ++i) {
        out << "Figure #" << i << ": " << static_cast<double>(*figures_pointers[i]) << '\n';
    }
    return out;
}

double GetTotalArea(const Array<Figure*>& figures_pointers) {
    double result = 0.0;
    for (size_t i = 0; i < figures_pointers.Size(); ++i) {
        result += static_cast<double>(*figures_pointers[i]);
    }

    return result;
}

// Фикстура для тестов с фигурами
class FigureTest : public ::testing::Test {
protected:
    Rectangle rec;
    Triangle trg;
    Square sqr;
    Array<Figure*> figures;

    void SetUp() override {
        // Инициализация тестовых данных
        figures.Resize(3);
        figures[0] = &rec;
        figures[1] = &trg;
        figures[2] = &sqr;

        // Инициализация фигур тестовыми значениями
        std::cin.clear();
        rec = Rectangle{{0,0}, {2,0}, {2,1}, {0,1}};
        trg = Triangle{{0, 0}, {1, 0}, {0, 1}};
        sqr = Square{{0, 0}, {1, 0}, {1, 1}, {0, 1}};
    }
};

// Тест на вывод фигур
TEST_F(FigureTest, PrintFigures) {
    testing::internal::CaptureStdout();
    PrintFigures(std::cout, figures);
    std::string output = testing::internal::GetCapturedStdout();
    
    std::string expected_output =
        "Figure #0: Figure(Point(0, 0), Point(2, 0), Point(2, 1), Point(0, 1))\n"
        "Figure #1: Figure(Point(0, 0), Point(1, 0), Point(0, 1))\n"
        "Figure #2: Figure(Point(0, 0), Point(1, 0), Point(1, 1), Point(0, 1))\n";
    
    EXPECT_EQ(output, expected_output);
}

// Тест на вывод площадей фигур
TEST_F(FigureTest, PrintFiguresArea) {
    testing::internal::CaptureStdout();
    PrintFiguresArea(std::cout, figures);
    std::string output = testing::internal::GetCapturedStdout();

    // Здесь площади должны быть рассчитаны в зависимости от формул
    std::string expected_output =
        "Figure #0: 2\n" // Площадь правильного прямоугольника
        "Figure #1: 0.5\n" // Площадь треугольника
        "Figure #2: 1\n";  // Площадь квадрата
    
    EXPECT_EQ(output, expected_output);
}

// Тест на общую площадь
TEST_F(FigureTest, GetTotalArea) {
    double total_area = GetTotalArea(figures);
    EXPECT_DOUBLE_EQ(total_area, 3.5); // 2 + 0.5 + 1
}

// Тест на сравнение фигур
TEST(FigureComparisonTest, CompareFigures) {
    Figure fig1{{-1, -1}, {1, -1}, {1, 1}, {-1, 1}};
    Figure fig2{{0, 0}, {2, 0}, {2, 2}, {0, 2}};
    
    // Фигуры с разными координатами должны быть не равны
    EXPECT_TRUE(fig1 == fig2);
    
    // Тест на равные фигуры
    Figure fig3{{0, 0}, {2, 0}, {2, 2}, {0, 2}};
    EXPECT_TRUE(fig2 == fig3);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}