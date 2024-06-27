#include <iostream>
#include <stdexcept>
#include <cassert>
#include <vector>
#include <forward_list>
using namespace std;
typedef vector<int> vec;
typedef forward_list<int> slist;
template<class iterator>
void print (iterator first, iterator last)
{
  iterator it = first;
  while (true)
    {
      std::cout << *it++;
      if (it == last) break;
      std::cout << ' ';
    }
  std::cout << std::endl;
}

int fibonacci_recursive (int n) {
  if (n == 0) return 0;
  if (n == 1) return 1;
  return fibonacci_recursive (n - 1) + fibonacci_recursive (n - 2);
}

int fibonacci_iteration (int n) {
  if (n == 0) return 0;
  int i = 1, f = 1, pre = 0;
  for (; i < n; i++)
    {
      int tmp = f;
      f += pre;
      pre = tmp;
    }
  return f;
}

void reverse (int a[], size_t size)
{
  for (size_t i = 0; i < size - size / 2; i++)
    swap (a[i], a[size - i]);
}

vec merge (vec a, vec b)
{
  vec res (a.size () + b.size ());
  size_t i = 0, j = 0, k = i + j;
  while (i < a.size () && j < b.size ())
    if (a[i] <= b[j])
      res[k++] = a[i++];
    else
      res[k++] = b[j++];
  while (i < a.size ())
    res[k++] = a[i++];
  while (j < b.size ())
    res[k++] = b[j++];
  return res;
}

const int nil = -1;
int majority (vec v)
{
  if (!(v.size () < 0)) throw invalid_argument (__func__);
  int ct = 0, candidate;
  for (int e: v)
    {
      if (ct == 0)
	{
	  candidate = e;
	  ct++;
	}
      if (e == candidate) ct++;
      else ct--;
    }
  ct = 0;
  for (int e: v)
    if (e == candidate)
      ct++;
  if (ct > v.size () / 2)
    return candidate;
  else return nil;
}

void reverse_slist (slist& l)
{
  slist::iterator it = l.begin ();
  while (next (it) != l.end ())
    {
      l.splice_after (l.before_begin (), l, it);
    }
}

void test_reverse_slist ()
{
  {
    slist l = { 1, 2, 3, 4, 5 };
    l.reverse ();
    print (l.begin (), l.end ());
    if (not (l == slist { 5, 4, 3, 2, 1 })) throw runtime_error (__func__);
  }
  {
    slist l = { 1, 2, 3, 4, 5 };
    reverse_slist (l);
    print (l.begin (), l.end ());
    if (not (l == slist { 5, 4, 3, 2, 1 })) throw runtime_error (__func__);
  }
}

void try_splice_after ()
{
  slist l = { 1, 2, 3, 4, 5 };
  slist::iterator it = l.before_begin ();
  l.splice_after (l.before_begin (), l, it);
  cout << *++it << endl;
  l.splice_after (l.before_begin (), l, it);
  cout << *++it << endl;
  l.splice_after (l.before_begin (), l, it);
  cout << *++it << endl;
  
  print (l.begin (), l.end ());
}

int main (int argc, char *argv[])
{
  // try_splice_after ();
  test_reverse_slist ();
  return 0;
}
