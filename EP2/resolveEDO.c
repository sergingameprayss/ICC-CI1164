#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utils.h"
#include "edo.h"
#include "gaussSeidel_EqDiff.h"


int main () {
    int h;
    real_t norma;
    EDo *edo = malloc(sizeof(EDo));

    scanf("%d", &h);
    
    edo->n = h;
    real_t *Y = calloc(edo->n, sizeof(real_t));

    scanf("%lf %lf", &edo->a, &edo->b);
    scanf("%lf %lf", &edo->ya, &edo->yb);
    scanf("%lf %lf", &edo->p, &edo->q);
    // ver logica de ler os coeficientes linha a linha
    // a apartir da quinta 
    while (scanf("%lf %lf %lf %lf", &edo->r1, &edo->r2, &edo->r3, &edo->r4) != EOF){    
        int it = 0;
        zera_vetor(Y, edo->n);
        Tridiag *sl = genTridiag(edo);

        prnEDOsl(edo);
        real_t time = gaussSeidel_3Diag(sl, Y, &it, MAXIT);
        prnVetor(Y, sl->n);
        printf("%d\n", it);
        norma = normaL2_3Diag(sl, Y); 
        printf(FORMAT, norma);
        printf("\n");
        printf("%16.8e", time);
        printf("\n");
    }


    free(edo);
    free(Y);



    return 0;
}
