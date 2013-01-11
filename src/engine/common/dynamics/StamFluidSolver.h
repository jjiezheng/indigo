#ifndef STAM_FLUID_SOLVER_H
#define STAM_FLUID_SOLVER_H

void add_source (int N, float * x, float * s, float dt);

void set_bnd (int N, int b, float * x );
void set_bnd_circ( int N, float * x, float * y );

void lin_solve (int N, int b, float * x, float * x0, float a, float c, int it);

void diffuse (int N, int b, float * x, float * x0, float diff, float dt, int it);
void advect (int N, int b, float * d, float * d0, float * u, float * v, float dt);
void project (int N, float * u, float * v, float * p, float * div, int it);

void dens_step (int N, float * x, float * x0, float * u, float * v, float diff, float dt, int it);
void vel_step (int N, float * u, float * v, float * u0, float * v0, float visc, float dt, int it);

void reduce(int N, float* x, float dt);

#endif