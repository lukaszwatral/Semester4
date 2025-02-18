#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include "matplotlibcpp.h"
#include <algorithm>
#include <fftw3.h>

namespace plt = matplotlibcpp;


void FFT(fftw_complex* in, fftw_complex* out, int N) {
	fftw_plan plan = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
	fftw_execute(plan);
	fftw_destroy_plan(plan);
	fftw_cleanup();
}

std::vector<int> konwerter(std::string str) {
	std::vector<int> out;
	int tmp;
	std::string tmp2;
	for (int c : str) {
		for (int i = 0; i < 7; i++) {
			out.push_back((c & 0x40) >> 6);
			c = c << 1;
		}
	}
	return out;
}

std::vector<double> ASK(std::vector<int> bn, double fs, double Tb, double fn) {
	int A1 = 1;
	int A2 = 2;
	double t;
	int Tbp = (int)(Tb * fs);
	std::vector<double> wartosci;
	for (int i = 0; i < bn.size(); i++) {
		if (bn[i] == 0) {
			for (int j = 0; j < Tbp; j++) {
				t = j / fs;
				wartosci.push_back(A1 * sin(2 * M_PI * fn * t));
			}
		}
		else {
			for (int j = 0; j < Tbp; j++) {
				t = j / fs;
				wartosci.push_back(A2 * sin(2 * M_PI * fn * t));
			}
		}
	}
	return wartosci;
}

std::vector<double> PSK(std::vector<int> bn, double fs, double Tb, double fn) {
	double Fi1 = 0;
	double Fi2 = M_PI;
	double t;
	int Tbp = (int)(Tb * fs);
	std::vector<double> wartosci;
	for (int i = 0; i < bn.size(); i++) {
		if (bn[i] == 0) {
			for (int j = 0; j < Tbp; j++) {
				t = j / fs;
				wartosci.push_back(sin(2 * M_PI * fn * t + Fi1));
			}
		}
		else {
			for (int j = 0; j < Tbp; j++) {
				t = j / fs;
				wartosci.push_back(sin(2 * M_PI * fn * t + Fi2));
			}
		}
	}
	return wartosci;
}

std::vector<double> FSK(std::vector<int> bn, double fs, double Tb, int W) {
	double fn1 = (W + 1) / Tb;
	double fn2 = (W + 2) / Tb;
	double t;
	int Tbp = (int)(Tb * fs);
	std::vector<double> wartosci;
	for (int i = 0; i < bn.size(); i++) {
		if (bn[i] == 0) {
			for (int j = 0; j < Tbp; j++) {
				t = j / fs;
				wartosci.push_back(sin(2 * M_PI * fn1 * t));
			}
		}
		else {
			for (int j = 0; j < Tbp; j++) {
				t = j / fs;
				wartosci.push_back(sin(2 * M_PI * fn2 * t));
			}
		}
		
	}
	return wartosci;
}


void my_plot(std::vector<double> wartosci, std::string title, std::string y) {
	plt::plot(wartosci);
	/*for (int i = 0; i <= bn.size(); i++) {
		plt::plot({ (double)(i * Tbp), (double)(i * Tbp) }, { -3.0, 3.0 }, "k");
	}*/
	plt::title(title);
	plt::xlabel("t");
	plt::ylabel(y);
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

void pasmo(int N, double fs, fftw_complex* out, std::vector<double> g, int roznica) {
	double max=g[0];
	for (int i = 0; i < (N / 2 - 1); i++) {
		if (g[i] > max) {
			max = g[i];
		}
	}
    double Bx = max - roznica;
    std::vector<int> tmp;
    for (int i = 0; i < (N / 2 - 1); i++) {
        if (g[i] >= Bx) {
            tmp.push_back(i);
        }
    }
    widmo(out, N, fs, "");
    double fmin, fmax;
    fmin = tmp.front() * fs / N; //konwersja indeksu na czestotliwosc
    fmax = tmp.back() * fs / N;
    std::cout << "fmin = " << fmin << ", fmax = " << fmax << ", BxdB = " << fmax - fmin << " Hz";
    plt::plot({ (double)fmin, (double)fmax }, { Bx, Bx }, "r");
    plt::show();
}

int main() {
	std::vector<int> bity = { 1, 0, 1, 1, 1, 1, 1, 0, 1, 1 };
	double Tc = 1;
	double fs = 20000;
	int N = (int)(Tc * fs);
	int B = bity.size();
	double fn = 2 * B;
	double Tb = (double)(Tc / B);
	std::vector<double> ask;
	std::vector<double> psk;
	std::vector<double> fsk;
	ask = ASK(bity, fs, Tb, fn);
	psk = PSK(bity, fs, Tb, fn);
	fsk = FSK(bity, fs, Tb, 2);
	//my_plot(ask, "Tc=1, fs=20000, B=10, fn=20", "zA(t)");
	//my_plot(psk, "Tc=1, fs=20000, B=10, fn=20", "zP(t)");
	//my_plot(fsk, "Tc=1, fs=20000, B=10, W=2", "zF(t)");
	fftw_complex* out;
	fftw_complex* in;
	out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * N);
	in = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * N);
	std::vector<double> g;
	/*for (int i = 0; i < N; i++) {
		in[i][0] = ask[i];
		in[i][1] = 0;
	}
	FFT(in, out, N);
	g = widmo(out, N, fs, "ASK, Tc=1, fs=20000");
	pasmo(N, fs, out, g, 12);*/
	//for (int i = 0; i < N; i++) {
	//	in[i][0] = psk[i];
	//	in[i][1] = 0;
	//}
	//FFT(in, out, N);
	//g = widmo(out, N, fs, "PSK, Tc=1, fs=20000");
	//pasmo(N, fs, out, g, 12);
	//for (int i = 0; i < N; i++) {
	//	in[i][0] = fsk[i];
	//	in[i][1] = 0;
	//}
	//FFT(in, out, N);
	//g = widmo(out, N, fs, "FSK, Tc=1, fs=20000");
	//pasmo(N, fs, out, g, 12);
	fftw_free(out);
	fftw_free(in);
	return 0;
}