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

int main(){
	return 0;
}