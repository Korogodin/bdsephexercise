#ifndef EPHEMERIDS_H
#define EPHEMERIDS_H

typedef struct
{
  double X;
  double Y;
  double Z;

} Coordinates;
Coordinates CoordGPS(double t,
                     double toe,
                     double M0,
                     double  e,
                     double n,
                     double  a,
                     double  dn,
                     double  w,
                     double Cuc,
                     double Cus,
                     double Crc,
                     double Crs,
                     double Cic,
                     double Cis,
                     double i0,
                     double IDOT,
                     double  Omega0,
                     double  OmegaDot,
                     double omegaE );

#endif

