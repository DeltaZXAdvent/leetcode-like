#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <stdlib.h>
void reverse (int *begin, int *end)
{
  while (begin < end)
    {
      int tmp = *begin;
      *begin++ = *end;
      *end-- = tmp;
    }
}

void swap_multiple (int *begin, int *mid, int *end)
{
  reverse (begin, end);
  reverse (begin, mid);
  reverse (mid, end);
}

int gcd (int a, int b)
{
  if (b == 0)
    return a;
  return gcd (b, a - a / b * b);
}

void swap_multiple_direct (int *begin, int *mid, int *end)
{
  int m = mid - begin,
    n = end - mid,
    k = gcd (m, n);
  for (int *start = begin; start != begin + k; ++start)
    {
      int *cur = start,
	tmp1 = *cur,
	tmp2,
	use_tmp1 = 1;
      do
	{
	  cur = cur < mid ?
	    cur + n : cur - m;
	  if (use_tmp1)
	    { tmp2 = *cur; *cur = tmp1; }
	  else
	    { tmp1 = *cur; *cur = tmp2; }
	  use_tmp1 = !use_tmp1;
	}
      while (cur != start);
    }
}

void print_vec (int *begin, int *end)
{
  printf ("[");
  for (; begin < end; ++begin)
    printf ("%d ", *begin);
  printf ("]\n");
}

void my_getline ()
{
  int ch;
  while ((ch = getchar ()) != '\n')
    assert (ch != EOF);
}

clock_t cp;
#define timer(exp) do {							\
    cp = clock ();							\
    printf ("%s", "press to start timer for task "#exp);		\
    my_getline ();							\
    (exp);								\
    clock_t new_cp = clock ();						\
    printf ("time spent: %f seconds\n", (double) (new_cp - cp) / CLOCKS_PER_SEC); \
    cp = new_cp;							\
  } while (0)

int main (int argc, char *argv[])
{
  assert (argc == 3);
  size_t m = atol (argv[1]),
    n = atol (argv[2]);
  printf ("m: %zu, n: %zu, sizeof (int) * (m + n): %zu\n", m, n, m + n, sizeof (int) * (m + n));
  int *vec = malloc (sizeof (int) * (m + n));
  for (size_t i = 0; i < m + n; ++i)
    vec[i] = i;
  timer (swap_multiple (vec, vec + m, vec + m + n));
  my_getline ();
  /* print_vec (vec, vec + m + n); */
  timer (swap_multiple_direct (vec, vec + m, vec + m + n));
  my_getline ();
  /* print_vec (vec, vec + m + n); */
  timer (gcd (m, n));
  free (vec);
  return 0;
}
