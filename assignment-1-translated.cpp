#include <iostream>
#include <stdexcept>
#include <vector>
#include <forward_list>
using namespace std;
#define run_test(test) ({ cout << #test << endl; (test_##test) (); })
typedef vector<int> vec;
typedef forward_list<int> slist;
template<class iterator>
ostream& print (ostream& os, iterator first, iterator last)
{
  iterator it = first;
  if (it != last)
    while (true)
      {
	os << *it++;
	if (it == last) break;
	os << ' ';
      }
  os << endl;
  return os;
}
template<class container>
ostream& print (ostream& os, container v)
{
  return print (os, v.begin (), v.end ());
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
    print(cout, l);
    if (not (l == slist { 5, 4, 3, 2, 1 }))
      throw runtime_error (__func__);
  }
  {
    slist l = { 1, 2, 3, 4, 5 };
    reverse_slist (l);
    print (cout, l);
    if (not (l == slist { 5, 4, 3, 2, 1 }))
      throw runtime_error (__func__);
  }
}

bool slist_circular_p (slist& l)
{
  slist::iterator slow = l.before_begin (),
    fast = l.before_begin ();
  do
    {
      ++fast;
      if (fast == l.end ()) return false;
      ++fast;
      if (fast == l.end ()) return false;
      ++slow;
    }
  while (slow != fast);
  return true;
}

slist& slist_merge (slist& l1, slist& l2)
{
  slist::iterator it1 = l1.before_begin (),
    it2 = l2.before_begin ();
  print (cout, l1);
  print (cout, l2);
  while (next (it1) != l1.end () && next (it2) != l2.end ())
    {
      if (*next (it1) <= *next (it2))
	++it1;
      else
	{
	  l1.splice_after (it1, l2, it2);
	  ++it1;
	}
    }
  while (next (it1) != l1.end ())
    ++it1;
  while (next (it2) != l2.end ())
    {
      l1.splice_after (it1, l2, it2);
      ++it1;
    }
  return l1;
}

void test_slist_merge ()
{
  {
    slist list1 = {1, 3, 3, 5, 9},
      list2 = {2,3,4,4,7,8};
    print (cout, list1);
    print (cout, list2);
    list1.merge (list2);
    print (cout, list1);
    print (cout, list2);
  }
  {
    slist list1 = {1, 3, 3, 5, 9},
      list2 = {2,3,4,4,7,8};
    print (cout, list1);
    print (cout, list2);
    slist_merge (list1, list2);
    print (cout, list1);
    print (cout, list2);
  }
}

slist::iterator slist_last (slist& l, size_t k)
{
  slist::iterator slow = l.before_begin (),
    fast = l.before_begin ();
  do
    {
      ++fast;
      k--;
      if (fast == l.end ()) return l.end ();
    }
  while (k > 0);
  do
    {
      ++slow;
      ++fast;
    }
  while (fast != l.end ());
  return slow;
}

void test_slist_last ()
{
  slist l { 1, 2, 3, 4, 5, 6, 7 };
  cout << *slist_last (l, 4) << endl;
}

void slist_sort (slist& l)
{
  // A) 使用归并排序，
  // 只需要找到中间的iterator，花费线性复杂度时间。
  // 故时间复杂度不变。但因为合并链表的空间复杂度为O(1)，
  // 所以总空间复杂度为O(1)。
  
  // B) 使用快速排序，
  // 单链表中无法访问前继结点，
  // 故需要前继节点需要先遍历一次链表。（可以采用指针数组）

  // C) 使用堆排序，
  // 堆排序对堆的基本操作中，父结点在up-heap操作中需要被访问，
  // 子结点在heapify操作中需要被访问，所以需要先遍历一次链表以建立可以访问父结点和子结点的树。

  // D) 参考语言标准实现，例如C++中
  // std::sort需要RandomAccessIterator，故前继与后继都需要O(1)访问时间；
  // std::qsort则需要排序对象是数组。
}

int main (int argc, char *argv[])
{
  run_test (reverse_slist);
  run_test (slist_merge);
  run_test (slist_last);
  return 0;
}
