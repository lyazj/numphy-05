#include "defs.h"
#include <stdlib.h>

// input: u0, u1, initial values
// output: u0, u1, final values
// assume: u[:,j + n] := u[:,j]
// XXX[performance] idiv instruction used
int kdv(int nt, int nx, number u0[nx], number u1[nx],
    number dt, number dx, number eps, number mu, int first)
{
  int i, j;
  number _u2[nx], *u2 = _u2, *ut, *uo0 = u0, *uo1 = u1;

  // Validate arguments to improve optimization.
  if(nt < 1 || nx < 3)
    return -1;
  if(labs(u0 - u1) < nx)
    return -1;

  if(first)  // i -> i + 1
  {
    // Approximate initial values u1.
    for(j = 0; j < nx; ++j)
    {
      u1[j] = u0[j]
        + (eps / 6) * (dt / dx)
          * (u0[(j-1+nx) % nx] + u0[j] + u0[(j+1) % nx])
          * (u0[(j-1+nx) % nx] - u0[(j+1) % nx])
        + (mu / 2) * (dt / (dx*dx*dx))
          * (u0[(j-2+nx) % nx] - 2*u0[(j-1+nx) % nx] + 2*u0[(j+1) % nx] - u0[(j+2) % nx])
      ;
    }
  }

  for(i = 0; i < nt; ++i)  // i -> i + 2
  {
    // Compute u0, u1 after time span dt.
    for(j = 0; j < nx; ++j)
    {
      u2[j] = u0[j]
        + (eps / 3) * (dt / dx)
          * (u1[(j-1+nx) % nx] + u1[j] + u1[(j+1) % nx])
          * (u1[(j-1+nx) % nx] - u1[(j+1) % nx])
        + (mu / 1) * (dt / (dx*dx*dx))
          * (u1[(j-2+nx) % nx] - 2*u1[(j-1+nx) % nx] + 2*u1[(j+1) % nx] - u1[(j+2) % nx])
      ;
    }
    ut = u0;
    u0 = u1;
    u1 = u2;
    u2 = ut;
  }

  // Write back results.
  if(u0 == uo0)
  {
    // do nothing
  }
  else if(u0 == uo1)  // u1 == _u2
  {
    for(j = 0; j < nx; ++j)
    {
      uo0[j] = u0[j];
      uo1[j] = u1[j];
    }
  }
  else  // u0 == _u2  u1 == uo0
  {
    for(j = 0; j < nx; ++j)
    {
      uo1[j] = u1[j];
      uo0[j] = u0[j];
    }
  }
  return 0;
}
