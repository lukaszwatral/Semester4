#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include "matplotlibcpp.h"
#include <algorithm>
#include <fftw3.h>
#include <Eigen/Dense>
#include <random>
#include <time.h>
#include <iomanip>

namespace plt = matplotlibcpp;
using namespace Eigen;

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
	//for (int i = 0; i < N; i++) {
	//	std::cout << bn[i] << " ";
	//}
	return bn;
}

class Symulacja {
public:
	std::vector<int> bits;
	double fs;
	double fn;
	double Tc;
	int N;
	int B;
	int W;
	double Tb;
	std::string model;

	Symulacja(std::vector<int> bits, double fs, double fn, double Tc, int N, int B, int W, double Tb, std::string model) {
		this->bits = bits;
		this->fs = fs;
		this->fn = fn;
		this->Tc = Tc;
		this->N = N;
		this->B = B;
		this->W = W;
		this->Tb = Tb;
		this->model = model;
	}

	// tutaj zmiana sposobu modulacji względem lab-4, ponieważ dla dużej liczby bitów poprzedni sposób zaczął generować błędy
	std::vector<double> ASK() {
		std::vector<double> wartosci;
		double A1 = 1.0;
		double A2 = 0.5;
		double A;
		int index = 0;
		int Tbp = (int)(fs * Tb);
		double t;
		int b;
		for (int i = 0; i < N; i++) {
			t = (double)i / fs;
			if (i % Tbp == 0) {
				b = bits[index];
				if (b == 0) {
					A = A1;
				}
				else {
					A = A2;
				}
				index++;
			}
			wartosci.push_back(A * sin(2 * M_PI * fn * t));
		}
		//plt::plot(wartosci);
		//plt::show();
		return wartosci;
	}

	std::vector<double> PSK() {
	std::vector<double> wartosci;
	double Fi1 = 0;
	double Fi2 = M_PI;
	double Fi;
	int index = 0;
	int Tbp = (int)(fs * Tb);
	double t;
	int b;
	for (int i = 0; i < N; i++) {
		t = (double)i / fs;
		if (i % Tbp == 0) {
			b = bits[index];
			if (b == 0) {
				Fi = Fi1;
			}
			else {
				Fi = Fi2;
			}
			index++;
		}
		wartosci.push_back(sin(2 * M_PI * fn * t + Fi));
	}
	//plt::plot(wartosci);
	//plt::show();
	return wartosci;
}

	std::vector<double> FSK() {
	std::vector<double> wartosci;
	double fn1 = (this->W + 1) / Tb;
	double fn2 = (this->W + 2) / Tb;
	double fn0;
	int index = 0;
	int Tbp = (int)(fs * Tb);
	double t;
	int b;
	for (int i = 0; i < N; i++) {
		t = (double)i / fs;
		if (i % Tbp == 0) {
			b = bits[index];
			if (b == 0) {
				fn0 = fn1;
			}
			else {
				fn0 = fn2;
			}
			index++;
		}
		wartosci.push_back(sin(2 * M_PI * fn0 * t));
	}
	//plt::plot(wartosci);
	//plt::show();
	return wartosci;
	}

	std::vector<int> d_ASK(std::vector<double> ask) {
		double A1 = 1;
		double A2 = 0.5;
		double t;
		std::vector<double> xt;
		std::vector<double> pt;
		std::vector<double> ct;
		std::vector<int> bn;
		int Tbp = (int)(Tb * fs);
		for (int i = 0; i < ask.size(); i++) {
			t = (double)i / fs;
			xt.push_back(ask[i] * sin(2 * M_PI * fn * t));
		}
		double sum = 0.0;
		for (int j = 0; j < B; j++)
		{
			sum = 0.0;
			for (int i = (j * Tbp); i < ((j + 1) * Tbp); i++) {
				sum += xt[i];
				pt.push_back(sum);
			}
		}

		double h = *std::max_element(pt.begin(), pt.end()) / 2 - 1;
		for (int i = 0; i < pt.size(); i++) {
			pt[i] < h ? ct.push_back(1) : ct.push_back(0);
		}
		bn = syg2bit(ct, B, Tbp);
		//plt::plot(xt);
		//plt::title("x(t)");
		//plt::show();
		//plt::plot(pt);
		//plt::title("p(t)");
		//plt::show();
		//plt::plot(ct);
		//plt::title("c(t)");
		//plt::show();
		return bn;
	}

