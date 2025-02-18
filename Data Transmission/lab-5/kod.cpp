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

std::vector<int> syg2bit(std::vector<double> ct, int N, int Tbp) {
	double cmp;
	double sum;
	std::vector<int> bn;
	for (int j = 0; j < N; j++)
	{
		sum = 0.0;
		for (int i = (j * Tbp); i < ((j + 1) * Tbp); i++) {
			sum += ct[i];
		}

		cmp = sum / Tbp;
		cmp < 0.5 ? bn.push_back(0) : bn.push_back(1);
	}
	for (int i = 0; i < N; i++) {
		std::cout << bn[i] << " ";
	}
	return bn;
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

void cmp_bits(std::vector<int> b1, std::vector<int> b2) {
	std::vector<double> tmp1;
	std::vector<double> tmp2;
	for (int i = 0; i < b1.size(); i++) {
		for (int j = 0; j < 100; j++) {
			tmp1.push_back(b1[i]);
			tmp2.push_back(b2[i]);
		}
	}
	plt::subplot(2, 1, 1);
	plt::plot(tmp1);
	plt::title("Bity wejsciowe");
	plt::subplot(2, 1, 2);
	plt::plot(tmp2);
	plt::title("Bity po demodulacji");
	plt::show();
}


std::vector<int> d_ASK(std::vector<double> ask, double fs, double Tb, double fn) {
	double A1 = 1;
	double A2 = 2;
	double t;
	std::vector<double> xt;
	std::vector<double> pt;
	std::vector<double> ct;
	std::vector<int> bn;
	int Tbp = (int)(Tb * fs);
	int N = fs / Tbp;
	for (int i = 0; i < ask.size(); i++) {
		t = i / fs;
		xt.push_back(ask[i] * sin(2 * M_PI * fn * t));
	}
	double sum = 0.0;
	for (int j = 0; j < N; j++)
	{
		sum = 0.0;
		for (int i = (j*Tbp); i < ((j+1)*Tbp); i++) {
			sum += xt[i];
			pt.push_back(sum);
		}
	}
	double cmp;
	double h = A1/A2*fs*Tb*0.99;
	for (int i = 0; i < pt.size(); i++) {
		pt[i] > h ? ct.push_back(1) : ct.push_back(0);
	}
	bn = syg2bit(ct, N, Tbp);
	plt::plot(xt);
	plt::title("x(t)");
	plt::show();
	plt::plot(pt);
	plt::title("p(t)");
	plt::show();
	plt::plot(ct);
	plt::title("c(t)");
	plt::show();
	return bn;
}

std::vector<int> d_PSK(std::vector<double> psk, double fs, double Tb, double fn) {

	double t;
	std::vector<double> xt;
	std::vector<double> pt;
	std::vector<double> ct;
	std::vector<int> bn;
	int Tbp = (int)(Tb * fs);
	int N = fs / Tbp;
	for (int i = 0; i < psk.size(); i++) {
		t = i / fs;
		xt.push_back(psk[i] * sin(2 * M_PI * fn * t));
	}
	double sum = 0.0;
	for (int j = 0; j < N; j++)
	{
		sum = 0.0;
		for (int i = (j * Tbp); i < ((j + 1) * Tbp); i++) {
			sum += xt[i];
			pt.push_back(sum);
		}
	}
	for (int i = 0; i < pt.size(); i++) {
		pt[i] < 0 ? ct.push_back(1) : ct.push_back(0);
	}
	bn = syg2bit(ct, N, Tbp);
	plt::plot(xt);
	plt::title("x(t)");
	plt::show();
	plt::plot(pt);
	plt::title("p(t)");
	plt::show();
	plt::plot(ct);
	plt::title("c(t)");
	plt::show();
	return bn;
}

std::vector<int> d_FSK(std::vector<double> psk, double fs, double Tb, int W) {
	double fn1 = (W + 1) / Tb;
	double fn2 = (W + 2) / Tb;
	double t;
	std::vector<double> x1;
	std::vector<double> x2;
	std::vector<double> pt;
	std::vector<double> p1;
	std::vector<double> p2;
	std::vector<double> ct;
	std::vector<int> bn;
	int Tbp = (int)(Tb * fs);
	int N = fs / Tbp;
	for (int i = 0; i < psk.size(); i++) {
		t = i / fs;
		x1.push_back(psk[i] * sin(2 * M_PI * fn1 * t));
		x2.push_back(psk[i] * sin(2 * M_PI * fn2 * t));
	}
	double sum1 = 0.0;
	double sum2 = 0.0;
	for (int j = 0; j < N; j++)
	{
		sum1 = 0.0;
		sum2 = 0.0;
		for (int i = (j * Tbp); i < ((j + 1) * Tbp); i++) {
			sum1 += x1[i];
			p1.push_back(sum1);
			sum2 += x2[i];
			p2.push_back(sum2);
		}
	}
	for (int i = 0; i < p1.size(); i++) {
		pt.push_back(p2[i] - p1[i]);
	}

	for (int i = 0; i < pt.size(); i++) {
		pt[i] > 0 ? ct.push_back(1) : ct.push_back(0);
	}
	bn = syg2bit(ct, N, Tbp);
	plt::plot(x1);
	plt::title("x1(t)");
	plt::show();
	plt::plot(x2);
	plt::title("x2(t)");
	plt::show();
	plt::plot(p1);
	plt::title("p1(t)");
	plt::show();
	plt::plot(p2);
	plt::title("p2(t)");
	plt::show();
	plt::plot(pt);
	plt::title("p(t)");
	plt::show();
	plt::plot(ct);
	plt::title("c(t)");
	plt::show();
	return bn;
}


int main() {
	std::vector<int> bity = { 1, 0, 1, 1, 1, 1, 1, 0, 1, 1 };
	double Tc = 1;
	double fs = 20000;
	int N = (int)(Tc * fs);
	int B = bity.size();
	int W = 2;
	double fn = 2 * B;
	double Tb = (double)(Tc / B);
	std::vector<double> ask;
	std::vector<double> psk;
	std::vector<double> fsk;
	std::vector<int> bity_a;
	std::vector<int> bity_p;
	std::vector<int> bity_f;
	ask = ASK(bity, fs, Tb, fn);
	psk = PSK(bity, fs, Tb, fn);
	fsk = FSK(bity, fs, Tb, W);
	my_plot(ask, "Tc=1, fs=20000, B=10, fn=20", "zA(t)");
	bity_a = d_ASK(ask, fs, Tb, fn);
	cmp_bits(bity, bity_a);
	my_plot(psk, "Tc=1, fs=20000, B=10, fn=20", "zP(t)");
	bity_p = d_PSK(psk, fs, Tb, fn);
	cmp_bits(bity, bity_p);
	my_plot(fsk, "Tc=1, fs=20000, B=10, W=2", "zF(t)");
	bity_f = d_FSK(fsk, fs, Tb, W);
	cmp_bits(bity, bity_f);
	return 0;
}