#pragma once

#include <stddef.h>

#ifndef number
#define number double
#define NBR_EPSILON DBL_EPSILON
#endif  /* number */

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif  /* M_PI */

int kdv(int nt, int nx, number u0[nx], number u1[nx],
    number dt, number dx, number eps, number mu, int first);
