#include <iostream>
#include <fstream>
#include <string>
#include "Soordinate.h"
#include "Kepler.h"
#include <ctime>
#include <cmath>

using namespace std;

int main()
{
	Efemeridi Efemer;
	Efemer.mu = 3.986004418E+14;
	Efemer.we = 7.2921150e-5;
	Efemer.toe = 284400;
	Efemer.A = 4.215808398716217e+07;
	Efemer.e = 8.14774842001497746e-03;
	Efemer.M0 = -2.45617118216572505;
	Efemer.omega = -2.52291283308052350;
	Efemer.i0 = 8.91248838651520714e-01;
	Efemer.omega0 = 2.63970155955976082;
	Efemer.del_n = 1.98079681996976564e-12;
	Efemer.i_dot = -2.30009580822278564e-13;
	Efemer.omega_dot = -2.82868925483299065e-12;
	Efemer.c_uc = 2.35158950090408325e-07;
	Efemer.c_us = -2.74321064352989197e-06;
	Efemer.c_rc = 3.05328125000000000e+02;
	Efemer.c_rs = 1.16406250000000000e+01;
	Efemer.c_ic = -2.70549207925796509e-07;
	Efemer.c_is = -1.37835741043090820E-07;

	time_t start, end;
	double t = 22680;
	double delta_t = 1;
	double* coord = new double[3];
	double* coord_matlab = new double[3];
	double max_del = 0;
	ofstream out;
	out.open("cpp.txt");
	ifstream in("matlab.txt");
	time(&start);
	for (int i = 0; i < (43200 / delta_t); i++)
	{
		Ocoord(t, coord, Efemer);
		t += delta_t;
		string coord_str1 = to_string(coord[0]);
		string coord_str2 = to_string(coord[1]);
		string coord_str3 = to_string(coord[2]);
		out << coord_str1 << "  " << coord_str2 << "  " << coord_str3 << endl;
		in >> coord_matlab[0] >> coord_matlab[1] >> coord_matlab[2];
		for (int j = 0; j < 3; j++)
		{
			if (abs(coord[j] - coord_matlab[j]) > max_del)
			{
				max_del = abs(coord[j] - coord_matlab[j]);
			}
		}
	}
	max_del = max_del * 10000000;
	time(&end);
	in.close();
	delete[] coord;
	delete[] coord_matlab;
	coord = nullptr;
	coord_matlab = nullptr;
	double seconds = difftime(end, start);
	string seconds1 = to_string(seconds / 43200 / delta_t);
	setlocale(LC_ALL, "rus");
	cout << "\n\t\tОбщее время расчёта, с: " << seconds << endl;
	cout << "\n\t\tСреднее время расчёта, с: " << seconds1 << endl;
	string max_del1 = to_string(max_del);
	cout << "\n\t\tМаксимальная разность координат(значение домножено на 10^7): " << max_del1 << endl;
	out.close();
	in.close();
}
