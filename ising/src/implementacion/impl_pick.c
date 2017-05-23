#include "stdlib.h"
#include "time.h"
#include "stdio.h"
#include <math.h>

#include "metropolis.h"
#include "lattice.h"

void escribir(int vector1[],int niter);

//Implementacion de pick site para ver si tira todos los valores de sitio homogeneamente
int main(int argc, char **argv) {
  int n = 10;
  int *lattice = malloc(n * n * sizeof(int));
  float prob = 0.5;
  float T = 2.0;
  int niter = 10000;
  int *vector_sitio= malloc(niter*sizeof(int));
  srand(time(NULL));
  fill_lattice(lattice, n, prob);
  print_lattice(lattice, n);
  for (int i = 0; i < niter; i++) {
    vector_sitio[i]=pick_site(lattice,n);
    }
  //print_lattice(lattice, n);
  escribir(vector_sitio,niter);
  free(lattice);
  free(vector_sitio);
  return 0;
}

void escribir(int vector1[],int niter){
  int i;
  FILE *fp;
  fp = fopen("pick_site_equi.txt","w");
  
  for(i=0;i<niter;i++){

    fprintf(fp, "%i \n",vector1[i]);
  }  

  fclose(fp);
}