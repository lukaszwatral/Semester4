#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>
#include <vector>
#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;


double funkcja_b(double t, int H) { //funkcja nr 4
    double suma = 0.0;
    for (int h = 1; h <= H; h++) {
        suma += (sin(6 * M_PI * t * h * h) / (pow((2 * h + 1), 2) + sin(12 * M_PI * t)));
    }
    return suma;
}

int main()
{
    double Tc = 1;
    double fs = 22050;
    int N = Tc * fs;
    double t;
    std::vector<double> tabb1;
    std::vector<double> tabb2;
    std::vector<double> tabb3;

    for (int n = 0; n < N; n++) {
        t = n / fs;
        tabb1.push_back(funkcja_b(t, 2));
        tabb2.push_back(funkcja_b(t, 6));
        tabb3.push_back(funkcja_b(t, 26));
    }

    plt::plot(tabb1);
    plt::title("Zadanie 4. - funkcja nr 4");
    plt::xlabel("t");
    plt::ylabel("b1(t)");
    plt::show();
    plt::plot(tabb2);
    plt::title("Zadanie 4. - funkcja nr 4");
    plt::xlabel("t");
    plt::ylabel("b2(t)");
    plt::show();
    plt::plot(tabb3);
    plt::title("Zadanie 4. - funkcja nr 4");
    plt::xlabel("t");
    plt::ylabel("b3(t)");
    plt::show();

}
