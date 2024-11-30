#include <iostream>
#include <memory>
#include <cassert>
#include <algorithm>

using namespace std;

struct forest
{
  string name;
  shared_ptr<forest> child, sibling;
};

shared_ptr<forest> test_forest =
  make_shared<forest>
  (forest {"A",
	   make_shared<forest>
	   (forest {"B",
		    make_shared<forest>
		    (forest {"D", nullptr, nullptr}),
		    make_shared<forest>
		    (forest {"E",
			     make_shared<forest>
			     (forest {"H", nullptr, nullptr}),
			     nullptr})}),
	   make_shared<forest>
	   (forest {"C",
		    make_shared<forest>
		    (forest {"F",
			     make_shared<forest>
			     (forest {"I",
				      nullptr,
				      make_shared<forest>
				      (forest {"M", nullptr, nullptr})}),
			     nullptr}),
		    make_shared<forest>
		    (forest {"G",
			     nullptr,
			     make_shared<forest>
			     (forest {"J",
				      make_shared<forest>
				      (forest {"K",
					       nullptr,
					       make_shared<forest>
					       (forest {"L", nullptr, nullptr})}),
				      nullptr})})})});

int forest_leaf_count (shared_ptr<forest> fr)
{
  if (!fr) return 0;
  if (!fr->child) return 1 + forest_leaf_count (fr->sibling);
  return forest_leaf_count (fr->child) + forest_leaf_count (fr->sibling);
}

void test_forest_leaf_count ()
{
  assert (forest_leaf_count (test_forest) == 7);
}

int forest_depth (shared_ptr<forest> fr)
{
  if (!fr) return 0;
  return max (forest_depth (fr->child) + 1,
	      forest_depth (fr->sibling));
}

void test_forest_depth ()
{
  assert (forest_depth (test_forest) == 3);
}

int main (int argc, char *argv[])
{
  test_forest_leaf_count ();
  test_forest_depth ();
  return 0;
}
