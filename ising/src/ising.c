#include "stdlib.h"
#include "time.h"
#include "stdio.h"
#include <math.h>

#include "metropolis.h"
#include "lattice.h"

void escribir(float vector1[],float vector2[],int niter);

int main(int argc, char **argv) {
  int n = 34;
  int *lattice = malloc(n * n * sizeof(int));
  float prob = 0.5;
  float T = 5.0;
  int niter = (n-2)*(n-2)*100;
  //int *vector_energia= malloc(sizeof(int));
  //float *vector_magnetizacion= malloc(sizeof(float));
  float vector_energia= 0;
  float vector_magnetizacion= 0.0;
  float *energia_final= malloc(niter*sizeof(int));
  float *magnetizacion_final= malloc(niter*sizeof(float));
  
  srand(time(NULL));
  fill_lattice(lattice, n, prob);
  vector_energia=calcula_energia_total(lattice,n,T,0,1);
  vector_magnetizacion=calcula_magnetizacion (lattice,n);

  //printf("energia %f\n", vector_energia );
  for (int i = 0; i < niter; i++) {

    metropolis(lattice, n, T,0,1,&vector_magnetizacion,&vector_energia);
    energia_final[i]= vector_energia;
    magnetizacion_final[i]= vector_magnetizacion;

  }
  escribir(energia_final,magnetizacion_final,niter);
  //print_lattice(lattice, n);
  free(lattice);
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
