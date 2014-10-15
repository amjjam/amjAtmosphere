/******************************************************************************
 * This implements a simple atmospheric path delay model                      *
 ******************************************************************************/

#include "../include/Atmosphere.H"

/*=============================================================================
  Atmosphere(RANDOM *random, float dt, float tau, int n) - constructor

  RANDOM *random - random number generator
  float dt - time resolution of the simulated atmosphere, in ms
  float tau - atmospheric coherence time, in ms
  int n - number of time points. Time in the model will then run from 
     0 to dt*(n-1)

  Note on the coherence time: I use the astronomical optical interferometry 
  definition of the coherence time: 

  <((d[t]-d[t+tau])/500 nm)^2>=1 radian^2
  I.e. the variance of the phase is one radian squared over one coherence time.

  Other than that the structure function is 
  ============================================================================*/
Atmosphere::Atmosphere(RANDOM *random, double dt, double tau, int nn){
  
  // Store resolution and the coherence time
  Atmosphere::dt=dt;
  Atmosphere::tau=tau;

  // Determine the length of d. It should be the smallest power
  // of 2 greater than or equal to n.
  double m=ceil(log(nn)/log(2));
  n=(int)round(exp(m*log(2)));
  d=amjMalloc1dDouble(n,(char *)"Atmosphere::Atmosphere:d");
  
  // Fill d with random normally distributed numbers
  for(int i=0;i<n;i++)
    d[i]=random->gaussian();

  // Forward Fourier transform d
  drealft(d-1,n,1);

  // Multiply the Fourier transform by the square root of the
  // Kolmogorov power spectrum. The Kolmogorov power spectrum is
  // f^{-4/3}
  double p=4./3.; // Index of the root power spectrum
  double f1=1/dt/(double)n; // Frequency resolution
  double f,tmp;

  d[0]=0; // Zero frequency special case set to zero
  for(int i=1;i<n/2;i++){
    f=f1*i;
    tmp=pow(f,p);
    d[2*i]/=tmp;
    d[2*i+1]/=tmp;
  }
  d[1]/=pow(f1*n/2,p); // Max frequency, n/2 special case

  // Reverse Fourier transform d
  drealft(d-1,n,-1);

  // The following is amplitude calibration

  // Multiply d by reverse FFT normalization factor as described in
  // Numerical Recipes (multiply by 2/n)
  for(int i=0;i<n;i++)
    d[i]*=2.0/(double)n;

  // Experimentatlly I found that the structure function scales as
  // dt, so if I divide the time-series by sqrt(dt) then dt
  // should be removed as a factor in the amplitude. 
  //tmp=pow(dt,4./3.);
  for(int i=0;i<n;i++)
    d[i]/=sqrt(dt);

  // Dividing by this factor will make the structure function equal to
  // (1/4*pi)^2 at a time delay of 1. 1/(4*pi) is 0.5/(2*pi), where
  // 0.5 is 0.5 microns is a factor which converts from delay in
  // microns to phase. This corresponds to making the phase structure
  // function equal to 1 radian^2 at at a delay of 1, when the delay
  // is in microns. This factor is experimentally determined.
  for(int i=0;i<n;i++)
    d[i]/=165.861;

  // Finally we must scale by a factor which creates a 1 radian^2
  // phase structure function at a coherence time tau. The structure
  // function scales as tau^(5/3), so we divide by the square root of
  // that, so divide by by tau^(5/6).
  tmp=pow(tau,5./6.);
  for(int i=0;i<n;i++)
    d[i]/=tmp;
}


/*=============================================================================
  double get(double t) - returns the delay at time t.
  
  For now it just returns the delay at the nearest grid point. Later I
  will do a simple linear interpolation.
  ============================================================================*/
double Atmosphere::get(double t){
  int i=round(t/dt);

  return d[i];
}


/******************************************************************************
 * Private functions. These are modified from Numerical Recipes.              *
 ******************************************************************************/

