#include <stdio.h>
#include <time.h>

#include "eliminacaoGauss.h"
#include "gaussSeidel.h"
#include "sislin.h"
#include "utils.h"

int main () {

    SistLinear_t *sl = lerSisLin();
    real_t *X = malloc(sl->n * sizeof(real_t));
    real_t *R = malloc(sl->n * sizeof(real_t));
    real_t it = 0;

    prnSisLin(sl);

    triangulariza(sl);
    //prnSisLin(sl);
    retrosubst(sl, X);
    residuo(sl, X, R, sl->n);

    printf("EG:\n");
    printf("COLOCAR TEMPO DPS   ms\n");
    prnVetor(X, sl->n);
    prnVetor(R, sl->n);

    printf("GS [ <it> iterações ]:\n");
    printf("COLOCAR TEMPO DPS   ms\n");
    //aq devem vir os resultados de x's
    //aq os residuos
    

    liberaSisLin(sl);
    free(X);
    free(R);

    return 1;
}