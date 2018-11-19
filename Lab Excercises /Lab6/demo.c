#include <stdio.h>
#include <math.h>

double sum(double (*f)(double), int start, int end);
double f(double g);

double sum(double (*f)(double), int start, int end)
{
  int c;
  double sum=0;

  for(c = start; c <= end; c++)
    sum += f(c);

  return sum;
}

double f(double g)
{
  return (sqrt(g));
}

int main(void)
{
  int i=1, j=10;

  double (*g)(double);
  g = &f;

  double sqrtSum = sum(g, i, j);

  printf("The sum is: %f\n", sqrtSum);

  return 0;
}