/*=============================================================================
  drealft(double *data, unsigned long n, int isign) - this is a double
  precision version of Numerical Recipes realft()
  
  double *data - [n] - the data. Remember this is using the (strange)
  Numerical Recipes 1..nn based numering scheme, so when using a
  normal C array pass it as drealf(data-1,....)
  unsigned long n - size of the array. It must be a power of 2.
  int isign - the direction of the Fourier transform. 1 for forward
  transformation, -1 for inverse Fourier transform.
  ============================================================================*/
void Atmosphere::drealft(double *data, unsigned long n, int isign){
  unsigned long i,i1,i2,i3,i4,np3;
  double c1=0.5,c2,h1r,h1i,h2r,h2i;
  double wr,wi,wpr,wpi,wtemp,theta;
  
  theta=3.141592653589793/(double) (n>>1);
  if (isign == 1) {
    c2 = -0.5;
    dfour1(data,n>>1,1);
  } else {
    c2=0.5;
    theta = -theta;
  }
  wtemp=sin(0.5*theta);
  wpr = -2.0*wtemp*wtemp;
  wpi=sin(theta);
  wr=1.0+wpr;
  wi=wpi;
  np3=n+3;
  for (i=2;i<=(n>>2);i++) {
    i4=1+(i3=np3-(i2=1+(i1=i+i-1)));
    h1r=c1*(data[i1]+data[i3]);
    h1i=c1*(data[i2]-data[i4]);
    h2r = -c2*(data[i2]+data[i4]);
    h2i=c2*(data[i1]-data[i3]);
    data[i1]=h1r+wr*h2r-wi*h2i;
    data[i2]=h1i+wr*h2i+wi*h2r;
    data[i3]=h1r-wr*h2r+wi*h2i;
    data[i4] = -h1i+wr*h2i+wi*h2r;
    wr=(wtemp=wr)*wpr-wi*wpi+wr;
    wi=wi*wpr+wtemp*wpi+wi;
  }
  if (isign == 1) {
    data[1] = (h1r=data[1])+data[2];
    data[2] = h1r-data[2];
  } else {
    data[1]=c1*((h1r=data[1])+data[2]);
    data[2]=c1*(h1r-data[2]);
    dfour1(data,n>>1,-1);
  }
}


/*=============================================================================
  dfour1((double *data, unsigned long nn, int isign) - double
  precision version of Numerical Recipes four1 function
  
  double *data - [2*nn] - the data. Four1 used the (strange) Numerical
  Recipes [1..2*nn] numbering scheme, so to use normal C arrays pass
  it to four1 as four1(data-1,...)
  unsigned long nn - number of complex elements in data
  int isigne - direction of Fourier transform. 1 for Forward
  transformation, -1 for reverse transformation.
  ============================================================================*/
#define SWAP(a,b) tempr=(a);(a)=(b);(b)=tempr
void Atmosphere::dfour1(double *data, unsigned long nn, int isign){
  unsigned long n,mmax,m,j,istep,i;
  double wtemp,wr,wpr,wpi,wi,theta;
  double tempr,tempi;
  
  n=nn << 1;
  j=1;
  for (i=1;i<n;i+=2) {
    if (j > i) {
      SWAP(data[j],data[i]);
      SWAP(data[j+1],data[i+1]);
    }
    m=n >> 1;
    while (m >= 2 && j > m) {
      j -= m;
      m >>= 1;
    }
    j += m;
  }
  mmax=2;
  while (n > mmax) {
    istep=mmax << 1;
    theta=isign*(6.28318530717959/mmax);
    wtemp=sin(0.5*theta);
    wpr = -2.0*wtemp*wtemp;
    wpi=sin(theta);
    wr=1.0;
    wi=0.0;
    for (m=1;m<mmax;m+=2) {
      for (i=m;i<=n;i+=istep) {
	j=i+mmax;
	tempr=wr*data[j]-wi*data[j+1];
	tempi=wr*data[j+1]+wi*data[j];
	data[j]=data[i]-tempr;
	data[j+1]=data[i+1]-tempi;
	data[i] += tempr;
	data[i+1] += tempi;
      }
      wr=(wtemp=wr)*wpr-wi*wpi+wr;
      wi=wi*wpr+wtemp*wpi+wi;
    }
    mmax=istep;
  }
}
#undef SWAP
