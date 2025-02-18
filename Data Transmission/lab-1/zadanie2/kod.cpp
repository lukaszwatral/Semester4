#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>
#include <vector>
#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;

double funkcja_x(double t, double f) { //funkcja nr 8
    double fi = 0;
    return ((1 - t) * sin(2 * M_PI * f * t + fi) * cos(4 * M_PI * t));
}

double funkcja_y(double t, double f) { //zestaw nr 10
    return (cos(2 * sqrt(t * (sin(M_PI * (t * t)) + 2 * M_PI) / 3)));
}

double funkcja_z(double t, double f) {
    return (funkcja_y(t, f) * (sin(0.2 * M_PI * t) * abs(funkcja_x(t, f)/5)));
}

double funkcja_v(double t, double f) {
    return (sqrt(abs(funkcja_x(t, f))) * cos(0.5 * funkcja_y(t, f)) + funkcja_z(t, f));
}

int main()
{
    double Tc = 3;
    double fs = 10000;
    double f = 20;
    int N = Tc * fs;
    double t;
    std::vector<double> taby;
    std::vector<double> tabz;
    std::vector<double> tabv;

    for (int n = 0; n < N; n++) {
        t = n / fs;
        taby.push_back(funkcja_y(t, f));
        tabz.push_back(funkcja_z(t, f));
        tabv.push_back(funkcja_v(t, f));
        
    }

    plt::plot(taby);
    plt::title("Zadanie 2. - zestaw nr 10");
    plt::xlabel("t");
    plt::ylabel("y(t)");
    plt::show();
    plt::plot(tabz);
    plt::title("Zadanie 2. - zestaw nr 10");
    plt::xlabel("t");
    plt::ylabel("z(t)");
    plt::show();
    plt::plot(tabv);
    plt::title("Zadanie 2. - zestaw nr 10");
    plt::xlabel("t");
    plt::ylabel("v(t)");
    plt::show();


}
