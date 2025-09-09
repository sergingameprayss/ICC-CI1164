#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utils.h"
#include "edo.c"

int main () {
    int h;
    real_t a, b, Ya, Yb, p,q;

    scanf("%d\n", &h);
    scanf("%lf, %lf\n", &a, &b);
    scanf("%lf, %lf\n", &Ya, &Yb);
    scanf("%lf, %lf\n", &p, &q);


    // ver logica de ler os coeficientes linha a linha
    // a apartir da quinta
    real_t *r = calloc(4, sizeof(real_t));
    
    

    return 0;
}
