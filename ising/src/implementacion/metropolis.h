#ifndef METROPOLIS_H
#define METROPOLIS_H
int metropolis(int *lattice, int n, float T, float magnet);
int pick_site(int *lattice, int n);
int flip(int *lattice, int n, float T, int idx);
int calcula_energia_total(int *lattice, int n, float T);
int calcula_delta_energia(int *lattice, int sitio,int n);
float magnetizacion (int*lattice, int n);
float delta_M (int spin_antes, int spin_despues, int sitio, float magnet, int *lattice, int n);
#endif