	std::vector<int> d_PSK(std::vector<double> psk) {

	double t;
	std::vector<double> xt;
	std::vector<double> pt;
	std::vector<double> ct;
	std::vector<int> bn;
	int Tbp = (int)(Tb * fs);
	for (int i = 0; i < psk.size(); i++) {
		t = (double)i / fs;
		xt.push_back(psk[i] * sin(2 * M_PI * fn * t));
	}
	double sum = 0.0;
	for (int j = 0; j < B; j++)
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
	bn = syg2bit(ct, B, Tbp);
	//plt::plot(xt);
	//plt::title("x(t)");
	//plt::show();
	//plt::plot(pt);
	//plt::title("p(t)");
	//plt::show();
	//plt::plot(ct);
	//plt::title("c(t)");
	//plt::show();
	return bn;
}


	std::vector<int> d_FSK(std::vector<double> fsk) {
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
	for (int i = 0; i < fsk.size(); i++) {
		t = i / fs;
		x1.push_back(fsk[i] * sin(2 * M_PI * fn1 * t));
		x2.push_back(fsk[i] * sin(2 * M_PI * fn2 * t));
	}
	double sum1 = 0.0;
	double sum2 = 0.0;
	for (int j = 0; j < B; j++)
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
	bn = syg2bit(ct, B, Tbp);
	//plt::plot(x1);
	//plt::title("x1(t)");
	//plt::show();
	//plt::plot(x2);
	//plt::title("x2(t)");
	//plt::show();
	//plt::plot(p1);
	//plt::title("p1(t)");
	//plt::show();
	//plt::plot(p2);
	//plt::title("p2(t)");
	//plt::show();
	//plt::plot(pt);
	//plt::title("p(t)");
	//plt::show();
	//plt::plot(ct);
	//plt::title("c(t)");
	//plt::show();
	return bn;
}

	std::vector<double> szum_bialy(std::vector<double> sygnal, double alfa) {
	//https://en.cppreference.com/w/cpp/numeric/random/uniform_real_distribution - generowanie rozkładu jednostajnego
	std::vector<double> tmp;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> szum(-3.0, 3.0);
	for (int i = 0; i<sygnal.size(); i++) {
		tmp.push_back(sygnal[i] + alfa * szum(gen));
	}
	return tmp;
}

	std::vector<double> tlumienie(std::vector<double> sygnal, double beta) {
	std::vector<double> tmp;
	double t;
	for (int i = 0; i < sygnal.size(); i++) {
		t = (double)i / fs;
		tmp.push_back(sygnal[i] * exp(-beta * t));
	}
	return tmp;
}

	std::vector<double> modulacja() {
		if (model == "ASK") {
			return ASK();
		}
		if (model == "PSK") {
			return PSK();
		}
		if (model == "FSK") {
			return FSK();
		}
	}

	std::vector<int> demodulacja(std::vector<double> vec) {
		if (model == "ASK") {
			return d_ASK(vec);
		}
		if (model == "PSK") {
			return d_PSK(vec);
		}
		if (model == "FSK") {
			return d_FSK(vec);
		}
	}

};

std::vector<int> koder_74(std::vector<int> bity) {
	std::vector<int> wynik = { 0, 0, 0, 0, 0, 0, 0 };
	wynik[2] = bity[0];
	wynik[4] = bity[1];
	wynik[5] = bity[2];
	wynik[6] = bity[3];
	wynik[0] = ((wynik[2] + wynik[4]) % 2 + wynik[6]) % 2;
	wynik[1] = ((wynik[2] + wynik[5]) % 2 + wynik[6]) % 2;
	wynik[3] = ((wynik[4] + wynik[5]) % 2 + wynik[6]) % 2;

	//for (int i = 0; i < 7; i++) {
	//	std::cout << wynik[i] << " ";
	//}
	//std::cout << "-" << "\n" << "-";
	return wynik;
}

std::vector<int> dekoder_74(std::vector<int> bity) {
	std::vector<int> wynik;
	int x1, x2, x4;
	int x1_, x2_, x4_;
	int x1r, x2r, x4r;
	int s;
	x1 = bity[0];
	x2 = bity[1];
	x4 = bity[3];
	x1_ = ((bity[2] + bity[4]) % 2 + bity[6]) % 2;
	x2_ = ((bity[2] + bity[5]) % 2 + bity[6]) % 2;
	x4_ = ((bity[4] + bity[5]) % 2 + bity[6]) % 2;

	s = 1 * ((x1 + x1_) % 2) + 2 * ((x2 + x2_) % 2) + 4 * ((x4 + x4_) % 2);
	if (s != 0) {
		bity[s - 1] = !bity[s - 1];
	}
	wynik = { bity[2], bity[4], bity[5], bity[6] };
	return wynik;
}

