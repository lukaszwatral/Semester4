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


int main()
{
    double Tc = 3;
    double fs = 10000;
    int N = Tc * fs;
    double t;
	double f = 20;
    std::vector<double> tabx;

    for (int n = 0; n < N; n++) {
        t = n / fs;
        tabx.push_back(funkcja_x(t, f));
    }

    plt::plot(tabx);
    plt::title("Zadanie 1. - funkcja nr 8");
    plt::xlabel("t");
    plt::ylabel("x(t)");
    plt::show();


}
