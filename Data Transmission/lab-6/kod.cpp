#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include "matplotlibcpp.h"
#include <algorithm>
#include <fftw3.h>
#include <Eigen/Dense>

namespace plt = matplotlibcpp;
using namespace Eigen;

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

std::vector<int> koder_74(std::vector<int> bity){
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

std::vector<int> dekoder_74(std::vector<int> bity){
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
		bity[s-1] = !bity[s-1];
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
			if(i==0) P(j, i) = c1[j];
			if(i==1) P(j, i) = c2[j];
			if(i==2) P(j, i) = c4[j];
			if(i==3) P(j, i) = c8[j];
		}
	}
	MatrixXd G(P.rows(), P.cols() + I.cols());
	G << P, I;
	tmp = b * G;
	for (int i = 0; i < 15; i++) {
		c.push_back((int)tmp(0, i)%2);
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
		tmp.push_back((int)s(0, i)%2);
	}
	int S = 1 * tmp[0] + 2 * tmp[1] + 4 * tmp[2] + 8 * tmp[3];
	std::vector<int> wynik = { bity[0], bity[1], bity[4], bity[2], bity[5], bity[6], bity[7], bity[3], bity[8], bity[9], bity[10], bity[11], bity[12], bity[13], bity[14] };
	if (S != 0) {
		wynik[S - 1] = !wynik[S - 1];
	}
	return { wynik[2], wynik[4], wynik[5], wynik[6], wynik[8], wynik[9], wynik[10], wynik[11], wynik[12], wynik[13], wynik[14]};
}



int main() {
	std::vector<int> bity = { 1, 0, 0, 1 };
	std::vector<int> zakodowane;
	std::vector<int> odkodowane;
	zakodowane = koder_74(bity);
	zakodowane[3] = !zakodowane[3]; // zakłamanie bitu
	odkodowane = dekoder_74(zakodowane);
	std::cout << "------------Hamming(7, 4)------------\nPrzed kodowaniem:\n";
	for (int i = 0; i < 4; i++) {
		std::cout << bity[i] << " ";
	}
	std::cout << "\nPo kodowaniu: \n";
	for (int i = 0; i < 7; i++) {
		std::cout << zakodowane[i] << " ";
	}
	std::cout << "\n" << "Po dekodowaniu: \n";
	for (int i = 0; i < 4; i++) {
		std::cout << odkodowane[i] << " ";
	}
	bity.clear();
	bity = { 0, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1 };
	zakodowane.clear();
	zakodowane = koder_1511(bity);
	odkodowane.clear();
	odkodowane = dekoder_1511(zakodowane);
	std::cout << "\n------------Hamming(15, 11)------------\nPrzed kodowaniem:\n";
	for (int i = 0; i < 11; i++) {
		std::cout << bity[i] << " ";
	}
	std::cout << "\nPo kodowaniu: \n";
	for (int i = 0; i < 15; i++) {
		std::cout << zakodowane[i] << " ";
	}
	std::cout << "\n" << "Po dekodowaniu: \n";
	for (int i = 0; i < 11; i++) {
		std::cout << odkodowane[i] << " ";
	}
	return 0;
}