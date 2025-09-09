#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fenv.h>

#include "utils.h"
#include "sislin.h"
#include "gaussSeidel.h"

// Método de Gauss-Seidel clássico
int gaussSeidel (SistLinear_t *C, real_t *X, real_t erro, int maxit, real_t *norma){
    fesetround(FE_DOWNWARD);
    real_t *X_old = malloc(C->n * sizeof(real_t));
    int it = 0;

    do {
        //copia as ultimas incognitas para x
        for(int i = 0; i < C->n; ++i){
            X_old[i] = X[i];
        }

        for(int i = 0; i < C->n; ++i){
            real_t soma = C->b[i];
            for(int j = 0; j < C->n; ++j){
                soma -= C->A[i][j] * X[j]*((j != i));
            }
            
            X[i] = soma / C->A[i][i];
        }
        *norma = normaMax(X, X_old, C->n);
        it++;
    } while ((*norma) >= erro && it < maxit);


    free(X_old);
    return it;
}


