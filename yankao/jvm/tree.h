#include <stdlib.h>

struct tree {
  char *name;
  struct tree *lchild, *rchild;
};
struct node {
  struct tree *tree;
  struct node *next;
};
struct stack {
  struct node *top;
};
static void stack_init (struct stack *stack) {
  stack->top = NULL;
}
static void stack_push (struct stack *stack, struct tree *tree) {
  struct node *push = malloc (sizeof (struct node));
  push->tree = tree;
  push->next = stack->top;
  stack->top = push;
}
static bool stack_pop (struct stack *stack, struct tree **out) {
  if (stack->top == NULL) return false;
  if (out != NULL)
    *out = stack->top->tree;
  struct node *tmp = stack->top;
  stack->top = stack->top->next;
  free (tmp);
  return true;
}
static bool stack_empty (struct stack *stack) {
  return stack->top == NULL;
}

static struct tree *
tree_new (char *name,
	  struct tree *lchild,
	  struct tree *rchild)
{
  struct tree *tree = malloc (sizeof (struct tree));
  tree->lchild = lchild;
  tree->rchild = rchild;
  tree->name = name;
  return tree;
}

static void
tree_free (struct tree *tree)
{
  if (tree == NULL) return;
  tree_free (tree->lchild);
  tree_free (tree->rchild);
  free (tree);
}
