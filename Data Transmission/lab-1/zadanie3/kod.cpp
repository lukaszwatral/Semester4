#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>
#include <vector>
#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;


double funkcja_u(double t) { //funkcja numer 7
    if (t >= 0 && t < 1.8) {
        return (sin(12 * cos(M_PI * t) * M_PI * t) + t * t);
    }
    if (t >= 1.8 && t < 2.3) {
        return (3 * (t - 1.7) * sin(3 * M_PI * t) * cos(20 * t * t));
    }
    if (t >= 2.3 && t < 3) {
        return ((t * t * t) / 16 * sin(8 * M_PI * t));
    }
    if (t >= 3 && t < 3.5) {
        return (log2(t) / (2 + sin(4 * M_PI * t)));
    }
}

int main()
{
    double Tc = 3.5;
    double fs = 10000;
    int N = Tc * fs;
    double t;
    std::vector<double> tabu;

    for (int n = 0; n < N; n++) {
        t = n / fs;
        tabu.push_back(funkcja_u(t));
    }

    plt::plot(tabu);
    plt::title("Zadanie 3. - funkcja nr 7");
    plt::xlabel("t");
    plt::ylabel("u(t)");
    plt::show();

}
