#include "Kepler.h"
#include <math.h>

double kepler(double en, double Mk)
{
double Ek = en*sin(0)+Mk;
double Ekold = 0;
while (fabs(Ek- Ekold)>0.000000001 )
{ Ekold = Ek;
 Ek = en*sin(Ek)+Mk;
}

return Ek;
}
