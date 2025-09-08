#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "utils.h"
#include "edo.h"
#include "gaussSeidel_EqDiff.h"

// Gera diagonais e termos independentes a partir da definição do EDO
Tridiag *genTridiag (EDo *edo)
{
  Tridiag *sl;
  real_t x, xnext;
  int n = edo->n;
  
  sl = (Tridiag *) malloc (sizeof(Tridiag));
  sl->n = edo->n;

  sl->D = (real_t *) calloc(n, sizeof(real_t));
  sl->Di = (real_t *) calloc(n, sizeof(real_t));
  sl->Ds = (real_t *) calloc(n, sizeof(real_t));
  sl->B = (real_t *) calloc(n, sizeof(real_t));

  real_t h = (edo->b - edo->a)/(n+1);

  for (int i=0; i < n; ++i) {
    x = edo->a + (i+1)*h;
    sl->B[i] = h*h * edo->r(x);
    sl->Di[i] = 1 - h * edo->p(x)/2.0;
    sl->D[i] = -2 + h*h * edo->q(x);
    sl->Ds[i] = 1 + h * edo->p(x)/2.0;
  }

  sl->B[0] -= edo->ya * (1 - h*edo->p(edo->a+h)/2.0);
  sl->B[n-1] -= edo->yb * (1 + h*edo->p(edo->b-h)/2.0);
  
  return sl;
}


rtime_t gaussSeidel_3Diag (Tridiag *sl, real_t *Y, unsigned int maxiter) {
    int n = sl->n;
    int it = 0;
    rtime_t tTotal = timestamp();

    // algoritmo  Gauss-Seidel   com  vetores   das  diagonais   e  termos
    // independentes do SL

    while (it < maxiter) {
        // 5(n-2)+6 ≈ 5n operações / iteração
        Y[ 0 ] = (sl->B[ 0 ] - sl->Ds[ 0 ] * Y[ 1 ]) / sl->D[ 0 ];
        for (int i=1; i < n-1; ++i)
            Y[ i ] = (sl->B[ i ] - sl->Di[ i-1 ] * Y[ i-1] - sl->Ds[ i ] * Y[ i+1 ]) / sl->D[ i ];
        Y[ n-1 ] = (sl->B[ n-1 ] - sl->Di[ n-2 ] * Y[ n-2 ] ) / sl->D[ n-1 ];
        
    }

    return timestamp() - tTotal;

}



  // real_t norma = 0.0;

  // for (int i=0; i < n; ++i)
  //   norma += X[i]*X[i];

  // return sqrt(norma);

real_t normaL2_3Diag (Tridiag *sl, real_t *Y, double h) {
    int n = sl->n;

    real_t normaL2 = 0.0;

    for (int i = 0; i < n; i++) {
        real_t Ay_i;

        if (i == 0)
            Ay_i = (sl->D[0] * Y[0]) + (sl->Ds[0] * Y[1]);
        else if (i == n - 1)
            Ay_i = (sl->Di[i-1] * Y[i-1]) + (sl->D[i] * Y[i]);
        else
            Ay_i = (sl->Di[i-1] * Y[i-1]) + (sl->D[i] * Y[i]) + (sl->Ds[i] * Y[i+1]);

        normaL2 += pow(sl->B[i] - Ay_i, 2);
    }

    return sqrt(h * normaL2);
}


