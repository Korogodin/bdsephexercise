#include "Kepler.h"
#include <math.h>

double kepler(double Mk, double e) {
	double Ek = Mk;
	double Ek1;
	do {
		Ek1 = Ek;
		Ek = Mk + e * sin(Ek);
	} while (fabs(Ek1 - Ek) > 0.0000001);
	return Ek;
}