#include "stdlib.h"
#include "time.h"
#include "stdio.h"
#include <math.h>

#include "metropolis.h"
#include "lattice.h"

int main(int argc, char **argv) {
  int n = 4;
  int *lattice = malloc(n * n * sizeof(int));
  float prob = 0.5;
  float T = 2.0;
  int niter = 4;
  int *vector_energia= malloc(niter*sizeof(int));
  srand(time(NULL));
  fill_lattice(lattice, n, prob);
  //print_lattice(lattice, n);
  int *energia = (int*) calcula_energia_total(lattice, n, T);
  int *magnetizacion = calcula_energia_total(lattice, n, T);
  for (int i = 0; i < niter; i++) {
    //print_lattice(lattice, n);
    //metropolis(lattice, n, T);
    vector_energia[i]=metropolis(lattice,n,T,*energia,*magnetizacion);
    //printf("Vector energia:%i\n", vector_energia[i]);
     // printf("Energia :%i\n", *energia);
  }
  //printf("Energia final:%i\n", *energia);
  //printf("Magnetizacion:%i\n", *magnetizacion);
  free(lattice);
  free(vector_energia);
  return 0;
}