rtime_t gaussSeidel_EDO (EDo *edoeq, real_t *Y, unsigned int maxiter) {
    int n = edoeq->n;
    real_t x, b, yi, d, di, ds, h;

    rtime_t tTotal = timestamp();

    
    h = (edoeq->b - edoeq->a) / (n+1);

    for (int k=0; k < maxiter; ++k) {

        // algoritmo Gauss-Seidel usando parâmetros EDO, sem usar vetores para
        // diagonais e termos independentes do SL

        for (int i=0; i < n; ++i) { // Para cada equação do SL
            x = edoeq->a + (i+1)*h; // valor xi da malha: 2 FLOP
            b = h*h * edoeq->r(x); // termo independente: 3 FLOP
            di = 1 - h * edoeq->p(x)/2.0; // diagonal inferior: 3 FLOP
            d = -2 + h*h * edoeq->q(x); // diagonal principal: 3 FLOP
            ds = 1 + h * edoeq->p(x)/2.0; // diagonal superior: 3 FLOP
            // 8 FLOP (maximo) ; 4 FLOP (mínimo)
            if (i == 0) b -= ds*Y[i+1] + edoeq->ya * (1 - h*edoeq->p(edoeq->a+h)/2.0);
            else if (i == n-1) b -= di*Y[i-1] + edoeq->yb * (1 + h*edoeq->p(edoeq->b-h)/2.0);
            else b -= ds*Y[i+1] + di*Y[i-1] ;
            Y[i] = b / d; 
        }
    }

  return timestamp() - tTotal;
}

real_t normaL2_EDO (EDo *edoeq, real_t *Y) {
    int n = edoeq->n;
    real_t normaL2 = 0.0;
    real_t h = (edoeq->b - edoeq->a) / (n + 1);
    real_t xi, bi, di, d, ds;

    for (int i = 0; i < n; ++i) {
        xi = edoeq->a + (i + 1) * h;
        bi = h * h * edoeq->r(xi);
        di = 1 - h * edoeq->p(xi)/2.0;
        d = -2 + h * h * edoeq->q(xi);
        ds = 1 + h * edoeq->p(xi)/2.0;

        if (i == 0)
            bi -= ds * Y[i + 1] + edoeq->ya * (1 - h*edoeq->p(edoeq->a+h) / 2.0);
        else if (i == n - 1)
            bi -= di * Y[i - 1] + edoeq->yb * (1 + h*edoeq->p(edoeq->b-h) / 2.0);
        else
            bi -= ds * Y[i + 1] + di * Y[i - 1] ;

        normaL2 = pow((bi / d ) -  h * h * edoeq->r(xi), 2);
    }

    return sqrt(h * normaL2);
}

// Exibe um vetor na saída padrão
void prnVetor (real_t *v, unsigned int n)
{
  int i;

  //  printf ("\n");
  printf ("   ");
  for(i=0; i < n; ++i)
      printf ("%20.12e", v[i]);
  printf ("\n");

}

void prnTriDiagonal(Tridiag *sl)
{
    prnVetor(sl->Di,sl->n);
    prnVetor(sl->D,sl->n);
    prnVetor(sl->Ds,sl->n);
    prnVetor(sl->B,sl->n);

}


// Exibe SL na saída padrão
void prnEDOsl (EDo *edoeq, int diagOnly)
{
  int n = edoeq->n, i, j;
  real_t x, b, d, di, ds;
  real_t h = (edoeq->b - edoeq->a)/(n+1);

  printf ("\tn = %d, \t H = %.8g\nSL:\n", n, h);
  if (diagOnly) {
    prnTriDiagonal(genTridiag(edoeq));
  }
  else {
    for (i=0; i < n; ++i) {
      x = edoeq->a + (i+1)*h;
      b = h*h * edoeq->r(x);      
      di = 1 - h * edoeq->p(x)/2.0;
      d = -2 + h*h * edoeq->q(x);
      ds = 1 + h * edoeq->p(x)/2.0;
      
      for (j=0; j < n; ++j) {
	if (i == j)
	  printf ("%20.12e",d);
	else if (j == i-1 && i)
	  printf ("%20.12e",di);
	else if (j == i+1 && i != n-1)
	  printf ("%20.12e",ds);
	else
	  printf("%20.12e", 0.0);
      }
      
      if (i == 0)
	b -= edoeq->ya * (1 - h*edoeq->p(edoeq->a+h)/2.0);
      else if (i == n-1)
	b -= edoeq->yb * (1 + h*edoeq->p(edoeq->b-h)/2.0);
      
      printf (" | %20.12e\n", b);
    }
  }
}


