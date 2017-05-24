#include "metropolis.h"
#include "time.h"
#include "stdio.h"
#include <stdlib.h>
#include <math.h>

# define ERROR 9999


int metropolis(int *lattice, int n, float T, float B, float J, float *magnet, float *energ) {
  //int delta_energia = 0;
  int sitio = pick_site(lattice,n);
  //int spin_antes= lattice[sitio];
  //int spin_despues= 0;
  //printf("SITIO:: %i\n", sitio );
  float delta_energia = calcula_delta_energia(lattice,sitio,n,B,J);
  //printf("delta_energia: %f \n",delta_energia*((n-2)*(n-2)));
  double p_pi = 0.0;
  double dado = 0.0;
  
  if(delta_energia<0){
    flip(lattice,n,T,sitio);
    *energ=*energ+delta_energia;
    *magnet=*magnet+2*lattice[sitio]/(float)((n-2)*(n-2));
    //printf("Entro al if \n");
  } 
  else{

    p_pi=exp(-delta_energia*((n-2)*(n-2))/T);
    dado = (double)rand()/(double)RAND_MAX;
    //printf("Entro al else: p_pi: %f dado: %f \n",p_pi,dado);
    if (dado < p_pi){
      flip(lattice, n, T, sitio);
      *energ=*energ+delta_energia;
      *magnet=*magnet+2*lattice[sitio]/(float)((n-2)*(n-2)); 
      //printf("yes flips\n");
    }
    else{
      //printf("no flips\n");
    	delta_energia=0;
    }
  }
  //printf("\n");
  return delta_energia;
}

int pick_site(int *lattice, int n) {

  double random; 
	int    sitio;
  int i=0;
	random = (double)rand()/RAND_MAX;
	random =  random*n*n;
	sitio = (int)(random);

  //printf("sitio: %i \n", sitio);
  
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


float calcula_energia_total(int *lattice, int n, float T,float B, float J){
	int i, j, k, s1, s2;
	float energiaJ = 0.0;
	int vecinos[4];
	float energiaB=0.0;
	float energia_total=0.0;

	for(i=1;i<n-1;i++){
    	for(j=1;j<n-1;j++){
    		s1 = lattice[j+n*i];
    		vecinos[0] = lattice[j+n*(i-1)];
    		vecinos[1] = lattice[j+1+n*i];
    		vecinos[2] = lattice[j+n*(i+1)];
    		vecinos[3] = lattice[(j-1)+n*i];   
    		energiaB+=B*s1;

    		for (k=0;k<4;k++){
    			s2 = vecinos[k]; 
    			energiaJ += -J*s1*s2; 
    		} 
    	}
  	}
  energia_total=(energiaB+energiaJ/2)/((n-2)*(n-2));
  return energia_total;
}

// Sacado de la diapositiva de metropolis de Dorso pag 22
float calcula_delta_energia(int *lattice, int sitio,int n, float B, float J){
    float delta_energia;
    int vecino_up = lattice[sitio-n];
    int vecino_down = lattice[sitio+n];
    int vecino_derecha = lattice[sitio + 1];
    int vecino_izquierda = lattice[sitio -1];
    delta_energia = ERROR;
    if (vecino_up*vecino_down*vecino_izquierda*vecino_derecha){
      if(vecino_up==vecino_down && vecino_up==vecino_izquierda \
       && vecino_up==vecino_derecha && vecino_up==1){
       delta_energia = 8.0;
      }
      else if(vecino_up==vecino_down && vecino_up==vecino_izquierda \
       && vecino_up==vecino_derecha && vecino_up==-1){
       delta_energia = -8.0;  
      }
      else{
        delta_energia = 0.0;
      }
    }
    if (vecino_up*vecino_down*vecino_izquierda*vecino_derecha<0){
      if(vecino_up+vecino_down+vecino_izquierda+vecino_derecha>0){
        delta_energia = 4.0;
      }
      if(vecino_up+vecino_down+vecino_izquierda+vecino_derecha<0){
        delta_energia = -4.0;
      }
    }
  if(lattice[sitio]==-1) delta_energia=-delta_energia;

  delta_energia=(J*delta_energia+B*2*lattice[sitio])/((n-2)*(n-2));

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


float calcula_magnetizacion (int*lattice, int n){
  int i=0;
  int j=0;
  float magnet=0;

    for(i=1;i<n-1;i++){
      for(j=1;j<n-1;j++){
        magnet+=lattice[j+n*i]/(float)((n-2)*(n-2));
      }
    }

  return magnet;
}

