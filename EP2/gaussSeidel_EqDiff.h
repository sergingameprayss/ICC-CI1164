// SERGIO SIVONEI DE SANT'ANA FILHO - GRR 20242337
#ifndef _GAUSS_SEIDEL_
#define _GAUSS_SEIDEL_

#define MAXIT 100

//calcula o sistema tridiagonal usando gaussSeidel otimizado 
rtime_t gaussSeidel_3Diag (Tridiag *sl, real_t *Y, int *it, unsigned int maxiter);

//normna l2 do residuo
real_t normaL2_3Diag (Tridiag *sl, real_t *Y);

#endif