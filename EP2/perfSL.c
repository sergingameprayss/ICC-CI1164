#include <stdio.h>
#include <time.h>

#include "eliminacaoGauss.h"
#include "gaussSeidel.h"
#include "sislin.h"
#include "utils.h"

int main () {

    SistLinear_t *sl = lerSisLin();
    real_t *Xeg = malloc(sl->n * sizeof(real_t));
    real_t *Reg = malloc(sl->n * sizeof(real_t));
    real_t *Xgs = calloc(sl->n, sizeof(real_t));
    real_t *Rgs = malloc(sl->n * sizeof(real_t));
    real_t norma;
    prnSisLin(sl);

    SistLinear_t *sl2 = dupSisLin(sl);

    triangulariza(sl);
    retrosubst(sl, Xeg);
    residuo(sl, Xeg, Reg, sl->n);

    int it = gaussSeidel(sl2, Xgs, TOL, MAXIT, &norma);
    residuo(sl2, Xgs, Rgs, sl2->n);

    printf("EG:\n");
    printf("COLOCAR TEMPO DPS   ms\n");
    prnVetor(Xeg, sl->n);
    prnVetor(Reg, sl->n);
    printf("\n");

    printf("GS [ %d iterações ]:\n", it);
    printf("COLOCAR TEMPO DPS   ms\n");
    prnVetor(Xgs, sl2->n);
    prnVetor(Rgs, sl2->n);
    

    liberaSisLin(sl);
    liberaSisLin(sl2);
    free(Xeg);
    free(Reg);
    free(Xgs);
    free(Rgs);

    return 1;
}