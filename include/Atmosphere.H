/******************************************************************************
 * This implements a simple atmospheric path delay model                      *
 ******************************************************************************/

#ifndef _ATMOSPHERE_H_
#define _ATMOSPHERE_H_

#include <math.h>

#include <Random.H>

extern "C"{
#include <amjMemory.h>
}

#define ATMOSPHERE_MODE_NONE 0
#define ATMOSPHERE_MODE_ZERO 1

class Atmosphere{
public:
  Atmosphere(Random *random, double dt, double tau, int n);
  Atmosphere(Random *random, double dt, double tau, int n, int mode);
  ~Atmosphere();
  double get(double t);
private:
  int n; 
  double dt;
  double tau;
  double *d; // [n]
  
  void initialize(Random *random, double dt, double tau, int nn, int mode);
  void drealft(double *data, unsigned long n, int isign);
  void dfour1(double *data, unsigned long nn, int isign);
};



#endif
