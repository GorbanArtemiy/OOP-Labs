// main.cpp
#include "Array.hpp"
#include "Figure.hpp"
#include "NAngle.hpp"
#include <iostream>
#include <memory>

template<Scalar T>
std::ostream& PrintFigures(std::ostream& out, const Array<std::unique_ptr<Figure<T>>>& figures) {
    for (size_t i = 0; i < figures.Size(); ++i) {
        out << "Figure #" << i << ": " << *figures[i] << '\n';
    }
    return out;
}

template<Scalar T>
std::ostream& PrintFiguresArea(std::ostream& out, const Array<std::unique_ptr<Figure<T>>>& figures) {
    for (size_t i = 0; i < figures.Size(); ++i) {
        out << "Figure #" << i << ": " << static_cast<double>(*figures[i]) << '\n';
    }
    return out;
}

template<Scalar T>
std::ostream& PrintFiguresCenter(std::ostream& out, const Array<std::unique_ptr<Figure<T>>>& figures) {
    for (size_t i = 0; i < figures.Size(); ++i) {
        std::pair<T, T> center = figures[i]->GetCenter();
        out << "Figure #" << i << ": (" << center.first << ", " << center.second << ")\n";
    }
    return out;
}

template<Scalar T>
double GetTotalArea(const Array<std::unique_ptr<Figure<T>>>& figures) {
    double result = 0.0;
    for (size_t i = 0; i < figures.Size(); ++i) {
        result += static_cast<double>(*figures[i]);
    }
    return result;
}

// Перегрузки для ваекторов, содержащих не умные указатели на объекты, а сами объекты
template<size_t N>
std::ostream& PrintFigures(std::ostream& out, const Array<NAngle<double, N>>& figures) {
    for (size_t i = 0; i < figures.Size(); ++i) {
        out << "NAngle #" << i << ": " << figures[i] << '\n';
    }
    return out;
}

template<size_t N>
std::ostream& PrintFiguresArea(std::ostream& out, const Array<NAngle<double, N>>& figures) {
    for (size_t i = 0; i < figures.Size(); ++i) {
        out << "NAngle #" << i << ": " << static_cast<double>(figures[i]) << '\n';
    }
    return out;
}

template<size_t N>
std::ostream& PrintFiguresCenter(std::ostream& out, const Array<NAngle<double, N>>& figures) {
    for (size_t i = 0; i < figures.Size(); ++i) {
        std::pair<double, double> center = figures[i].GetCenter();
        out << "NAngle #" << i << ": (" << center.first << ", " << center.second << ")\n";
    }
    return out;
}

template<size_t N>
double GetTotalArea(const Array<NAngle<double, N>>& figures) {
    double result = 0.0;
    for (size_t i = 0; i < figures.Size(); ++i) {
        result += static_cast<double>(figures[i]);
    }
    return result;
}

int main() {
    Array<std::unique_ptr<Figure<double>>> figures;
    figures.Resize(3);

    std::cout << "Фигуры вводятся путём перечисления координат их точек по порядку." << std::endl;
    std::cout << "Введите три фигуры:" << std::endl;

    std::cout << "1. Прямоугольник:" << std::endl;
    auto rec = std::make_unique<Rectangle<double>>();
    std::cin >> *rec;
    figures[0] = std::move(oct);

    std::cout << "2. Треугольник:" << std::endl;
    auto trg = std::make_unique<Triangle<double>>();
    std::cin >> *trg;
    figures[1] = std::move(trg);

    std::cout << "3. Квадрат:" << std::endl;
    auto sqr = std::make_unique<Square<double>>();
    std::cin >> *sqr;
    figures[2] = std::move(sqr);

    std::cout << figures.Size() << '\n';

    PrintFigures(std::cout, figures) << '\n';
    PrintFiguresArea(std::cout, figures) << '\n';
    PrintFiguresCenter(std::cout, figures) << '\n';
    std::cout << "Total area: " << GetTotalArea(figures) << '\n';

    std::cout << "Проверяем, что сравнение фигур работает:\n";
    Figure<double> fig1 = {{-1, -1}, {1, -1}, {1, 1}, {-1, 1}};
    Figure<double> fig2 = {{0, 0}, {2, 0}, {2, 2}, {0, 2}};
    std::cout << (fig1 == fig2) << '\n';

    fig1[0] = 1000.0;
    std::cout << (fig1 == fig2) << '\n';

    Array<Square<double>> squares;
    squares.Resize(3);
    squares[0] = Square<double>({{0, 0}, {0, 1}, {1, 1}, {1, 0}});
    squares[1] = Square<double>({{-3, -3}, {-2, -3}, {-2, -4}, {-3, -4}});
    squares[2] = Square<double>({{2, 4}, {2, 7}, {-1, 7}, {-1, 4}});

    PrintFigures(std::cout, squares) << '\n';
    PrintFiguresArea(std::cout, squares) << '\n';
    PrintFiguresCenter(std::cout, squares) << '\n';
    std::cout << "Total area: " << GetTotalArea(squares) << '\n';

    return 0;
}

// Пример ввода для программы:
/*
0 0
2 0
2 1
0 1
0 0
1 0
1 1
1 1
1 0
0 0
0 1
*/