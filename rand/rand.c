#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <err.h>

#define N 10000
#define R 10000

int main(void)
{
  time_t t;
  long seed;
  int i, r;
  double d;
  unsigned long dd;
  unsigned long b[10];

  if((t = time(0)) == -1)
    err(EXIT_FAILURE, "time");
  seed = t ^ getpid();
  srand48(seed);
  fprintf(stderr, "seed: %ld\n", seed);

  for(r = 0; r < R; ++r)
  {
    for(i = 0; i < 10; ++i)
      b[i] = 0;
    for(i = 0; i < N; ++i)
    {
      d = drand48();  // uniformly over [0.0, 1.0)
      if((dd = d * 10) >= 10)
        errx(EXIT_FAILURE, "unexpected value: %a", d);
      ++b[dd];
    }
    printf("%lu\n", b[3]);
  }

  return 0;
}
