#include <stdio.h>
#include <time.h>

#include "eliminacaoGauss.h"
#include "gaussSeidel.h"
#include "sislin.h"
#include "utils.h"

int main () {

    SistLinear_t *sl = lerSisLin();

    prnSisLin(sl);

    triangulariza(sl);

    prnSisLin(sl);

    liberaSisLin(sl);

    return 1;
}