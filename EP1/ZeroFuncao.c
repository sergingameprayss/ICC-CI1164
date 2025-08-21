#include <stdio.h>
#include <math.h>
#include <fenv.h>
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
    fesetround(FE_DOWNWARD);

    if(criterio == CRITERIO_1){
        real_t dif = fabs(xk - xk1);
        if(fabs(xk) <= ZERO)
            *valErro = dif;
        else *valErro = dif / fabs(xk);

        return (*valErro <= EPS);
    }


    if(criterio == CRITERIO_2){
        *valErro = fabs(fxk);
        return (*valErro <= ZERO);
    }

    if(criterio == CRITERIO_3) {
        Double_t uxk, uxk1;
        uxk.f = xk;
        uxk1.f = xk1;
        *valErro = llabs(uxk.i - uxk1.i) - 1;
        if(*valErro < ZERO){
            *valErro = 0.0;
        }
        return (*valErro <= ULPS);    
    }

    return 0;
}

// Retorna valor do erro quando método finalizou. Este valor depende de tipoErro
real_t newtonRaphson (Polinomio p, real_t x0, int criterioParada, int *it, real_t *raiz, int tipoCalc) {
    
    fesetround(FE_DOWNWARD);


    //metodo da iteração linear
    real_t x_new = x0, x_old, fx, fdx, old_fdx;
    real_t valErro = 0;
    void (*calculo)(Polinomio, real_t, real_t *, real_t *) = calcPolinomio_rapido;
    
    if(tipoCalc == 1) {
        calculo = calcPolinomio_lento;
    }

    (*it) = 1;
    do {

        x_old = x_new;
        calculo(p, x_old, &fx, &fdx);
        if(fabs(fdx) > ZERO){
            old_fdx = fdx;
            x_new = x_old - (fx / fdx);
        } else  x_new = x_old - (fx / old_fdx);

        calculo(p, x_old, &fx, &fdx);
        ++(*it);
    } while (!calcErros(fx, x_new, x_old, &valErro, criterioParada) && (*it) < MAXIT);

    *raiz = x_new;
    
    return valErro;

}


// Retorna valor do erro quando método finalizou. Este valor depende de tipoErro
real_t bisseccao (Polinomio p, real_t a, real_t b, int criterioParada, int *it, real_t *raiz, int tipoCalc){
    
    fesetround(FE_DOWNWARD);
    real_t valErro = 0;

    void (*calculo)(Polinomio, real_t, real_t *, real_t *) = calcPolinomio_rapido;

    if(tipoCalc == 1) {
        calculo = calcPolinomio_lento;
    }

    real_t xm_old, xm_new;

    xm_new = (a + b) / 2.0;
    real_t pa, pb, pxm, d;

    (*it) = 1;

    calculo(p, a, &pa, &d); 
    calculo(p, xm_new, &pxm, &d);

    if (pa * pxm < 0) {
        b = xm_new;
    } else if (pa * pxm > 0) {
        a = xm_new;
    } else  {
        *raiz = xm_new;
        return valErro; // Retorna erro 0 se raiz exata encontrada
    }
    do {
        
        ++(*it);

        xm_old = xm_new;
        xm_new = (a + b) / 2.0;
        calculo(p, a, &pa, &d);
        calculo(p, xm_new, &pxm, &d);
        if (pa * pxm < 0) {
            b = xm_new;
        } else if (pa * pxm > 0) {
            a = xm_new;
        } else {
            *raiz = xm_new;
            return 0; 
        }
    } while (!calcErros(pxm, xm_new, xm_old, &valErro, criterioParada) && (*it) < MAXIT); //ver condição criterio aq

    *raiz = xm_new;

    return valErro; // Retorna erro se não convergiu
}


void calcPolinomio_rapido(Polinomio p, real_t x, real_t *px, real_t *dpx)
{
    fesetround(FE_DOWNWARD);
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
    fesetround(FE_DOWNWARD);

    *px = 0.0;
    *dpx = 0.0;

    for (int i = p.grau; i >= 0; --i) {
        *px += p.p[i] * pow(x, i);
    }

    for (int i = p.grau; i > 0; --i) {
        *dpx +=  p.p[i] * i * pow(x, i - 1);
    }

}
