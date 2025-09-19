// SERGIO SIVONEI DE SANT'ANA FILHO - GRR 20242337
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <likwid.h>
#include <fenv.h>

#include "utils.h"
#include "edo.h"
#include "gaussSeidel_EqDiff.h"


int main () {
    fesetround(FE_DOWNWARD);
    LIKWID_MARKER_INIT;
    
    int h;
    real_t norma;
    EDo *edo = malloc(sizeof(EDo));

    scanf("%d", &h);
    
    edo->n = h;
    real_t *Y = calloc(edo->n, sizeof(real_t));

    scanf("%lf %lf", &edo->a, &edo->b);
    scanf("%lf %lf", &edo->ya, &edo->yb);
    scanf("%lf %lf", &edo->p, &edo->q);

    int i = 0;
    while (scanf("%lf %lf %lf %lf", &edo->r1, &edo->r2, &edo->r3, &edo->r4) != EOF){    
        int it = 0;
        zera_vetor(Y, edo->n);
        printf("\n");
        Tridiag *sl = genTridiag(edo);
        prnEDOsl(edo);

        LIKWID_MARKER_START(markerName("TEST", i));
        
        real_t time = gaussSeidel_3Diag(sl, Y, &it, MAXIT);

        LIKWID_MARKER_STOP(markerName("TEST", i));

        prnVetor(Y, sl->n);
        printf("%d\n", it);
        norma = normaL2_3Diag(sl, Y); 
        printf(FORMAT, norma);
        printf("\n");
        printf("%16.8e", time);
        printf("\n");
        ++i;
    }


    free(edo);
    free(Y);


    LIKWID_MARKER_CLOSE;
    return 0;
}
