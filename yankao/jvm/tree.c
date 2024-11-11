#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "tree.h"

enum return_addr {
  BEGIN, L, R
};
bool tree_is_ancestor_recursive (struct tree *tree, char *name) {
  if (tree == NULL) return false;
  bool left = tree_is_ancestor_recursive (tree->lchild, name);
  bool right = tree_is_ancestor_recursive (tree->rchild, name);
  bool mid = !strcmp (tree->name, name);
  if (left && right || left && mid || right && mid) {
    printf ("multiple occurrences of value! ");
    return true;
  }
  if (mid)
    return true;
  if (left || right) {
    printf ("%s ", tree->name);
    return true;
  }
  return false;
}

bool tree_print_ancestors (struct tree *tree, char *name) {
  struct stack stack;
  stack_init (&stack);
  stack_push (&stack, tree);
  enum return_addr addr = BEGIN;
  while (true) {
    struct tree *tree = stack.top->tree;
    switch (addr) {
    case BEGIN:
      if (!strcmp (tree->name, name)) {
	for (struct node *node = stack.top->next;
	     node != NULL;
	     node = node->next) {
	  printf ("%s ", node->tree->name);
	}
	return true;
      }
      if (tree->lchild != NULL) {
	stack_push (&stack, tree->lchild);
	continue;
      }
      addr = L;
    case L:
      if (tree->rchild != NULL) {
	addr = BEGIN;
	stack_push (&stack, tree->rchild);
	continue;
      }
      addr = R;
    case R:
      assert (stack_pop (&stack, NULL));
      if (stack_empty (&stack)) {
	return false;
      }
      else if (stack.top->tree->lchild == tree)
        addr = L;
      else if (stack.top->tree->rchild == tree)
	addr = R;
      else exit (1);
      continue;
    default:
      exit (1);
    }
  }
}

bool tree_is_ancestor_r (struct tree *tree, char *name) {
  if (tree == NULL) return false;
  if (tree_is_ancestor_r (tree->lchild, name)) {
    printf ("%s ", tree->name);
    return true;
  }
  if (tree_is_ancestor_r (tree->rchild, name)) {
    printf ("%s ", tree->name);
    return true;
  }
  if (!strcmp (tree->name, name)) {
    return true;
  }
  return false;
}

void test_tree () {
  struct tree *example_tree =
    tree_new ("a",
	      tree_new ("e",
			tree_new ("d",
				  NULL,
				  tree_new ("f",
					    NULL,
					    NULL)),
			tree_new ("b",
				  tree_new ("e",
					    NULL,
					    NULL),
				  NULL)),
	      tree_new ("c",
			NULL,
			NULL));

  assert (tree_print_ancestors (example_tree, "b"));
  printf ("\n");
  assert (tree_is_ancestor_recursive (example_tree, "b"));
  printf ("\n");
  assert (tree_is_ancestor_recursive (example_tree, "e"));
  printf ("\n");
  assert (!tree_is_ancestor_recursive (example_tree, "g"));
  printf ("\n");
  assert (tree_is_ancestor_r (example_tree, "f"));
  printf ("\n");
  
  tree_free (example_tree);
}

int main (int argc, char *arv[]) {
  test_tree ();
  /* printf ("yes\n"); */
  return 0;
}
