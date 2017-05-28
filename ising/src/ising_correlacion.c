#include "stdlib.h"
#include "time.h"
#include "stdio.h"
#include <math.h>

#include "metropolis.h"
#include "lattice.h"

void escribir2(float vector[],int size);

int main(int argc, char **argv) {
  int   n = 8;
  float prob = 0.5;
  float T = 5.0;
  int   niter = 11*(n-2)*(n-2);
  float energia = 0.0;
  float magnetizacion = 0.0;
  int   i,j;
  // Dada una tira de E, k_max es la distancia max de analisis de correlacion. 
  int   k_max = 10*(n-2)*(n-2);  
  int   cant_iter_corr = 1000;
  int   n_termalizacion = 11*(n-2)*(n-2);
  int   *lattice = malloc(n * n * sizeof(int));
  float *vector_energia= malloc(niter*sizeof(int));
  float *vector_magnetizacion= malloc(niter*sizeof(float));
  float *vector_correlacion = malloc(k_max*sizeof(float));

  srand(time(NULL));
  fill_lattice(lattice, n, prob);
  energia = calcula_energia_total(lattice,n,T,0,1);
  magnetizacion = calcula_magnetizacion (lattice,n);

  // Loop de termalizacion
  for(i=0;i<n_termalizacion;i++){
    metropolis(lattice,n,T,0,1,&magnetizacion,&energia);
  }

  // Inicializa vector de correlacion
  for(j=0;j<k_max;j++){
    vector_correlacion[j]=0;
  }

  // Loop de correlacion
  for(j=0;j<cant_iter_corr;j++){
    for (int i = 0; i < niter; i++) {
      metropolis(lattice, n, T,0,1,&magnetizacion,&energia);
      vector_energia[i] = energia;
      vector_magnetizacion[i] = magnetizacion;
    }
    calcula_correlacion(vector_energia,niter,vector_correlacion,k_max,cant_iter_corr);
  }  
  escribir2(vector_correlacion,k_max);
  free(lattice);
  free(vector_correlacion);
  free(vector_energia);
  free(vector_magnetizacion);
  return 0;
}

void escribir2(float vector[],int size){
  int i;
  FILE *fp;
  fp = fopen("correlacion_N8_T5.txt","w");
  for(i=0;i<size;i++){
    fprintf(fp, "%.6f \n",vector[i]);
  }  
  fclose(fp);
}


