#include "stdlib.h"
#include "time.h"
#include "stdio.h"
#include <math.h>

#include "metropolis.h"
#include "lattice.h"

void  escribir(float vector1[],float vector2[],float vector3[],int niter,char *str);
float observable(float magnitud,float magnitud_cuadrado,float T, int cant_iter);

int main(int argc, char **argv) {

  int   n,n_posta; 
  float prob = 0.5;
  int   cant_T = 100;
  float T_min = 1.7;
  float T_max = 4.0;
  int   iter_descorr; // cantidad de iteraciones para descorrelacionar 
  int   i,j, itera_T;
  int   cant_iter = 10000;   // cantidad de iteraciones para promediar 
  int   n_termalizacion, itera_size; // cantidad de iteraciones para termalizar
  float vector_T[cant_T];
  float CV[cant_T];
  float susceptibilidad[cant_T];
  float delta_T = (T_max - T_min)/(cant_T-1);
  float T;
  float acumula_magnetizacion, acumula_energia,acumula_energia_cuadrado,acumula_magnetizacion_cuadrado;
  char  str[60];
  int   vector_sizered[3]={34,66,130}; 
  srand(time(NULL));

  for(itera_size=0;itera_size<3;itera_size++){

    float energia = 0.0;
    float magnetizacion = 0.0;
    // Inicializo la red de tamaño (n-2)
    n = vector_sizered[itera_size];
    n_posta = n-2;
    n_termalizacion = 11*(n-2)*(n-2);
    iter_descorr = 3*(n-2)*(n-2);
    int *lattice = malloc(n * n * sizeof(int));

    fill_lattice(lattice, n, prob);

    // Inicializo vectores
    for(itera_T = 0;itera_T<cant_T;itera_T++){
      vector_T[itera_T] = T_max - delta_T*itera_T;
      CV[itera_T] = 0.0;
      susceptibilidad[itera_T] = 0.0;
    }


    // Loop de temperatura
    for(itera_T = 0;itera_T<cant_T;itera_T++){ 
       acumula_energia = 0.0;
       acumula_magnetizacion = 0.0;
       acumula_energia_cuadrado = 0.0;
       acumula_magnetizacion_cuadrado = 0.0;

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
        acumula_energia += energia;
        acumula_energia_cuadrado+=energia*energia;
        acumula_magnetizacion += magnetizacion;
        acumula_magnetizacion_cuadrado+=magnetizacion*magnetizacion;
      }
      CV[itera_T]+= observable(acumula_energia,acumula_energia_cuadrado,T*T,cant_iter);
      susceptibilidad[itera_T]+=observable(acumula_magnetizacion,acumula_magnetizacion_cuadrado,T,cant_iter);
    }  
    sprintf(str,"T_cv_susc_N%i.txt",n_posta);
    escribir(vector_T,CV,susceptibilidad,cant_T,str);
    free(lattice);
  }
  
  return 0;
}

void escribir(float vector1[],float vector2[],float vector3[],int niter,char *str){
  int i;
  FILE *fp;
  fp = fopen(str,"w");
  
  for(i=0;i<niter;i++){

    fprintf(fp, "%.2f \t %.2f \t %.2f \n",vector1[i],vector2[i],vector3[i]);
  }  

  fclose(fp);
}

float observable(float magnitud,float magnitud_cuadrado,float T, int cant_iter){
  // Toma M o E y calcula susceptibilidad o calor especifico. 
  float observable;
  observable =  (magnitud_cuadrado/cant_iter) - (magnitud/cant_iter)*(magnitud/cant_iter);
  observable = observable/T;
  
  return observable;
}
