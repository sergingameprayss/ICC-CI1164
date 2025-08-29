/* Matriz  'normal' (vetor  de  ponteiros (linhas  matriz) para  vetores
   (colunas da matriz), estilo 'Mazieiro/Prog 2'
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"
#include "sislin.h"
#include "eliminacaoGauss.h"

static int encontraMax(SistLinear_t *C, int l) {
    int large_line = l;

    for(int i = l+1; i < C->n; ++i){
        if(C->A[i][l] > C->A[large_line][l]){
            large_line = i;
        }
    }

    return large_line;
}

static void trocaLinha (SistLinear_t *C, int l, int lp) {

    //troca linhas da matriz
    *(long *)&(C->A[l]) ^= *(long *)&(C->A[lp]);
    *(long *)&(C->A[lp]) ^= *(long *)&(C->A[l]);
    *(long *)&(C->A[l]) ^= *(long *)&(C->A[lp]);

    //troca linhas dos termos independentes
    *(long *)&(C->b[l]) ^= *(long *)&(C->b[lp]);
    *(long *)&(C->b[lp]) ^= *(long *)&(C->b[l]);
    *(long *)&(C->b[l]) ^= *(long *)&(C->b[lp]);

}

/* Seja um S.L. de ordem 'n'
   C = A|B em Ax=B
 */
void triangulariza( SistLinear_t *C)
{
    /* para cada linha a partir da primeira */
    for (int i=0; i < C->n; ++i) {
        unsigned int iPivo = encontraMax(C, i);
        if ( i != iPivo )
            trocaLinha( C, i, iPivo);
        for(int k=i+1; k < C->n; ++k) {
            double m = C->A[k][i] / C->A[i][i];
            C->A[k][i] = 0.0;
            for(int j=i+1; j < C->n; ++j)
                C->A[k][j] -= C->A[i][j] * m;
            C->b[k] -= C->b[i] * m;
        }
    }
}

void retrosubst( SistLinear_t *C, real_t *X )
{
 
}
