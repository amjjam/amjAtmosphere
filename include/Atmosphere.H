/******************************************************************************
 * This implements a simple atmospheric path delay model                      *
 ******************************************************************************/

#ifndef _ATMOSPHERE_H_
#define _ATMOSPHERE_H_

#include <random.H>
#include <math.h>

class Atmosphere{
public:
  Atmosphere(RANDOM *random, double dt, double tau, int n);
  ~Atmosphere();
  double get(double t);
private:
  int n; 
  double dt;
  double tau;
  double *d; [n]
  
  drealft(double *data, unsigned long n, int isign);
  dfour1(double *data, unsigned long nn, int isign);
};



#endif
