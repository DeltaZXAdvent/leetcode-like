#include <cassert>
#include <cstdio>
#define MAX_SIZE 64
#define print_int(i) { printf ("%d ", i); fflush (stdout); }
#define prn() printf ("\n")

typedef struct {
  int SqBiTNodes[MAX_SIZE];
  int ElemNum;
} SqBiTree;

int lchild (int i) { return 2 * i + 1; }
int rchild (int i) { return 2 * i + 2; }
int parent (int i) { return (i - 1) / 2; }
bool is_lchild (int i) { return i % 2 == 1; }
bool valid (SqBiTree& tr, int i) {
  return 0 <= i && i < tr.ElemNum && tr.SqBiTNodes[i] != -1;
}

bool tree_is_bst (SqBiTree& tr)
{
  int i = 0, m = 0;
  if (tr.ElemNum == 0) return true;
  while (valid (tr, lchild (i)))
    i = lchild (i);
  while (true)
    {
      print_int (i);
      if (tr.SqBiTNodes[i] <= m)
	return false;
      m = tr.SqBiTNodes[i];
      if (valid (tr, rchild (i)))
	{
	  i = rchild (i);
	  while (valid (tr, lchild (i)))
	    i = lchild (i);
	}
      else
	{
	  while (!is_lchild (i))
	    {
	      if (i == 0) return true;
	      i = parent (i);
	    }
	  i = parent (i);
	}
    }
  return true;
}

void test_tree_is_bst ()
{
  SqBiTree tl = { { 40, 25, 60, -1, 30, -1, 80, -1, -1, 27 }, 10 },
    tr = { { 40, 50, 60, -1, 30, -1, -1, -1, -1, -1, 35 }, 11 };
  assert (tl.ElemNum == 10);
  assert (tr.ElemNum == 11);
  assert (tree_is_bst (tl)
	  && !tree_is_bst (tr));
  prn ();
}

int main (int argc, char *argv[])
{
  test_tree_is_bst ();
  return 0;
} 
