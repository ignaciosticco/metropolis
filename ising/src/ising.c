#include "stdlib.h"
#include "time.h"
#include "stdio.h"
#include <math.h>

#include "metropolis.h"
#include "lattice.h"

void escribir(float vector1[],float vector2[],int niter);

int main(int argc, char **argv) {
  int n = 10;
  int *lattice = malloc(n * n * sizeof(int));
  float prob = 0.5;
  float T = 2.0;
  int niter = 100;
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
  //print_lattice(lattice, n);
  printf("%f\n", vector_energia );
  //printf("%f\n", *vect_magnetizacion);
  for (int i = 0; i < niter; i++) {
    //printf("VALOR i: %i\n",i );
    //printf("%i\n",calcula_delta_energia(lattice, 10, n) );
    //print_lattice(lattice, n);
    metropolis(lattice, n, T,0,1,&vector_magnetizacion,&vector_energia);
    energia_final[i]= vector_energia;
    magnetizacion_final[i]= vector_magnetizacion;
    //printf("Energia%f\n", energia_final[i] );
    //printf("Magnetizacion%f\n", magnetizacion_final[i]);
    //printf("Vector energia:%i\n", vector_energia[i]);
    //vect_magnetizacion[i]=magetiza_total;
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

    fprintf(fp, "%f \t %f \n",vector1[i],vector2[i]);
  }  

  fclose(fp);
}