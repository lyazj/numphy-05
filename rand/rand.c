#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <err.h>

#define N 10000
#define R 10000

int main(int argc, const char *argv[])
{
  time_t t;
  long seed;
  int i, r;
  double d;
  unsigned long dd;
  unsigned long b[10] = { };

  if(argc == 1)
  {
    if((t = time(0)) == -1)
      err(EXIT_FAILURE, "time");
    seed = t ^ getpid();
  }
  else if(argc == 2)
    seed = atoi(argv[1]);
  else
    errx(EXIT_FAILURE, "expect 0 or 1 arguments");
  srand48(seed);
  fprintf(stderr, "seed: %ld\n", seed);

  for(r = 0; r < R; ++r)
  {
    for(i = 0; i < N; ++i)
    {
      d = drand48();  // uniformly over [0.0, 1.0)
      if((dd = d * 10) >= 10)
        errx(EXIT_FAILURE, "unexpected value: %a", d);
      ++b[dd];
    }
    for(i = 0; i < 10; ++i)
    {
      printf("%6lu", b[i]);
      b[i] = 0;
    }
    printf("\n");
  }

  return 0;
}
