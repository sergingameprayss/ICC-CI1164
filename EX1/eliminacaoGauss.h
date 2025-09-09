#ifndef _ELIMINACAO_GAUSS_
#define _ELIMINACAO_GAUSS_

#include "sislin.h"

void triangulariza( SistLinear_t *C );
void retrosubst( SistLinear_t *C, real_t *X);


#endif