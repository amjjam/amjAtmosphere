/******************************************************************************
 * This implements a simple atmospheric path delay model                      *
 * The model has duration n*dt, and it repeats if a time beyond the end is    *
 * requested.
 ******************************************************************************/

#ifndef _AMJATMOSPHERE_H_
#define _AMJATMOSPHERE_H_

#include <math.h>

#include <amjRandom.H>

#include <vector>

#define AMJATMOSPHERE_MODE_NONE 0
#define AMJATMOSPHERE_MODE_ZERO 1

class amjAtmosphere{
public:
  amjAtmosphere(amjRandom *random, double dt, double tau, int n);
  amjAtmosphere(amjRandom *random, double dt, double tau, int n, int mode);
  ~amjAtmosphere();
  double get(double t);
private:
  int n; 
  double dt;
  double tau;
  std::vector<double> d; // [n]
  
  void initialize(amjRandom *random, double dt, double tau, int nn, int mode);
  void drealft(double *data, unsigned long n, int isign);
  void dfour1(double *data, unsigned long nn, int isign);
};



#endif
