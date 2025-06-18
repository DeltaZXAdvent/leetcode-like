/**
 * https://codeforces.com/contest/2114/problem/G
 *
 * Investigation:
 * Every element can come from two halves of it.
 * 
 * Each element A is composed of one to s(A) atomic parts,
 * where s(A) is the largest power of two that can divide A.
 * Define b(A) := A / s(A)
 *
 * However not all values between the range are valid.
 *
 * The simplest case is [2, 1, 2].
 * The composition of adjacent elements cannot coincide.
 * The composition of elements have order because you can only insert elements
 * from two ends.
 *
 * Suppose an array [..., A, B, C, ...],
 * if we insert parts of A first, then before inserting parts of C,
 * B must have already been completed.
 *
 * Hence if b(C) = b(B) and C > B,
 * then composition of C must at least start from 2*B elements.
 *
 * If A < B, then starting from B is definitely better.
 *
 * This algorithm can be reduced to:
 * One by one compose the elements, and try starting from each elements.
 * And finally select the maximum of the number of atoms,
 * the minimum being the length of the array obviously.
 *
 * Seems like same as the tutorial.
 */
#include <bits/stdc++.h>
static_assert (sizeof (int) * CHAR_BIT >= 32);
typedef long long llong;
using namespace std;
#define FOR2(i, n) FOR3 (i, 0, n)
#define FOR3(i, p, q) for (int i = p; i < q; ++i)
#define DUMP(x) (string(#x) + ": " + to_string(x))

int main(int argc, char *argv[])
{
  int t;
  cin >> t;
  while (t--)
    {
      int n, k;
      cin >> n >> k;
      vector<int> a(n, 0);
      FOR2 (i, n) cin >> a[i];
      vector<int> insert_after_next(n, 0),
	insert_after_prior(n, 0),
	base(n, 0),
	multi(n, 0);
      FOR2 (i, n) {
	base[i] = a[i];
	while (base[i] % 2 == 0)
	  base[i] = base[i] / 2;
	multi[i] = a[i] / base[i];
      }
      FOR3 (i, 0, n - 1) {
	insert_after_next[i] =
	  (a[i] > a[i + 1] && base[i] == base[i + 1]) ?
	  multi[i] - 2 * multi[i + 1] + 1:
	  multi[i];
      }
      FOR3 (i, 1, n) {
	insert_after_prior[i] = 
	  (a[i] > a[i - 1] && base[i] == base[i - 1]) ?
	  multi[i] - 2 * multi[i - 1] + 1:
	  multi[i];
      }
      
      llong cur = 0;
      cur += multi[0];
      FOR3 (i, 1, n) cur += insert_after_prior[i];
      llong curmax = cur;
      FOR3 (i, 1, n) {
	cur -= multi[i - 1];
	cur += insert_after_next[i - 1];
	cur -= insert_after_prior[i];
	cur += multi[i];
	curmax = max(curmax, cur);
      }
      cout << (n <= k && k <= curmax ? "YES" : "NO") << '\n';
    }
  return 0;
}
