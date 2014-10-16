/******************************************************************************
 * This is a test program for atmosphere. It computes atmosphere and writes   *
 * it to a file.                                                              *
 ******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <zlib.h>
#include <string.h>

#include "../../include/Atmosphere.H"


int n;
double dt;
double t0;
char *oFile;

void parseArgs(int argc, char *argv[]);

int main(int argc, char *argv[]){

  RANDOM *random=new RANDOM(1);

  parseArgs(argc,argv);

  Atmosphere *a=new Atmosphere(random,dt,t0,n);

  gzFile fp=gzopen(oFile,"w9");

  gzwrite(fp,&n,sizeof(int));
  gzwrite(fp,&dt,sizeof(double));
  gzwrite(fp,&t0,sizeof(double));
  
  double d;
  for(int i=0;i<n;i++){
    d=a->get(dt*i);
    gzwrite(fp,&d,sizeof(double));
  }

  gzclose(fp);
  
  return 0;
}



void parseArgs(int argc, char *argv[]){

  int i,error=0;

  for(i=1;i<argc;i++){
    if(strcmp(argv[i],"-n")==0){
      i++;
      n=atoi(argv[i]);
    }
    else if(strcmp(argv[i],"-dt")==0){
      i++;
      dt=atof(argv[i]);
    }
    else if(strcmp(argv[i],"-t")==0){
      i++;
      t0=atof(argv[i]);
    }
    else if(strcmp(argv[i],"-o")==0){
      i++;
      oFile=argv[i];
    }
    else if(argv[i][0]=='-'){
      error=1;
    }
    else{
      error=2;
    }

    if(error==1){
      fprintf(stderr,"Unknown option: %s\n",argv[i]);
      exit(1);
    }
    if(error==2){
      fprintf(stderr,"Unknown parameter: %s\n",argv[i]);
      exit(1);
    }
  }
}
