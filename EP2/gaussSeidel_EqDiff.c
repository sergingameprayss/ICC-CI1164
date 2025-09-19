// SERGIO SIVONEI DE SANT'ANA FILHO - GRR 20242337
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <fenv.h>

#include "utils.h"
#include "edo.h"
#include "gaussSeidel_EqDiff.h"


rtime_t gaussSeidel_3Diag (Tridiag *sl, real_t *Y, int *it, unsigned int maxiter) {
    int n = sl->n;
    rtime_t tTotal = timestamp();

    fesetround(FE_DOWNWARD);
    // algoritmo  Gauss-Seidel   com  vetores   das  diagonais   e  termos
    // independentes do SL
    *it = 0;
    while(normaL2_3Diag(sl, Y) > 1e-5 && (*it) < maxiter) {
        (*it) += 1;
        
        // 5(n-2)+6 ≈ 5n operações / iteração
        Y[ 0 ] = (sl->B[ 0 ] - sl->Ds[ 0 ] * Y[ 1 ]) / sl->D[ 0 ];
        for (int i=1; i < n-1; ++i)
            Y[ i ] = (sl->B[ i ] - sl->Di[ i-1 ] * Y[ i-1] - sl->Ds[ i ] * Y[ i+1 ]) / sl->D[ i ];
        Y[ n-1 ] = (sl->B[ n-1 ] - sl->Di[ n-2 ] * Y[ n-2 ] ) / sl->D[ n-1 ];
        
    }

    return timestamp() - tTotal;

}

real_t normaL2_3Diag (Tridiag *sl, real_t *Y) {
    int n = sl->n;
    fesetround(FE_DOWNWARD);
    real_t normaL2 = 0.0;

    for (int i = 0; i < n; i++) {
        real_t Ay_i;

        if (i == 0)
            Ay_i = (sl->D[0] * Y[0]) + (sl->Ds[0] * Y[1]);
        else if (i == n - 1)
            Ay_i = (sl->Di[i-1] * Y[i-1]) + (sl->D[i] * Y[i]);
        else
            Ay_i = (sl->Di[i-1] * Y[i-1]) + (sl->D[i] * Y[i]) + (sl->Ds[i] * Y[i+1]);

        normaL2 += (sl->B[i] - Ay_i) * (sl->B[i] - Ay_i);
    }

    return sqrt(normaL2);
}

