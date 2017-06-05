#include "stdlib.h"
#include "time.h"
#include "stdio.h"
#include <math.h>

#include "metropolis.h"
#include "lattice.h"

void escribir(float vector1[],float vector2[],float vector3[],int niter,char *str);

int main(int argc, char **argv) {
  int   n = 34;
  float prob = 0.5;
  int   cant_T = 50;
  float T_min = 1.7;
  float T_max = 5.0;
  float B_min = 0.1;
  float B_max = 0.9;
  int   cant_B = 9;
  int   iter_descorr = 2*(n-2)*(n-2); // cantidad de iteraciones para descorrelacionar 
  float energia;
  float magnetizacion;
  int   i,j, itera_T, ietera_B;
  int   cant_iter = 10000;   // cantidad de iteraciones para promediar 
  int   n_termalizacion = 11*(n-2)*(n-2); // cantidad de iteraciones para termalizar
  int   *lattice = malloc(n * n * sizeof(int));
  float vector_T[cant_T];
  float M[cant_T];
  float E[cant_T];
  float delta_T = (T_max - T_min)/(cant_T-1);
  float delta_B = (B_max - B_min)/(cant_B-1);
  float T,B;
  char  str[60];

  srand(time(NULL));

  fill_lattice(lattice, n, prob);

  // Loop de campo externo (B)
  for(ietera_B = 0;ietera_B < cant_B;ietera_B++){
    B = B_min + delta_B*ietera_B; 
    energia = 0.0;
    magnetizacion = 0.0;
  
    // Inicializo vectores
    for(itera_T = 0;itera_T<cant_T;itera_T++){
      vector_T[itera_T] = T_max - delta_T*itera_T;
      E[itera_T] = 0.0;
      M[itera_T] = 0.0;
    }

    // Loop de temperatura
    for(itera_T = 0;itera_T<cant_T;itera_T++){ 

      T = vector_T[itera_T];
      energia = calcula_energia_total(lattice,n,T,B,0);
      magnetizacion = calcula_magnetizacion (lattice,n);
      
      // Loop de termalizacion
      for(i=0;i<n_termalizacion;i++){
        metropolis(lattice,n,T,B,0,&magnetizacion,&energia);
      }
      
      // Loop de promedio
      for(j=0;j<cant_iter;j++){
        // Loop de descorrelacion
        for (int i = 0; i < iter_descorr; i++) {
          metropolis(lattice, n, T,0,B,&magnetizacion,&energia);
        }
        // Sumo el valor de M y E luego de "iter_descorr" pasos para descorrelacionar el sistema
        M[itera_T]+=magnetizacion/(float)cant_iter;
        E[itera_T]+=energia/(float)cant_iter;
      }
    }  
    sprintf(str,"magnetizacion_vsT_N32_B%.2f.txt",B);
    escribir(vector_T,M,E,cant_T,str);
    
  }
  free(lattice);
  return 0;
}

void escribir(float vector1[],float vector2[],float vector3[],int niter,char *str){
  int i;
  FILE *fp;
  fp = fopen(str,"w");
  
  for(i=0;i<niter;i++){

    fprintf(fp, "%.3f \t %.3f \t %.3f \n",vector1[i],vector2[i],vector3[i]);
  }  

  fclose(fp);
}

