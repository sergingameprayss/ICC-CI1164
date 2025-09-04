#include <stdio.h>
#include <time.h>
#include <likwid.h>

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

    LIKWID_MARKER_INIT;
    LIKWID_MARKER_START("EG_TEST");
    rtime_t time_EG = timestamp();

    triangulariza(sl);
    retrosubst(sl, Xeg);
    residuo(sl, Xeg, Reg, sl->n);

    printf("EG:\n");
    printf("%.8e\n", timestamp() - time_EG);
    prnVetor(Xeg, sl->n);
    prnVetor(Reg, sl->n);
    printf("\n");

    LIKWID_MARKER_STOP("EG_TEST");
    LIKWID_MARKER_CLOSE;

    int it = gaussSeidel(sl2, Xgs, TOL, MAXIT, &norma);
    residuo(sl2, Xgs, Rgs, sl2->n);

    

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