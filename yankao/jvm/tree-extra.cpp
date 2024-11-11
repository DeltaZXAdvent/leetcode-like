#include <iostream>
#include <queue>
#include <memory>
#include <algorithm>
#include <cassert>
#include <utility>
#include <string>
#include <iterator>
#include <list>
#include <unistd.h>
#include <mutex>
using namespace std;

template <class type>
struct double_buffer
{
  queue<type> parents, children;
  void pop_parent () { parents.pop (); }
  void push_child (type value) { children.push (value); }
  void swap () { std::swap (parents, children); }
  type front_parent () { return parents.front (); }
  bool empty_parents () { return parents.empty (); }
  bool empty_children () { return children.empty (); }
  size_t size_children () { return children.size (); }
};

struct tree
{
  string name;
  shared_ptr<tree> lchild, _rchild;
  bool rchild_threaded;
  int weight;
  tree (string name, shared_ptr<tree> lchild, shared_ptr<tree> rchild)
  {
    this->name = name;
    this->lchild = lchild;
    this->_rchild = rchild;
    this->rchild_threaded = false;
  }
  tree (string name, int weight, shared_ptr<tree> lchild, shared_ptr<tree> rchild)
  {
    this->name = name;
    this->weight = weight;
    this->lchild = lchild;
    this->_rchild = rchild;
    this->rchild_threaded = false;
  }
  shared_ptr<tree> rchild ()
  {
    return rchild_threaded ? nullptr : _rchild;
  }
};

shared_ptr<tree> example_tree =
  make_shared<tree>
  (tree {"a", 1,
	 make_shared<tree>
	 (tree {"e", 2,
		make_shared<tree>
		(tree {"d", 3,
		       nullptr,
		       make_shared<tree>
		       (tree {"f", 4,
			      nullptr,
			      nullptr})}),
		make_shared<tree>
		(tree {"b", 5,
		       nullptr,
		       nullptr})}),
	 make_shared<tree>
	 (tree {"c", 6,
		nullptr,
		nullptr})});

size_t tree_width (shared_ptr<tree> root)
{
  size_t maxwidth = 0;
  double_buffer<shared_ptr<tree>> buffer;
  buffer.push_child (root);
  while (!buffer.empty_children ())
    {
      maxwidth = max (maxwidth, buffer.size_children ());
      buffer.swap ();
      while (!buffer.empty_parents ())
	{
	  shared_ptr<tree> tr = buffer.front_parent ();
	  buffer.pop_parent ();
	  if (tr->lchild != nullptr)
	    buffer.push_child (tr->lchild);
	  if (tr->rchild () != nullptr)
	    buffer.push_child (tr->rchild ());
	}
    }
  return maxwidth;
}

void test_tree_width ()
{
  assert (tree_width (example_tree) == 2);
}

shared_ptr<tree>
tree_link_leaves (shared_ptr<tree> root,
		  shared_ptr<tree> tail)
{
  if (root == nullptr) return tail;
  if (root->lchild == nullptr && root->rchild () == nullptr)
    {
      root->_rchild = tail;
      root->rchild_threaded = true;
      return root;
    }
  return tree_link_leaves (root->lchild,
			   tree_link_leaves (root->rchild (), tail));
}

struct tree_wpl_ret
{
  int wpl;
  int leaf_weight_sum;
};
tree_wpl_ret tree_wpl (shared_ptr<tree> root)
{
  if (!root) return { 0, 0 };
  if (!root->lchild && !root->rchild ())
    return { 0, root->weight };
  auto l = tree_wpl (root->lchild),
    r = tree_wpl (root->rchild ());
  return { .wpl = l.wpl + r.wpl + l.leaf_weight_sum + r.leaf_weight_sum,
	   .leaf_weight_sum = l.leaf_weight_sum + r.leaf_weight_sum };
}

void test_tree_wpl ()
{
  assert (tree_wpl (example_tree).wpl
	  == 3 * 4 + 2 * 5 + 1 * 6);
}

