#include "stdlib.h"
#include "time.h"
#include "stdio.h"
#include <math.h>

#include "metropolis.h"
#include "lattice.h"

void escribir(float vector1[],int niter,char *str);

int main(int argc, char **argv) {
  int   n = 34;
  float prob = 0.5;
  int   cant_T = 5;
  float T_min = 2.3;
  float T_max = 2.7;
  int   iter_descorr = 10*(n-2)*(n-2); // cantidad de iteraciones para descorrelacionar 
  float energia = 0.0;
  float magnetizacion = 0.0;
  int   i,j, itera_T;
  int   cant_iter = 10000;   // cantidad de iteraciones para promediar 
  int   n_termalizacion = 11*(n-2)*(n-2); // cantidad de iteraciones para termalizar
  int   *lattice = malloc(n * n * sizeof(int));
  float vector_T[cant_T];
  float M[cant_iter];
  float delta_T = (T_max - T_min)/(cant_T-1);
  float T;
  char  str[50];

  srand(time(NULL));

  fill_lattice(lattice, n, prob); // Crea la red

  // Inicializo vectores
  for(itera_T = 0;itera_T<cant_T;itera_T++){
    vector_T[itera_T] = T_max - delta_T*itera_T;
    //E[itera_T] = 0.0;
    //M[itera_T] = 0.0;
  }


  // Loop de temperatura
  for(itera_T = 0;itera_T<cant_T;itera_T++){ 

    T = vector_T[itera_T];
    energia = calcula_energia_total(lattice,n,T,0,1);
    magnetizacion = calcula_magnetizacion (lattice,n);
    
    // Loop de termalizacion
    for(i=0;i<n_termalizacion;i++){
      metropolis(lattice,n,T,0,1,&magnetizacion,&energia);
    }
    
    // Loop de promedio
    for(j=0;j<cant_iter;j++){
      // Loop de descorrelacion
      for (int i = 0; i < iter_descorr; i++) {
        metropolis(lattice, n, T,0,1,&magnetizacion,&energia);
      }

      // Sumo el valor de M y E luego de "iter_descorr" pasos para descorrelacionar el sistema
      M[j] = magnetizacion;
    }
    sprintf(str,"magnetizacion_vsiteracion_T%f_N32.txt",T);
    escribir(M,cant_iter,str);
  }  
  
  free(lattice);
  return 0;
}

void escribir(float vector1[],int niter,char *str){
  int i;
  FILE *fp;
  fp = fopen(str,"w");
  
  for(i=0;i<niter;i++){

    fprintf(fp, "%.2f \n",vector1[i]);
  }  

  fclose(fp);
}