std::vector<int> koder_1511(std::vector<int> bity) {
	std::vector<int> c;
	Eigen::MatrixXd b(1, 11);
	for (int i = 0; i < 11; i++) {
		b(0, i) = bity[i];
	}
	MatrixXd tmp(1, 15);
	MatrixXd P(11, 4);
	MatrixXd I = MatrixXd::Identity(11, 11);
	int c1[11] = { 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1 };
	int c2[11] = { 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1 };
	int c4[11] = { 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1 };
	int c8[11] = { 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1 };
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 11; j++) {
			if (i == 0) P(j, i) = c1[j];
			if (i == 1) P(j, i) = c2[j];
			if (i == 2) P(j, i) = c4[j];
			if (i == 3) P(j, i) = c8[j];
		}
	}
	MatrixXd G(P.rows(), P.cols() + I.cols());
	G << P, I;
	tmp = b * G;
	for (int i = 0; i < 15; i++) {
		c.push_back((int)tmp(0, i) % 2);
	}
	return c;
}

std::vector<int> dekoder_1511(std::vector<int> bity) {
	MatrixXd c(1, 15);
	for (int i = 0; i < 15; i++) {
		c(0, i) = bity[i];
	}

	MatrixXd I = MatrixXd::Identity(4, 4);
	MatrixXd P(11, 4);
	int c1[11] = { 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1 };
	int c2[11] = { 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1 };
	int c4[11] = { 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1 };
	int c8[11] = { 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1 };
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 11; j++) {
			if (i == 0) P(j, i) = c1[j];
			if (i == 1) P(j, i) = c2[j];
			if (i == 2) P(j, i) = c4[j];
			if (i == 3) P(j, i) = c8[j];
		}
	}
	MatrixXd H(4, 15);
	H << I, P.transpose();
	MatrixXd s(1, 4);
	s << c * H.transpose();
	std::vector<int> tmp;
	for (int i = 0; i < 4; i++) {
		tmp.push_back((int)s(0, i) % 2);
	}
	int S = 1 * tmp[0] + 2 * tmp[1] + 4 * tmp[2] + 8 * tmp[3];
	std::vector<int> wynik = { bity[0], bity[1], bity[4], bity[2], bity[5], bity[6], bity[7], bity[3], bity[8], bity[9], bity[10], bity[11], bity[12], bity[13], bity[14] };
	if (S != 0) {
		wynik[S - 1] = !wynik[S - 1];
	}
	return { wynik[2], wynik[4], wynik[5], wynik[6], wynik[8], wynik[9], wynik[10], wynik[11], wynik[12], wynik[13], wynik[14] };
}

double calc_ber(std::vector<int> in_bits, std::vector<int> b3) {
	int E = 0;
	int N = in_bits.size();
	for (int i = 0; i < N; i++) {
		//std::cout << in_bits[i] << " - " << b3[i] << "\n";
		if (in_bits[i] != b3[i]) {
			E++;
		}
	}
	double ber = (double)E / (double)N;
	return ber;
}

std::vector<int> koduj(std::vector<int> in_bits) {
	std::vector<int> b1;
	for (int i = 0; i < in_bits.size(); i += 4) {
		std::vector<int> tmp(in_bits.begin()+i, in_bits.begin() + 4 + i);
		std::vector<int> tmp2 = koder_74(tmp);
		for (int j = 0; j < tmp2.size(); j++) {
			b1.push_back(tmp2[j]);
		}
	}
	return b1;
}

std::vector<int> dekoduj(std::vector<int> b2) {
	std::vector<int> b3;
	for (int i = 0; i < b2.size(); i += 7) {
		std::vector<int> tmp(b2.begin() + i, b2.begin() + 7 + i);
		std::vector<int> tmp2 = dekoder_74(tmp);
		for (int j = 0; j < tmp2.size(); j++) {
			b3.push_back(tmp2[j]);
		}
	}
	return b3;
}

