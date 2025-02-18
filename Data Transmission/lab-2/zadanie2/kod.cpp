#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>
#include <iomanip>
#include <vector>
#include "matplotlibcpp.h"
#include <fftw3.h>
namespace plt = matplotlibcpp;

std::vector<std::vector<double>> DFT(std::vector<double> x) {
    std::vector<double> re;
    std::vector<double> im;
    std::vector<std::vector<double>> X;
    int N = x.size();
    for (int k = 0; k < N; k++) {
        re.push_back(0);
        im.push_back(0);
        for (int n = 0; n < N; n++) {
            re[k] += (x[n] * cos(-2 * M_PI * k * n / N));
            im[k] += (x[n] * sin(-2 * M_PI * k * n / N));
        }
    }
    X.push_back(re);
    X.push_back(im);
    return X;
}

void widmo(std::vector<std::vector<double>> Xk, int N, double fs, std::string str) {
    std::vector<double> Mk;
    std::vector<double> Mpk;
    std::vector<double> fk;
    std::vector<double> log_x;
    std::vector<double> log_y;
    for (int k = 0; k <= (N / 2 - 1); k++) {
        Mk.push_back(sqrt(pow(Xk[0][k], 2) + pow(Xk[1][k], 2)));
        Mpk.push_back(10 * log10(Mk[k]));
        fk.push_back(k * fs / N);
    }
    plt::plot(fk, Mpk);
    plt::xlabel("Czestotliwosc [Hz]");
    plt::ylabel("Amplituda [dB]");
    plt::title(str);
    plt::show();

}

int main()
{
    std::vector<double> x = { 6,46,22,33,8,2,30,24,44,27,22 };
    std::vector<std::vector<double>> Xk;
    int N = x.size();
    double fs = 10000;
    Xk = DFT(x);
    widmo(Xk, N, fs, "M'(k)");
}
