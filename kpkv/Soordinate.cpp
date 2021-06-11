#include "Soordinate.h"
#include <iostream>
#include <math.h>
#include <ostream>
#include "Kepler.h"

using namespace std;

void Ocoord(double t, double* coord, Efemeridi Ef)
{
	double tk = t - Ef.toe;
	double Mk = Ef.M0 + (sqrt(Ef.mu) / pow(sqrt(Ef.A), 3) + Ef.del_n) * tk;
	double Ek = kepler(Mk, Ef.e);
	double Vk = atan2(sqrt(1 - pow(Ef.e, 2)) * sin(Ek), cos(Ek) - Ef.e);
	double Uk = Ef.omega + Vk + Ef.c_uc * cos(2 * (Ef.omega + Vk)) + Ef.c_us * sin(2 * (Ef.omega + Vk));
	double rk = Ef.A * (1 - Ef.e * cos(Ek)) + Ef.c_rc * cos(2 * (Ef.omega + Vk)) + Ef.c_rs * sin(2 * (Ef.omega + Vk));
	double ik = Ef.i0 + Ef.i_dot * tk + Ef.c_ic * cos(2 * (Ef.omega + Vk)) + Ef.c_is * sin(2 * (Ef.omega + Vk));
	double lambk = Ef.omega0 + (Ef.omega_dot - Ef.we) * tk - Ef.we * Ef.toe;
	coord[0] = (cos(-lambk) * cos(-Uk) - sin(-lambk) * cos(-ik) * sin(-Uk)) * rk;
	coord[1] = (-sin(-lambk) * cos(-Uk) - cos(-lambk) * cos(-ik) * sin(-Uk)) * rk;
	coord[2] = (sin(-ik) * sin(-Uk)) * rk;
}
