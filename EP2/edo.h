// SERGIO SIVONEI DE SANT'ANA FILHO - GRR 20242337
#ifndef __EQDIFF_H__
#define __EQDIFF_H__


typedef double real_t;


// Sistema linear Tri-diagonal
typedef struct {
  real_t *D, *Di, *Ds, *B;
  int n;
} Tridiag;

// Equação Diferencial Ordinária
typedef struct {
  int n; // número de pontos internos na malha
  real_t a, b; // intervalo
  real_t ya, yb; // condições contorno
  real_t p, q, r1, r2, r3, r4; // coeficientes EDO genérica
} EDo;

// Funções auxiliares

Tridiag *genTridiag (EDo *edoeq);
void prnEDOsl (EDo *edoeq);

#endif // __EQDIFF_H__

