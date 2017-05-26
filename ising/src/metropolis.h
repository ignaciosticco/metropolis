#ifndef METROPOLIS_H
#define METROPOLIS_H

int metropolis(int *lattice, int n, float T, float B, float J, float *magnet, float *energ);
int pick_site(int *lattice, int n);
int flip(int *lattice, int n, float T, int idx);
float calcula_energia_total(int *lattice, int n, float T,float B, float J);
float calcula_delta_energia(int *lattice, int sitio,int n, float B, float J);
float calcula_magnetizacion (int*lattice, int n);
void calcula_correlacion(float* vector_magnitud,int longitud_magnitud,float* vector_correlacion,int k_max, int iter_corr_max);
#endif