// make tree pointers become iterators for using standard library algorithm mismatch
mutex m;
struct leaf_list: shared_ptr<tree>
{
  leaf_list (): shared_ptr<tree>() { }
  leaf_list (shared_ptr<tree> ptr):
    shared_ptr<tree>(ptr) { }
  leaf_list& operator++()
  {
    m.lock ();
    cout << __func__ << ": "
	 << (*this)->rchild_threaded << ' '
	 << (*this)->name << endl;
    m.unlock ();
    if (!*this) return *this;	// for safety
    return *this = (*this)->rchild_threaded ? (*this)->_rchild : shared_ptr<tree>();
  }
};

void test_tree_link_leaves ()
{
  leaf_list head = tree_link_leaves (example_tree, nullptr);
  list<string> l {"f", "b", "c"};
  // see if the names of the trees are correspondent to those of the list
  assert (leaf_list () == leaf_list ());
  assert (l.end () == l.end ());
  auto res_pair = mismatch (head, leaf_list (),
			    l.begin (), l.end (),
			    [&] (tree& tr, string& s)
			    {
			      m.lock ();
			      // sleep (1);
			      cout << &tr << ' ' << &s << ' ' << tr.name << ' ' << s << endl;
			      m.unlock ();
			      return tr.name == s;
			    });
  assert (res_pair
	  == make_pair (leaf_list (), l.end ()));
  // cout << head->name << " " << (++head)->name << " " << (++++head)->name << endl;
  // cout << *l.begin () << " " << *++l.begin () << " " << *++++l.begin () << endl;
  // cout << (leaf_list () == leaf_list ()) << endl
  //      << (leaf_list () == ++++++head) << endl
  //      << (head == leaf_list ()) << endl;
  // cout << res_pair.first->name << ' ' << *res_pair.second << endl;
  // for_each (head, ++++++head, [] (tree& tr) { cout << tr.name << " "; });
}

string tree_to_infix_internal (shared_ptr<tree> root)
{
  if (!root) return "";
  if (!root->lchild && !root->rchild ())
    return root->name;
  return string ("(")
    .append (tree_to_infix_internal (root->lchild))
    .append (root->name)
    .append (tree_to_infix_internal (root->rchild ()))
    .append (")");
}

string tree_to_infix (shared_ptr<tree> root)
{
  string raw = tree_to_infix_internal (root);
  if (!root->lchild && !root->rchild ())
    return raw;
  else
    return raw.substr (1, raw.size () - 2);
}

void test_tree_to_infix ()
{
  shared_ptr<tree> tl =
    make_shared<tree>
    (tree ("*",
	   make_shared<tree>
	   (tree ("+",
		  make_shared<tree>
		  (tree
		   ("a",
		    nullptr,
		    nullptr)),
		  make_shared<tree>
		  (tree
		   ("b",
		    nullptr,
		    nullptr)))),
	   make_shared<tree>
	   (tree ("*",
		  make_shared<tree>
		  (tree
		   ("c",
		    nullptr,
		    nullptr)),
		  make_shared<tree>
		  (tree
		   ("-",
		    nullptr,
		    make_shared<tree>
		    (tree
		     ("d",
		      nullptr,
		      nullptr))))))));
  shared_ptr<tree> tr =
    make_shared<tree>
    (tree ("+",
	   make_shared<tree>
	   (tree ("*",
		  make_shared<tree>
		  (tree
		   ("a",
		    nullptr,
		    nullptr)),
		  make_shared<tree>
		  (tree
		   ("b",
		    nullptr,
		    nullptr)))),
	   make_shared<tree>
	   (tree ("-",
		  nullptr,
		  make_shared<tree>
		  (tree
		   ("-",
		    make_shared<tree>
		    (tree
		     ("c",
		      nullptr,
		      nullptr)),
		    make_shared<tree>
		    (tree
		     ("d",
		      nullptr,
		      nullptr))))))));
  cout << tree_to_infix (tl) << endl;
  assert (tree_to_infix (tl) == "(a+b)*(c*(-d))");
  cout << tree_to_infix (tr) << endl;
  assert (tree_to_infix (tr) == "(a*b)+(-(c-d))");
}

int main (int argc, char *argv[])
{
  test_tree_width ();
  test_tree_link_leaves ();
  test_tree_wpl ();
  test_tree_to_infix ();
  return 0;
}
