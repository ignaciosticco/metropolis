#include "stdlib.h"
#include "time.h"
#include "stdio.h"
#include <math.h>

#include "metropolis.h"
#include "lattice.h"

void escribir(float vector1[],float vector2[],int niter);

int main(int argc, char **argv) {
  int n = 34;
  float prob = 0.5;
  float T = 2.0;
  float energia= 0.0;
  float magnetizacion= 0.0;
  int i;
  int n_termalizacion = 25*(n-2)*(n-2);
  int niter = n_termalizacion;
  int *lattice = malloc(n * n * sizeof(int));
  float *vector_energia= malloc(niter*sizeof(int));
  float *vector_magnetizacion= malloc(niter*sizeof(float));

  srand(time(NULL));
  fill_lattice(lattice, n, prob);
  energia=calcula_energia_total(lattice,n,T,0,1);
  magnetizacion=calcula_magnetizacion (lattice,n);

  // Loop de termalizacion
  for(i=0;i<n_termalizacion;i++){
    metropolis(lattice,n,T,0,1,&magnetizacion,&energia);
    vector_energia[i] = energia;
    vector_magnetizacion[i]= magnetizacion;
  }
  escribir(vector_energia,vector_magnetizacion,n_termalizacion);

  free(lattice);
  free(vector_energia);
  free(vector_magnetizacion);
  return 0;
}

void escribir(float vector1[],float vector2[],int niter){
  int i;
  FILE *fp;
  fp = fopen("termalizacion_T2_N32.txt","w");
  for(i=0;i<niter;i++){
    fprintf(fp, "%.6f \t %.6f \n",vector1[i],vector2[i]);
  }  
  fclose(fp);
}

