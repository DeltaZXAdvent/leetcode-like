import java.util.Stack;

public class Tree {
    public String name;
    public Tree lchild, rchild;
    public static final Tree exampleTree =
	new Tree ("a",
		  new Tree ("e",
			    new Tree ("d",
				      null,
				      new Tree ("f",
						null,
						null)),
			    new Tree ("b",
				      null,
				      null)),
		  new Tree ("c",
			    null,
			    null));

    public Tree (String name, Tree lchild, Tree rchild) {
	this.name = name;
	this.lchild = lchild;
	this.rchild = rchild;
    }
    enum ReturnAddress {
	BEGIN,
	L,
	R,
    }    
    public static void lrn_recursive (Tree tree) {
	if (tree == null)
	    return;
	lrn_recursive (tree.lchild);
	lrn_recursive (tree.rchild);
	System.out.print (tree.name + " ");
    }

    public Tree lrn_iteration () throws Exception {
	Stack<Tree> stack = new Stack<>();
	stack.push (this);
	ReturnAddress returnAddress = ReturnAddress.BEGIN;
	while (true) {
	    Tree tree = stack.peek ();
	    switch (returnAddress) {
	    case ReturnAddress.BEGIN:
		if (tree.lchild != null) {
		    stack.push (tree.lchild);
		    continue;
		}
		returnAddress = ReturnAddress.L;
	    case ReturnAddress.L:
		if (tree.rchild != null) {
		    returnAddress = ReturnAddress.BEGIN;
		    stack.push (tree.rchild);
		    continue;
		}
		returnAddress = ReturnAddress.R;
	    case ReturnAddress.R:
		System.out.print (tree.name + " ");
		stack.pop ();
		if (stack.empty ()) {
		    System.out.println ();
		    return this;
		}
		else if (stack.peek ().lchild == tree)
		    returnAddress = ReturnAddress.L;
		else if (stack.peek ().rchild == tree)
		    returnAddress = ReturnAddress.R;
		else throw new Exception ();
		continue;
	    default:
		throw new Exception ();
	    }
	}
    }

    public static Tree swap (Tree tree) {
	if (tree == null) return tree;
	Tree tmp = tree.rchild;
	tree.rchild = tree.lchild;
	tree.lchild = tmp;
	swap (tree.lchild);
	swap (tree.rchild);
	return tree;
    }

    public Tree nth (int k) throws Exception {
	Stack<Tree> stack = new Stack<>();
	stack.push (this);
	ReturnAddress returnAddress = ReturnAddress.BEGIN;
	int current = 0;
	while (true) {
	    Tree tree = stack.peek ();
	    switch (returnAddress) {
	    case ReturnAddress.BEGIN:
		if (++current == k) return tree;
		if (tree.lchild != null) {
		    stack.push (tree.lchild);
		    continue;
		}
		returnAddress = ReturnAddress.L;
	    case ReturnAddress.L:
		if (tree.rchild != null) {
		    returnAddress = ReturnAddress.BEGIN;
		    stack.pop ();
		    stack.push (tree.rchild);
		    continue;
		}
		stack.pop ();
		if (stack.empty ()) {
		    System.out.println ();
		    return null;
		}
		returnAddress = ReturnAddress.L;
		continue;
	    default:
		throw new Exception ();
	    }
	}

    }

    public static void main (String[] args) throws Exception {
	lrn_recursive (exampleTree);
	exampleTree.lrn_iteration ();
	System.out.println (exampleTree.nth (5).name);
	swap (exampleTree).lrn_iteration ();
	System.out.println (exampleTree.nth (7).name);
    }
}
