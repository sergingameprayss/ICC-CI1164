#include <stdio.h>
#include <math.h>

#include "utils.h"
#include "ZeroFuncao.h"
#include "DoubleType.h"



// ERRO EH O VALOR QUE FAZ SAIR DO WHILE PARA CADA CASO DE CRITERIO (ERRO MUDA C0ONFORME CRITERIO)
//FAZER AS 3 FUNÇÕES QUE CALCULAM O TIPO DE ERRO
//CHAMAR UMA FUNÇÃO DE CONTROLE NO WHILE TODA VEZ
//ESSA FUNÇÃO RECEBE UM ENUM? E AI TEM QUAL EH O TIPO
//DAWN

// //funções de erro privadas
// real_t erro_tipo_1 (real_t xk, real_t xk1) {
//     return fabs(xk - xk1) / fabs(xk);
// }

// real_t erro_tipo_2 (real_t fxk) {
//     return fabs(xk - xk1) / fabs(xk);
// }

// real_t erro_tipo_1 (real_t xk, real_t xk1) {
//     return fabs(xk - xk1) / fabs(xk);
// }

//retorna se o erro atinge o criterio de parada
//coloca o valor do erro na variavel valErro
real_t calcErros (real_t fxk, real_t xk, real_t xk1, real_t *valErro, int criterio) {

    //MELHOR NAO USAR SWITCH DEVIDOP AOS BREAKS
    switch (criterio) {
        case CRITERIO_1:
            *valErro = fabs(xk - xk1) / fabs(xk);
            return (*valErro <= pow(10, -7));
            break;

        case CRITERIO_2:
            *valErro = fabs(fxk);
            return (*valErro <= DBL_EPSILON);
            break;
        case CRITERIO_3:
            Double_t uxk, uxk1;
            uxk.f = xk;
            uxk1.f = xk1;
            *valErro = fabs(uxk.i - uxk1.i) - 1;
            return (*valErro <= 3);
            break;
        }

        return 0;
}

// Retorna valor do erro quando método finalizou. Este valor depende de tipoErro
real_t newtonRaphson (Polinomio p, real_t x0, int criterioParada, int *it, real_t *raiz, int tipoCalc) {



    //metodo da iteração linear
    real_t x_new = x0, x_old, fx, fdx;
    real_t valErro = 0;
    void (*calculo)(Polinomio, real_t, real_t *, real_t *) = calcPolinomio_rapido;
    
    if(tipoCalc == 1) {
        calculo = calcPolinomio_lento;
    }

    (*it) = 0;
    do {
        x_old = x_new;
        calculo(p, x_old, &fx, &fdx);
        x_new = x_old - fx / fdx; //CUIDAR CASO FDX == 0
    } while (calcErros(fx, x_new, x_old, &valErro, criterioParada) && (*it) < MAXIT);

    *raiz = x_new;
    
    return valErro;

}


// Retorna valor do erro quando método finalizou. Este valor depende de tipoErro
real_t bisseccao (Polinomio p, real_t a, real_t b, int criterioParada, int *it, real_t *raiz, int tipoCalc){

    real_t valErro = 0;

    void (*calculo)(Polinomio, real_t, real_t *, real_t *) = calcPolinomio_rapido;

    // real_t (*erro)(real_t xk, real_t xk1, real_t fxk)

    if(tipoCalc == 1) {
        calculo = calcPolinomio_lento;
    }

    real_t xm_old, xm_new;

    xm_new = (a + b) / 2.0;
    real_t pa, pb, pxm;

    (*it) = 0;
    //FAZER PŔO LENTO TB
    calculo(p, a, &pa, NULL); //CUIDADO NULL AQ
    calculo(p, xm_new, &pxm, NULL);

    if (pa * pxm < 0) {
        b = xm_new;
    } else if (pa * pxm > 0) {
        a = xm_new;
    } else  {
        *raiz  = xm_new;
        return valErro; // Retorna erro 0 se raiz exata encontrada
    }
    do {
        (*it)++;

        xm_old = xm_new;
        xm_new = (a + b) / 2.0;
            //FAZER PŔO LENTO TB
        calculo(p, a, &pa, NULL);
        calculo(p, xm_new, &pxm, NULL);
        if (pa * pxm < 0) {
            b = xm_new;
        } else if (pa * pxm > 0) {
            a = xm_new;
        } else {
            *raiz = xm_new;
            return 0; //pois raiz encontradq????????
        }
    } while (calcErros(pxm, xm_new, xm_old, &valErro, criterioParada) && (*it) < MAXIT); //ver condição criterio aq

    *raiz = xm_new;

    return valErro; // Retorna erro se não convergiu
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
