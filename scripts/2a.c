#include "stdlib.h"
#include "time.h"
#include "stdio.h"
#include <math.h>

#include "metropolis.h"
#include "lattice.h"

void  escribir(float vector1[],float vector2[],float vector3[],int niter);
float observable(float magnitud,float T, int cant_iter);

int main(int argc, char **argv) {
  int   n = 34;
  float prob = 0.5;
  int   cant_T = 10;
  float T_min = 0.5;
  float T_max = 6.0;
  int   iter_descorr = 10*(n-2)*(n-2); // cantidad de iteraciones para descorrelacionar 
  float energia = 0.0;
  float magnetizacion = 0.0;
  int   i,j, itera_T;
  int   cant_iter = 100;   // cantidad de iteraciones para promediar 
  int   n_termalizacion = 11*(n-2)*(n-2); // cantidad de iteraciones para termalizar
  int   *lattice = malloc(n * n * sizeof(int));
  float vector_T[cant_T];
  float CV[cant_T];
  float susceptibilidad[cant_T];
  float delta_T = (T_max - T_min)/(cant_T-1);
  float T;

  srand(time(NULL));

  fill_lattice(lattice, n, prob);

  // Inicializo vectores
  for(itera_T = 0;itera_T<cant_T;itera_T++){
    vector_T[itera_T] = T_max - delta_T*itera_T;
    CV[itera_T] = 0.0;
    susceptibilidad[itera_T] = 0.0;
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
      //  luego de "iter_descorr" pasos para descorrelacionar el sistema
      CV[itera_T]+= observable(magnetizacion,T*T,cant_iter);
      susceptibilidad[itera_T]+=observable(energia,T,cant_iter);
    }
  }  
  escribir(vector_T,CV,susceptibilidad,cant_T);
  free(lattice);
  return 0;
}

void escribir(float vector1[],float vector2[],float vector3[],int niter){
  int i;
  FILE *fp;
  fp = fopen("T_cv_suscept_N32.txt","w");
  
  for(i=0;i<niter;i++){

    fprintf(fp, "%.6f \t %.6f \t %.6f \n",vector1[i],vector2[i],vector3[i]);
  }  

  fclose(fp);
}

float observable(float magnitud,float T, int cant_iter){
  // Toma M o E y calcula susceptibilidad o calor especifico. 
  float observable;
  observable =  (magnitud*magnitud/cant_iter) - (magnitud/cant_iter)*(magnitud/cant_iter);
  observable = observable/T;
  
  return observable;
}