int main() {
	std::vector<int> in_bits = konwerter("kochamTD");
	std::vector<int> b1;
	std::vector<int> b2;
	std::vector<int> b3;
	std::vector<int> tmp;
	std::vector<int> tmp2;
	std::vector<double> s1;
	std::vector<double> s2;
	std::vector<double> s3;
	b1 = koduj(in_bits);

	int B = b1.size();
	double fs = 20000;
	double Tc = 1;
	int W = 2;
	double Tb = (double)(Tc / B);
	int N = floor(Tc * fs);
	double fn = (double)(W * (1 / Tb));	

	std::vector<double> bers;
	int kroki_bety = 60;
	int kroki_alfy = 30;
	Eigen::VectorXd bety = Eigen::VectorXd::LinSpaced(kroki_bety, 0.0, 10.0);
	Eigen::VectorXd alfy = Eigen::VectorXd::LinSpaced(kroki_alfy, 0.0, 1.0);
	std::string typ;

	/////////////////////////
	std::string model = "ASK";

	int wybor = 4;
	switch (wybor) {
	case 1: 
		typ = "szum";
		break;
	case 2:
		typ = "tlumienie";
		break;
	case 3:
		typ = "szum+tlumienie";
		break;
	case 4:
		typ = "tlumienie+szum";
		break;
	default:
		break;
	}
	////////////////////////


	Symulacja* sym = new Symulacja(b1, fs, fn, Tc, N, B, W, Tb, model);
	s1 = sym->modulacja();
	//symulacja dla tłumienia
	if (typ == "tlumienie") {
		for (int k = 0; k < bety.size(); k++) {
			s2.clear();
			b2.clear();
			b3.clear();
			s2 = sym->tlumienie(s1, bety(k));
			//plt::plot(s2);
			//plt::show();

			b2 = sym->demodulacja(s2);

			b3 = dekoduj(b2);
			double xxx = calc_ber(in_bits, b3);
			bers.push_back(xxx);
		}
		std::vector<double> xx;
		for (int i = 0; i < bety.size(); i++) {
			xx.push_back(bety(i));
		}
		plt::plot(xx, bers);
		plt::show();
	}

	if (typ == "szum") {
		for (int k = 0; k < alfy.size(); k++) {
			s1.clear();
			s2.clear();
			b2.clear();
			b3.clear();
			s1 = sym->modulacja();
			s2 = sym->szum_bialy(s1, alfy(k));
			//plt::plot(s2);
			//plt::show();

			b2 = sym->demodulacja(s2);

			b3 = dekoduj(b2);
			double xxx = calc_ber(in_bits, b3);
			std::cout << xxx << " ";
			bers.push_back(xxx);
		}
		std::vector<double> xx;
		for (int i = 0; i < alfy.size(); i++) {
			xx.push_back(alfy(i));
		}
		plt::plot(xx, bers);
		plt::show();
	}

	if (typ == "szum+tlumienie") {
		for (int k = 0; k < alfy.size(); k++) {
			for (int l = 0; l < bety.size(); l++) {
				s2.clear();
				s3.clear();
				b2.clear();
				b3.clear();
				s2 = sym->szum_bialy(s1, alfy(k));
				//plt::plot(s2);
				//plt::show();

				s3 = sym->tlumienie(s2, bety(l));

				b2 = sym->demodulacja(s3);

				b3 = dekoduj(b2);
				double xxx = calc_ber(in_bits, b3);
				bers.push_back(xxx);
			}
		}
		std::vector<double> xx;
		for (int i = 0; i < alfy.size(); i++) {
			xx.push_back(alfy(i));
		}

		std::vector<double> yy;
		for (int i = 0; i < bety.size(); i++) {
			yy.push_back(bety(i));
		}
		std::cout << "\nalfy\n";
		for (auto x : bers) {
			std::cout << x << " ";
		}
		std::cout << "\n";
	}

	if (typ == "tlumienie+szum") {
		for (int k = 0; k < bety.size(); k++) {
			for (int l = 0; l < alfy.size(); l++) {
				s2.clear();
				s3.clear();
				b2.clear();
				b3.clear();
				s2 = sym->tlumienie(s1, bety(k));
				//plt::plot(s2);
				//plt::show();

				s3 = sym->szum_bialy(s2, alfy(l));
				b2 = sym->demodulacja(s3);

				b3 = dekoduj(b2);
				double xxx = calc_ber(in_bits, b3);
				bers.push_back(xxx);
			}
		}
		std::cout << "\nalfy\n";
		for (auto x : bers) {
			std::cout << x << " ";
		}
		std::cout << "\n";
		plt::plot(bers);
		plt::show();
	}
	delete sym;
}