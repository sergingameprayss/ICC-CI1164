#ifndef _GAUSS_SEIDEL_
#define _GAUSS_SEIDEL_

#define MAXIT 100

rtime_t gaussSeidel_3Diag (Tridiag *sl, real_t *Y, int *it, unsigned int maxiter);
real_t normaL2_3Diag (Tridiag *sl, real_t *Y);

void prnVetor (real_t *v, unsigned int n);

#endif