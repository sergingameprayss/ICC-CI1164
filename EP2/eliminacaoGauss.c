/* Matriz  'normal' (vetor  de  ponteiros (linhas  matriz) para  vetores
   (colunas da matriz), estilo 'Mazieiro/Prog 2'
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"
#include "sislin.h"
#include "eliminacaoGauss.h"

static int encontraMax(SistLinear_t *C, int k)
{
  
}

static void trocaLinha (SistLinear_t *C, int k, int p, int n)
{
  
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
            trocaLinha( C, C->b, i, iPivo );
        for(int k=i+1; k < n; ++k) {
            double m = A[k][i] / A[i][i];
            A[k][i] = 0.0;
            for(int j=i+1; j < n; ++j)
                A[k][j] -= A[i][j] * m;
            b[k] -= b[i] * m;
}

void retrosubst( SistLinear_t *C, real_t *X )
{
 
}
