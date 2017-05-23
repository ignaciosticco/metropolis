#include "lattice.h"
//#include "time.h"
#include "stdio.h"
#include <stdlib.h>
#include <math.h>

int fill_lattice(int *lattice, int n, float p) {
 
 int i,j;
 double e;  
 // Llenamos toda la red
  for(i=0;i<n;i=i+1){
    for(j=0;j<n;j=j+1){
      e = (double)rand()/RAND_MAX;
      if(e <= p){
        lattice[j+n*i]=1;
      }
      else{
        lattice[j+n*i]=-1;
      }
    }
  }
  // Hacemos las cpc
  	// Primera fila
  for(j=0;j<n;j++){
  	lattice[j+n*0]=lattice[j+n*(n-2)];
  }
  // Ultima fila
  for(j=0;j<n;j++){
  	lattice[j+n*(n-1)]=lattice[j+n*1];
  }
    // Primera columna
  for(i=0;i<n;i++){
  	lattice[0+n*i]=lattice[(n-2)+n*i];
  }
   // Ultima columna
  for(i=0;i<n;i++){
  	lattice[(n-1)+n*i]=lattice[1+n*i];
  }
  return 0;
}

int print_lattice(int *lattice, int n) {
	// Imprimo en pantalla la matriz///////
	int i,j;
	for(i=0;i<n;i=i+1){
		for(j=0;j<n;j=j+1){
			printf("%d \t",lattice[j+n*i]);
		}
		printf("\n");
	}
  return 0;
}
