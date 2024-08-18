#include <iostream>
#include <vector>
#include <numeric>
#include <chrono>
#include <string>
using namespace std;
typedef vector<long double> vec;
typedef vec::value_type val;
void reverse (vec::iterator begin, vec::iterator end);
void swap_multiple (vec::iterator begin, vec::iterator mid, vec::iterator end)
{
  reverse (begin, end);
  reverse (begin, mid);
  reverse (mid, end);
}
void reverse (vec::iterator begin, vec::iterator end)
{
  while (begin < end)
    {
      swap (*begin, *end);
      ++begin;
      --end;
    }
}

int gcd (int a, int b)
{
  if (b == 0)
    return a;
  return gcd (b, a - a / b * b);
}

// Why is swap_multiple faster? The transfer in this version is apparently less.
// Maybe because of caching?
void swap_multiple_direct (vec::iterator begin, vec::iterator mid, vec::iterator end)
{
  int m = mid - begin,
    n = end - mid,
    k = gcd (m, n);
  for (vec::iterator start = begin; start != begin + k; ++start)
    {
      vec::iterator cur = start;
      val tmp1 = *cur,
	tmp2;
      bool use_tmp1 = true;
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

ostream &operator<< (ostream &os, vec v)
{
  for (int ve: v)
    cout << ve << ' ';
  cout << endl;
  return os;
}

chrono::time_point<chrono::system_clock> tp;
string task;
void timer_start (string task_name)
{
  task = task_name;
  cout << "Start timer for task \"" << task
       << "\"?" << endl;
  cin.ignore (numeric_limits<int>::max (), '\n');
  tp = chrono::system_clock ().now ();
}
void timer_stop ()
{
  cout << "Time spent: "
       << chrono::duration_cast<chrono::duration<double>> (chrono::system_clock ().now () - tp).count ()
       << endl;
}
#define timer(exp) ({				\
      timer_start (string (#exp));		\
      exp;					\
      timer_stop ();				\
    })
void wait ()
{
  cin.ignore (numeric_limits<int>::max (), '\n');
}

int main (int argc, char *argv[])
{
  int m = stoi (argv[1]),
    n = stoi (argv[2]);
  vec v (m + n);
  iota (v.begin (), v.end (), 1);
  timer (swap_multiple (v.begin (), v.begin () + m, v.end ()));
  // wait ();
  // cout << v << endl;
  timer (swap_multiple_direct (v.begin (), v.begin () + m, v.end ()));
  // wait ();
  // cout << v << endl;
  timer (gcd (m, n));
  return 0;
}

// TODO
// 这个是因为想纯使用C++库，
// 我对优化和汇编都不了解，但我想的是第二种算法的分支也很简单，不应该需要跳转指令吧，只需要把两条分支都条件执行一遍；
// 第二种算法是内存访问少一半，把每个元素移到对应位置，然后把相应位置元素再移走。
