#include <stdio.h>
#include <math.h>
#include <err.h>

#define number double

#define M     128
#define MM    128
#define N     128
#define L      10
#define LL   1024

#define X0    0.0
#define XM    1.0
#define Y0    0.0
#define YN    1.0
#define T0    0.0
#define TL    1.0

static int tdm_tri(int n, int m,
    number d[n], number l[n], number u[n], number r[n][m]);

int main(void)
{
  int m, n, l, ll, mm;
  number x, y;
  static number TT[M + 1][L + 1][N + 1], T[MM + 1][L + 1][N + 1];
  number C = ((TL - T0) / (L * LL)) / pow((YN - Y0) / N, 2);

  fprintf(stderr, "C = %.17le\n", (double)C);

  for(m = 1; m <= M; ++m)  // XXX: parallelism
  {
    number mpi = m * M_PI;
    number Km = mpi * ((YN - Y0) / N);

    fprintf(stderr, "m = %3d  Km = %.17le\n", m, (double)Km);

    l = 0;
    for(n = 0; n <= N; ++n)
    {
      y = Y0 + (YN - Y0) * n / N;
      if(fabs(y - 0.5) >= 0.1)
        TT[m][l][n] = 0;
      else
        TT[m][l][n] = (cos(0.4 * mpi) - cos(0.6 * mpi)) / mpi;
    }
    printf("m = %d  l = %d\n", m, l);
    for(n = 0; n <= N; ++n)
      printf("%+.17le\n", (double)TT[m][l][n]);
    printf("\n");

    for(l = 1; l <= L; ++l)
    {
      number TT0[n];

      for(n = 0; n <= N; ++n)
        TT0[n] = TT[m][l - 1][n];

      for(ll = 0; ll < LL; ++ll)
      {
        number a[N - 1], b[N - 1], d[N - 1];
        int i;

        for(i = 1; i < N - 1; ++i)
          a[i] = -C / 2;
        for(i = 0; i < N - 2; ++i)
          b[i] = -C / 2;

        d[0] = 1 + C / 2 * (1 + Km * Km);
        for(i = 1; i < N - 2; ++i)
          d[i] = 1 + C * (1 + Km * Km / 2);
        d[N - 2] = 1 + C / 2 * (1 + Km * Km);

        for(i = 0; i < N - 1; ++i)
        {
          n = i + 1;
          TT[m][l][n] = C / 2 * TT0[n - 1]
            + (1 - C * (1 + Km * Km / 2)) * TT0[n]
            + C / 2 * TT0[n + 1];
        }

        if(tdm_tri(N - 1, 1, d, a, b, (void *)&TT[m][l][1]) != N - 1)
          errx(1, "tdm_tri failed: m = %d l = %d", m, l);
        TT[m][l][0] = TT[m][l][1];
        TT[m][l][N] = TT[m][l][N - 1];

        for(n = 0; n <= N; ++n)
          TT0[n] = TT[m][l][n];
      }

      printf("m = %d  l = %d\n", m, l);
      for(n = 0; n <= N; ++n)
        printf("%+.17le\n", (double)TT[m][l][n]);
      printf("\n");
    }
  }

  for(mm = 0; mm <= MM; ++mm)
  {
    fprintf(stderr, "mm = %3d\n", mm);
    for(l = 0; l <= L; ++l)
      for(n = 0; n <= N; ++n)
        T[mm][l][n] = 0;
    for(m = 0; m <= M; ++m)
    {
      number mpi = m * M_PI;
      x = X0 + (XM - X0) * mm / MM;
      for(l = 0; l <= L; ++l)
        for(n = 0; n <= N; ++n)
          T[mm][l][n] += 2 * TT[m][l][n] * sin(mpi * x);
    }
    for(l = 0; l <= L; ++l)
    {
      printf("mm = %d  l = %d\n", mm, l);
      for(n = 0; n <= N; ++n)
        printf("%+.17le\n", (double)T[mm][l][n]);
      printf("\n");
    }
  }

  return 0;
}

int tdm_tri(int n, int m,
    number d[n], number l[n], number u[n], number r[n][m])
{
  number a, b;
  int i, j;

  // LU decomposition
  if((a = d[0]) == 0)
    return 0;
  for(i = 1; i < n; ++i)
  {
    b = l[i] / a;
    l[i] = b;
    a = d[i] - b * u[i - 1];
    d[i] = a;
    if(a == 0)
      return i;
  }

  for(i = 1; i < n; ++i)
    for(j = 0; j < m; ++j)
      r[i][j] -= l[i] * r[i - 1][j];
  for(j = 0; j < m; ++j)
    r[n - 1][j] /= d[n - 1];
  for(i = n - 2; i >= 0; --i)
    for(j = 0; j < m; ++j)
      r[i][j] = (r[i][j] - u[i] * r[i + 1][j]) / d[i];
  return n;
}
