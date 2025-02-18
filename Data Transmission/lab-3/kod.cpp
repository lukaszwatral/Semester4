#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include "matplotlibcpp.h"
#include <fftw3.h>

namespace plt = matplotlibcpp;

void FFT(fftw_complex* in, fftw_complex* out, int N) {
    fftw_plan plan = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(plan);
    fftw_destroy_plan(plan);
    fftw_cleanup();
}

double mt(double fm, double t) {
	return sin(2 * M_PI * fm * t);
}

double zat(double ka, double fn, double t, double fm) {
	return ((ka * mt(fm, t) + 1) * cos(2 * M_PI * fn * t));
}

double zpt(double kp, double fn, double t, double fm) {
	return (cos(2 * M_PI * fn * t + kp * mt(fm, t)));
}

double zft(double kf, double fn, double t, double fm) {
	return (cos(2 * M_PI * fn * t + (kf / fm) * mt(fm, t)));
}


void my_plot(std::vector<double> y, std::string title, std::string ylabel) {
    plt::plot(y);
    plt::ylabel(ylabel);
    plt::xlabel("time [s]");
    plt::title(title);
    plt::show();
}

std::vector<double> widmo(fftw_complex* Xk, int N, double fs, std::string str) {
    std::vector<double> Mk;
    std::vector<double> Mpk;
    std::vector<double> fk;
    std::vector<double> log_x;
    std::vector<double> log_y;
    for (int k = 0; k <= (N / 2 - 1); k++) {
        Mk.push_back(sqrt(pow(Xk[k][0], 2) + pow(Xk[k][1], 2)));
        Mpk.push_back(10 * log10(Mk[k]));
        fk.push_back(k * fs / N);
    }
    plt::semilogx(fk, Mpk, "b");
    plt::xlabel("Czestotliwosc [Hz]");
    plt::ylabel("Amplituda [dB]");
    plt::title(str);
    //plt::show();
    return Mpk;
}

void pasmo(int N, int fs, int fn, fftw_complex* out, std::vector<double> g, int roznica) {
    double Bx = g[fn * N / fs] - roznica;
    std::vector<int> tmp;
    for (int i = 0; i < (N / 2 - 1); i++) {
        if (g[i] >= Bx) {
            tmp.push_back(i);
        }
    }
    widmo(out, N, fs, "");
    int fmin, fmax;
    fmin = tmp.front() * fs / N; //konwersja indeksu na czestotliwosc
    fmax = tmp.back() * fs / N;
    std::cout << "fmin = " << fmin << ", fmax = " << fmax << ", BxdB = " << fmax - fmin << " Hz";
    plt::plot({ (double)fmin, (double)fmax }, { Bx, Bx }, "r");
    plt::show();
}

int main()
{
    double Tc = 5;
    double fs = 8000;
    int N = Tc * fs;
    double t;
    double f = 20;
    std::vector<double> tabx;
    std::vector<double> tabA;
    std::vector<double> tabP;
    std::vector<double> tabF;
    fftw_complex* in;
    fftw_complex* out;
    in = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * N);
    out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * N);
    //fn - czestotliwosc nosna
    for (int n = 0; n < N; n++) {
        t = n / fs;
        tabx.push_back(sin(t));
        tabA.push_back(zat(0.5, 1000, t, 1));
        tabP.push_back(zpt(0.5, 20, t, 1));
        tabF.push_back(zft(0.5, 20, t, 1));
    }
    //my_plot(tabA, "Sygnal zmodulowany amplitudowo, kA = 0.5", "zA(t)");
    //my_plot(tabP, "Sygnal zmodulowany katowo - modulacja fazy, kP = 4pi", "zP(t)");
   // my_plot(tabF, "Sygnal zmodulowany katowo - modulacja czestotliwosci, kF = 4pi", "zF(t)");
    for (int n = 0; n < N; n++) {
        t = n / fs;
        //in[n][0] = zat(0.5, 1000, t, 50);
        //in[n][0] = zat(8, 1000, t, 50);
        //in[n][0] = zat(27, 1000, t, 50);
        //in[n][0] = zpt(0.5, 1000, t, 50);
        //in[n][0] = zpt(1.75, 1000, t, 50);
        //in[n][0] = zpt(4*M_PI, 1000, t, 50);
        //in[n][0] = zft(0.5, 1000, t, 50);
        //in[n][0] = zft(1.75, 1000, t, 50);
        in[n][0] = zft(4*M_PI, 1000, t, 50);
        in[n][1] = 0;
    }
    FFT(in, out, N);
    std::vector<double> g = widmo(out, N, fs, "Widmo amplitudowe sygnalu zmodulowanego katowo - modulacja czestotliwosci, kF = 4pi");
    pasmo(N, fs, 1000, out, g, 6);
}