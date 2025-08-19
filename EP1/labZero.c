#include <stdio.h>
#include <math.h>
#include <float.h>

#include "utils.h"
#include "ZeroFuncao.h"

#define RAPIDO 0;
#define LENTO 1;

int main ()
{

  real_t a, b;
  Polinomio pol;

  scanf("%d", &pol.grau);

  for (int i=pol.grau; i >=0; --i)
    scanf("%lf", &pol.p[i]);

  scanf("%lf %lf", &a, &b); // intervalo onde está uma das raizes.


  // Restante do programa a partir daqui
  fesetround(FE_DOWNWARD);
  real_t raiz = 0;
  int it = 0;
  real_t erro;

  printf("RAPIDO\n");
  printf("\n");
  erro = bisseccao(pol, a, b, CRITERIO_1, &it, &raiz, 0);

  printf("bissec %.15e %.15e %d %.8e\n", raiz, erro, it, TEMPO);


  return 0;
}

