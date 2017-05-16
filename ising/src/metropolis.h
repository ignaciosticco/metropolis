#ifndef METROPOLIS_H
#define METROPOLIS_H
int metropolis(int *lattice, int n, float T);
int pick_site(int *lattice, int n);
int flip(int *lattice, int n, float T, int idx);
int calcula_energia_total(int *lattice, int n, float T);
int calcula_delta_energia(int *lattice, int sitio,int n);

#endif
