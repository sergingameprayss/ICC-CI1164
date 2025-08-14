#include <stdio.h>
#include <math.h>

#include "utils.h"
#include "ZeroFuncao.h"

// ERRO EH O VALOR QUE FAZ SAIR DO WHILE PARA CADA CASO DE CRITERIO (ERRO MUDA C0ONFORME CRITERIO)

// Retorna valor do erro quando método finalizou. Este valor depende de tipoErro
real_t newtonRaphson (Polinomio p, real_t x0, int criterioParada, int *it, real_t *raiz)
{

}


// Retorna valor do erro quando método finalizou. Este valor depende de tipoErro
real_t bisseccao (Polinomio p, real_t a, real_t b, int criterioParada, int *it, real_t *raiz){


    //switch (criterioParada)  // critério de parada
    //{
    //case 1:
      //  /* code */
        //break;
    
    //default:
    //    break;
    //}

    real_t xm_old, xm_new;

    xm_new = (a + b) / 2.0;
    real_t pa, pb, pxm;
    calcPolinomio_rapido(p, a, &pa, NULL); //CUIDADO NULL AQ
    calcPolinomio_rapido(p, xm_new, &pxm, NULL);

    if (pa * pxm < 0) {
        b = xm_new;
    } else if (pa * pxm > 0) {
        a = xm_new;
    } else  {
        *raiz  = xm_new;
        return ERRO; // Retorna erro 0 se raiz exata encontrada
    }
    do {
        xm_old = xm_new;
        xm_new = (a + b) / 2.0;
        calcPolinomio_rapido(p, a, &pa, NULL);
        calcPolinomio_rapido(p, xm_new, &pxm, NULL);
        if (pa * pxm < 0) {
            b = xm_new;
        } else if (pa * pxm > 0) {
            a = xm_new;
        } else {
            *raiz = xm_new;
            return ERRO;
        }
        (*it)++;
    } while (CRITERIO && (*it) < MAXIT); //ver condição criterio aq

    return ERRO; // Retorna erro se não convergiu
}


void calcPolinomio_rapido(Polinomio p, real_t x, real_t *px, real_t *dpx)
{
    real_t b = 0;
    real_t c = 0;
    for (int i = p.grau; i > 0; --i) {
        b = b * x + p.p[i];
        c = c*x + b;
    }

    b = b*x + p.p[0];
    *px = b;
    *dpx = c;

}


void calcPolinomio_lento(Polinomio p, real_t x, real_t *px, real_t *dpx)
{
    for (int i = p.grau; i >= 0; --i) {
        *px += p.p[i] * pow(x, i);
    }

    for (int i = p.grau; i > 0; --i) {
        *dpx += i * p.p[i] * pow(x, i - 1);
    }

}
