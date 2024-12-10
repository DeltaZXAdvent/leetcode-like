/**
 * OK, it seems that the declarative version does no improvement and is even worse
 * but the version from /Introdution To Algorithms/ may be better
 *
 * for rand_vec (100000, 100000, 999999):
 * Start timer for task "qsort_textbook (foo.begin (), foo.end ())"? 
 * Cost time: 0.0216536
 * Start timer for task "qsort_declarative (bar.begin (), bar.end ())"? 
 * Cost time: 0.0709463 (C++ iterator efficiency sucks)
 * Start timer for task "qsort_ita <vector <int> > (var, 0, var.size () - 1)"? 
 * Cost time: 0.0290672
 *
 * wtf? Compiled with ~-O3~: rand_vec (900000, 100000, 999999)
 * Start timer for task "qsort_textbook (foo.begin (), foo.end ())"? 
 * Cost time: 0.0649892
 * Start timer for task "qsort_declarative (bar.begin (), bar.end ())"? 
 * Cost time: 0.0684815
 * Start timer for task "qsort_ita <vector <int> > (var, 0, var.size () - 1)"? 
 * Cost time: 0.0622234
 */

#include <iterator>
/**
 * Originally ElemType A[]
 */
template <class ElemTypeArray>
int Partition(ElemTypeArray A,int low,int high);

template <class ElemTypeArray>
void QuickSort(ElemTypeArray A,int low,int high){
  if(low<high){
    int pivotpos=Partition(A,low,high);
    QuickSort(A,low,pivotpos-1);
    QuickSort(A,pivotpos+1,high);
  }
}
template <class ElemTypeArray>
int Partition(ElemTypeArray A,int low,int high){
  auto pivot=A[low];
  while(low<high){
    while(low<high&&A[high]>=pivot) --high;
    A[low]=A[high];
    while(low<high&&A[low]<=pivot) ++low;
    A[high]=A[low];
  }
  A[low]=pivot;
  return low;
}

template <class iter>
void qsort_textbook (iter first, iter last)
{
  QuickSort (first, 0, last - first - 1);
}

template <class iter>
iter partition_declarative (iter first, iter last);

template <class iter>
void qsort_declarative (iter first, iter last)
{
  if (first != last)
    {
      auto pivot = partition_declarative (first, last);
      qsort_declarative (first, pivot);
      qsort_declarative (pivot + 1, last);
    }
}

template <class iter>
iter partition_declarative (iter first, iter last)
{
  // if (first == last) return 0;
  auto pivot = *first;

  auto start = first;
  auto last_reverse = std::reverse_iterator (last);
  while (start + 1 < last_reverse.base ())
    {
      for (; *last_reverse >= pivot && start + 1 < last_reverse.base (); ++last_reverse);
      *start = *last_reverse;
      for (; *start <= pivot && start + 1 < last_reverse.base (); ++start);
      *last_reverse = *start;
    }
  *start = pivot;
  return start;
}

template <class container>
typename container::difference_type
partition_ita (container& A,
	       typename container::difference_type p,
	       typename container::difference_type r)
{
  auto x = A[r];
  auto i = p - 1;
  for (auto j = p; j < r; ++j)
    if (A[j] <= x)
      {
	++i;
	std::swap (A[i], A[j]);
      }
  std::swap (A[i + 1], A[r]);
  return i + 1;
}

template <class container>
void qsort_ita (container& A,
	       typename container::difference_type p,
	       typename container::difference_type r)
{
  if (p < r)
    {
      auto q = partition_ita (A, p, r);
      qsort_ita (A, p, q - 1);
      qsort_ita (A, q + 1, r);
    }
}

