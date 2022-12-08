#include "defs.h"
#include <stdio.h>
#include <math.h>

#define NX  256
#define NT  20000000

#define X0  ((number)0.0)
#define XN  ((number)2.0)
#define T0  ((number)0.0)
#define TN  ((number)8.0)

#define EPS ((number)1.0)
#define MU  ((number)(0.022 * 0.022))

#define DX  ((XN - X0) / NX)
#define DT  ((TN - T0) / NT)

#define NR  32

int main(void)
{
  int r, j;
  number u0[NX], u1[NX];

  for(j = 0; j < NX; ++j)
  {
    u0[j] = cos((2*M_PI) * j / NX);
    printf("%25.13la", u0[j]);
  }
  printf("\n");
  for(r = 0; r < NR; ++r)
  {
    fprintf(stderr, "run [%2d]: t = %.2lf\n",
        r, (double)(T0 + (NT / NR) * r * DT));
    kdv(NT / NR, NX, u0, u1, DT, DX, EPS, MU, r == 0);
    for(j = 0; j < NX; ++j)
      printf("%25.13la", u0[j]);
    printf("\n");
  }
  return 0;
}
