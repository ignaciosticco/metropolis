#include "stdlib.h"
#include "time.h"
#include "stdio.h"
#include <math.h>

#include "metropolis.h"
#include "lattice.h"

void escribir(float vector1[],float vector2[],int niter);
void escribir2(float vector[],int size);

int main(int argc, char **argv) {
  int n = 12;
  float prob = 0.5;
  float T = 5.0;
  int niter = (n-2)*(n-2)*11;
  float vector_energia= 0;
  float vector_magnetizacion= 0.0;
  int i,j;
  int k_max = 10*(n-2)*(n-2);
  int iter_corr_max = 1000;
  int n_termalizacion = 10*(n-2)*(n-2);
  int *lattice = malloc(n * n * sizeof(int));
  float *energia_final= malloc(niter*sizeof(int));
  float *magnetizacion_final= malloc(niter*sizeof(float));
  float *vector_correlacion = malloc(k_max*sizeof(float));

  srand(time(NULL));
  fill_lattice(lattice, n, prob);
  vector_energia=calcula_energia_total(lattice,n,T,0,1);
  vector_magnetizacion=calcula_magnetizacion (lattice,n);

  // Loop de termalizacion
  for(i=0;i<n_termalizacion;i++){
    metropolis(lattice,n,T,0,1,&vector_magnetizacion,&vector_energia);
  }

  // Inicializa vector de correlacion
  for(j=0;j<iter_corr_max;j++){
    vector_correlacion[j]=0;
  }

  // Loop de correlacion
  for(j=0;j<iter_corr_max;j++){
  
    for (int i = 0; i < niter; i++) {
      metropolis(lattice, n, T,0,1,&vector_magnetizacion,&vector_energia);
      energia_final[i]= vector_energia;
      magnetizacion_final[i]= vector_magnetizacion;
    }
    calcula_correlacion(energia_final,niter,vector_correlacion,k_max,iter_corr_max);
  }  
  escribir2(vector_correlacion,iter_corr_max);
  free(lattice);
  free(vector_correlacion);
  free(energia_final);
  free(magnetizacion_final);
  return 0;
}

void escribir(float vector1[],float vector2[],int niter){
  int i;
  FILE *fp;
  fp = fopen("energia_magnetizacion.txt","w");
  
  for(i=0;i<niter;i++){

    fprintf(fp, "%.6f \t %.6f \n",vector1[i],vector2[i]);
  }  

  fclose(fp);
}

void escribir2(float vector[],int size){
  int i;
  FILE *fp;
  fp = fopen("correlacion_.txt","w");
  
  for(i=0;i<size;i++){

    fprintf(fp, "%.6f \n",vector[i]);
  }  

  fclose(fp);
}


