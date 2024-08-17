#include <iostream>
#include "timer.hpp"
using namespace std;
struct slist_node;
struct slist
{
  slist_node *next;
  slist (size_t l);
  ~slist ();
  // left mid
  slist *mid_floyd ();
  slist *mid ();
};
struct slist_node: slist
{
  long long data;
  slist_node (size_t l);
};

slist::slist (size_t l): next (nullptr)
{
  if (l == 0) return;
  this->next = new slist_node (l);
}
slist::~slist ()
{
  if (next != nullptr)
    delete next;
}
// left mid
slist *slist::mid_floyd ()
{
  slist *slow = this,
    *fast = this;
  while (true)
    {
      if (fast == nullptr) break;
      fast = fast->next;
      if (fast == nullptr) break;
      fast = fast->next;
      slow = slow->next;
    }
  return slow;
}
slist *slist::mid ()
{
  size_t len = 0;
  for (slist *p = this; p != nullptr; p = p->next)
    ++len;
  slist* q = this;
  for (size_t half_len = len / 2; half_len > 0; --half_len)
    q = q->next;
  return q;
}

slist_node::slist_node (size_t l): slist (l - 1)
{
}

int main (int argc, char *argv[])
{
  // nearly no difference
  slist l (50000);
  timer (cout << l.mid_floyd () << endl);
  timer (cout << l.mid () << endl);
  return 0;
}
