#include <stdio.h>
#include <math.h>
#include <float.h>

#include "utils.h"
#include "ZeroFuncao.h"

enum Modo {
  RAPIDO,
  LENTO
};


int main ()
{

  real_t a, b;
  Polinomio pol;

  scanf("%d", &pol.grau);

  pol.p = calloc(pol.grau + 1, sizeof(long));

  for (int i=pol.grau; i >=0; --i){
    scanf("%lf", &pol.p[i]);
  }
  scanf("%lf %lf", &a, &b); // intervalo onde está uma das raizes.


  // Restante do programa a partir daqui
  real_t raiz = 0;
  int it = 0;
  real_t erro;
  real_t tempo;

  printf("RAPIDO\n");
  printf("\n");

  for(enum Modo veloci = RAPIDO; veloci <= LENTO; ++veloci){
    for(enum Criterios crit = CRITERIO_1; crit <= CRITERIO_3; ++crit){
      printf("bissec ");
      tempo = timestamp();
      erro = bisseccao(pol, a, b, crit, &it, &raiz, veloci);
      //tempo = timestamp() - tempo;
      printf("%.15e %.15e %d %.8e\n", raiz, erro, it, timestamp() - tempo);
    }
    for(enum Criterios crit = CRITERIO_1; crit <= CRITERIO_3; ++crit){
      printf("newton ");
      tempo = timestamp();
      erro = newtonRaphson(pol, (a+b)/2, crit, &it, &raiz, veloci);
      //tempo = timestamp() - tempo; //PODE SER O A
      printf("%.15e %.15e %d %.8e\n", raiz, erro, it, timestamp() - tempo);
    }
    if(veloci < LENTO){
      printf("LENTO\n");
      printf("\n");
    }

  }

  free(pol.p);
  return 0;
}

