#include <stdio.h>
#include <math.h>

#define number double

#define M       128
#define N       128
#define L        32
#define LL       32

#define X0      0.0
#define XM      1.0
#define Y0      0.0
#define YN      1.0
#define T0      0.0
#define TL      1.0

#define LAMBDA  1.0

int main(void)
{
  number _u0[M + 1][N + 1], _u1[M + 1][N + 1], _u2[M + 1][N + 1];
  number (*u0)[N + 1] = _u0, (*u1)[N + 1] = _u1, (*u2)[N + 1] = _u2;
  number (*uu)[N + 1];
  number x, y;
  int ll, l, m, n;
  number TX = LAMBDA * pow(((TL - T0) / (L * LL)) / ((XM - X0) / M), 2);
  number TY = LAMBDA * pow(((TL - T0) / (L * LL)) / ((YN - Y0) / N), 2);

  for(m = 0; m <= M; ++m)
  {
    x = X0 + (XM - X0) * m / M;
    for(n = 0; n <= N; ++n)
    {
      y = Y0 + (YN - Y0) * n / N;
      u0[m][n] = u1[m][n] = sin(M_PI * x) * sin(2 * M_PI * y);
    }
  }
  for(n = 0; n <= N; ++n)
    u2[0][n] = 0;
  for(m = 1; m < M; ++m)
    u2[m][0] = u2[m][N] = 0;
  for(n = 0; n <= N; ++n)
    u2[M][n] = 0;

  for(m = 0; m <= M; ++m)
  {
    for(n = 0; n <= N; ++n)
      printf("%+26.17le", u0[m][n]);
    printf("\n");
  }
  printf("\n");

  for(l = 1; l <= L; ++l)
  {
    for(ll = l == 1 ? 2 : 1; ll <= LL; ++ll)
    {
      for(m = 1; m < M; ++m)
        for(n = 1; n < N; ++n)
        {
          u2[m][n] = 2*u1[m][n] - u0[m][n] + TX * (
            u1[m-1][n] - 2*u1[m][n] + u1[m+1][n]
          ) + TY * (
            u1[m][n-1] - 2*u1[m][n] + u1[m][n+1]
          );
        }
      uu = u0;
      u0 = u1;
      u1 = u2;
      u2 = uu;
    }
    for(m = 0; m <= M; ++m)
    {
      for(n = 0; n <= N; ++n)
        printf("%+26.17le", u1[m][n]);
      printf("\n");
    }
    printf("\n");
  }

  return 0;
}
