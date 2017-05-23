#include "metropolis.h"
#include "time.h"
#include "stdio.h"
#include <stdlib.h>
#include <math.h>

# define ERROR 9999

int metropolis(int *lattice, int n, float T, int *energia, int *magnetizacion) {
  int sitio = pick_site(lattice,n);
  //printf("SITIO:: %i\n", sitio );
  int delta_energia = calcula_delta_energia(lattice,sitio,n);
  //printf(" delta energia: %i\n", calcula_delta_energia(lattice,sitio,n));
  double p_pi = 0.0;
  double dado = 0.0;
  if(delta_energia<0){
    flip(lattice,n,T,sitio);
    *magnetizacion = (-1)*lattice[sitio];
  } 
  else{

    p_pi=exp(-delta_energia/T);
    dado = (double)rand()/RAND_MAX;
    if (dado < p_pi){
      flip(lattice, n, T, sitio);
      *magnetizacion = (-1)*lattice[sitio]; 
    }
  }
  *energia+=*delta_energia;   // Actualiza el valor de la energia de la red. 
  //printf("energia adentro metropolis: %i\n", energia);
  return delta_energia;
}

int pick_site(int *lattice, int n) {

  double random; 
	int    sitio;
  int i=0;
	random = (double)rand()/RAND_MAX;
	random =  random*n*n;
	sitio = (int)(random);
  
  if (sitio < n-1 ){
    sitio = pick_site(lattice, n);
  }
  else if(sitio > n*(n-1)){
    sitio = pick_site(lattice, n); 
  }
  else if (sitio % n == 0 ){
    sitio = pick_site(lattice, n); 
  }
  else{
    while(i<n){
      if (sitio == ((n-1) + n*i)){
        sitio = pick_site(lattice, n);
      }
      i=i+1;
    }
  }

  return sitio;
}

int flip(int *lattice, int n, float T, int idx) {

  lattice[idx] = -lattice[idx];

	if(idx > n && idx < 2*n) {
		lattice[idx + n*(n-2)]=lattice[idx];
	}
	
	if(idx >n*(n-2) && idx < n*(n-1)) {
		lattice[idx - n*(n-2)]=lattice[idx];
	}

	if(idx % n == 1) {
		lattice[idx+(n-2)]=lattice[idx];
	}

	if(idx % n == (n-2)){
		lattice[idx-(n-2)]=lattice[idx];
	}
	
  return 0;
}


int calcula_energia_total(int *lattice, int n, float T){
	int i, j, k, s1, s2;
	int energia = 0;
	int vecinos[4];
	for(i=1;i<n-1;i++){
    	for(j=1;j<n-1;j++){
    		s1 = lattice[j+n*i];
    		vecinos[0] = lattice[j+n*(i-1)];
    		vecinos[1] = lattice[j+1+n*i];
    		vecinos[2] = lattice[j+n*(i+1)];
    		vecinos[3] = lattice[(j-1)+n*i];   
    		for (k=0;k<4;k++){
    			s2 = vecinos[k]; 
    			energia += -s1*s2; 
    		} 
    	}
  	}

  return energia/2;
}

// Sacado de la diapositiva de metropolis de Dorso pag 22
int calcula_delta_energia(int *lattice, int sitio,int n){
    int delta_energia;
    int vecino_up = lattice[sitio-n];
    int vecino_down = lattice[sitio+n];
    int vecino_derecha = lattice[sitio + 1];
    int vecino_izquierda = lattice[sitio -1];
    delta_energia = ERROR;
    if (vecino_up*vecino_down*vecino_izquierda*vecino_derecha){
      if(vecino_up==vecino_down && vecino_up==vecino_izquierda \
       && vecino_up==vecino_derecha && vecino_up==1){
       delta_energia = 8;
      }
      else if(vecino_up==vecino_down && vecino_up==vecino_izquierda \
       && vecino_up==vecino_derecha && vecino_up==-1){
       delta_energia = -8;  
      }
      else{
        delta_energia = 0;
      }
    }
    if (vecino_up*vecino_down*vecino_izquierda*vecino_derecha<0){
      if(vecino_up+vecino_down+vecino_izquierda+vecino_derecha>0){
        delta_energia = 4;
      }
      if(vecino_up+vecino_down+vecino_izquierda+vecino_derecha<0){
        delta_energia = -4;
      }
    }
  if(lattice[sitio]==-1) delta_energia=-delta_energia;
  return delta_energia;

}

int calcula_magnetizacion_total(int *lattice, int n){
  int i,j;
  int magnetizacion = 0;
    for(i=1;i<n-1;i++){
      for(j=1;j<n-1;j++){
        magnetizacion += lattice[j+n*i];
      }
    }
  return magnetizacion;
}


