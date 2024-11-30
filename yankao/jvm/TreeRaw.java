import java.util.Stack;

public class TreeRaw {
    public String name;
    public TreeRaw lchild, rchild;
    public static final TreeRaw nullTree = new TreeRaw ("null", null, null);
    public TreeRaw (String name, TreeRaw lchild, TreeRaw rchild) {
	this.name = name;
	this.lchild = lchild;
	this.rchild = rchild;
    }
    enum ReturnAddress {
	BEGIN,
	L,
	R,
	POP
    }
    static class ReturnFrame{
	TreeRaw tree;
	ReturnAddress returnAddress;
	public ReturnFrame(TreeRaw tree, ReturnAddress returnAddress) {
	    this.tree = tree;
	    this.returnAddress = returnAddress;
	}
    }
    public void lrn_recursive () {
	if (this == nullTree)
	    return;
	lchild.lrn_recursive ();
	rchild.lrn_recursive ();
	System.out.println (name);
    }
    
    private void lrn_iteration_raw() throws Exception {
	Stack<ReturnFrame> stack = new Stack<>();
	stack.push (new ReturnFrame (this, ReturnAddress.BEGIN));
	while (!stack.empty ()) {
	    ReturnFrame returnFrame = stack.peek ();
	    // System.out.println (returnFrame.tree);
	    // System.out.println (returnFrame.returnAddress);
	    // System.out.println (returnFrame.tree.name);
	    // System.out.println (stack.size ());
	    // java.util.concurrent.TimeUnit.SECONDS.sleep(1);
	    if (returnFrame.tree == nullTree) {
		stack.pop ();
		continue;
	    }
	    switch (returnFrame.returnAddress) {
	    case ReturnAddress.BEGIN:
		// System.out.println ("begin");
		returnFrame.returnAddress = ReturnAddress.L;
		stack.push (new ReturnFrame (returnFrame.tree.lchild, ReturnAddress.BEGIN));
		continue;
	    case ReturnAddress.L:
		// System.out.println ("l");
		returnFrame.returnAddress = ReturnAddress.R;
		stack.push (new ReturnFrame (returnFrame.tree.rchild, ReturnAddress.BEGIN));
		continue;
	    case ReturnAddress.R:
		// System.out.println ("r");
		stack.pop ();
		System.out.println (returnFrame.tree.name);
		continue;
	    default:
		throw new Exception();
	    }
	}
    }

    private void lrn_iteration_raw_begin_removed() throws Exception {
	Stack<ReturnFrame> stack = new Stack<>();
	TreeRaw tree = this;
	while (true) {
	    if (tree != nullTree) {
		// System.out.println (tree);
		stack.push (new ReturnFrame (tree, ReturnAddress.L));
		tree = tree.lchild;
		continue;
	    }
	    if (stack.empty ()) break;
	    ReturnFrame returnFrame = stack.peek ();
	    // System.out.println (returnFrame.returnAddress);
	    switch (returnFrame.returnAddress) {
	    case ReturnAddress.L:
		returnFrame.returnAddress = ReturnAddress.R;
		tree = returnFrame.tree.rchild;
		continue;
	    case ReturnAddress.R:
		stack.pop ();
		System.out.println (returnFrame.tree.name);
		continue;
	    default:
		throw new Exception();
	    }
	}
    }
    
    public void lrn_iteration() throws Exception {
	Stack<TreeRaw> stack = new Stack<>();
	stack.push (this);
	ReturnAddress returnAddress = ReturnAddress.BEGIN;
	while (true) {
	    TreeRaw tree = stack.peek ();
	    switch (returnAddress) {
	    case ReturnAddress.BEGIN:
		if (tree.lchild != nullTree)
		    stack.push (tree.lchild);
		else returnAddress = ReturnAddress.L;
		continue;
	    case ReturnAddress.L:
		if (tree.rchild != nullTree) {
		    returnAddress = ReturnAddress.BEGIN;
		    stack.push (tree.rchild);
		} else returnAddress = ReturnAddress.R;
		continue;
	    case ReturnAddress.R:
		returnAddress = ReturnAddress.POP;
		System.out.println (tree.name);
		continue;
	    case ReturnAddress.POP:
		stack.pop ();
		if (stack.empty ()) return;
		else if (stack.peek ().lchild == tree) returnAddress = ReturnAddress.L;
		else if (stack.peek ().rchild == tree) returnAddress = ReturnAddress.R;
		else throw new Exception ();
		continue;
	    }
	}
    }

    // alternative:
    // use lnr/nlr iteration but push the depth of node onto stack
    public int height () throws Exception {
	Stack<TreeRaw> stack = new Stack<>();
	int maxdepth = 0;
	stack.push (this);
	if (stack.size () > maxdepth) maxdepth = stack.size ();
	ReturnAddress returnAddress = ReturnAddress.BEGIN;
	while (true) {
	    TreeRaw tree = stack.peek ();
	    switch (returnAddress) {
	    case ReturnAddress.BEGIN:
		if (tree.lchild != nullTree) {
		    stack.push (tree.lchild);
		    if (stack.size () > maxdepth) maxdepth = stack.size ();
		    continue;
		}
		returnAddress = ReturnAddress.L;
	    case ReturnAddress.L:
		if (tree.rchild != nullTree) {
		    returnAddress = ReturnAddress.BEGIN;
		    stack.push (tree.rchild);
		    if (stack.size () > maxdepth) maxdepth = stack.size ();
		    continue;
		}
		returnAddress = ReturnAddress.R;
	    case ReturnAddress.R:
		stack.pop ();
		if (stack.empty ()) {
		    return maxdepth;
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

    public static void main (String[] args) throws Exception {
	TreeRaw tree = new TreeRaw ("a",
			      new TreeRaw ("e",
					new TreeRaw ("d",
						  nullTree,
						  new TreeRaw ("f",
							    nullTree,
							    nullTree)),
					new TreeRaw ("b",
						  nullTree,
						  nullTree)),
			      new TreeRaw ("c",
					nullTree,
					nullTree));
	// nullTree.lrn_recursive ();
	System.out.println (nullTree == nullTree);
	tree.lrn_recursive ();
	tree.lrn_iteration_raw();
	System.out.println ("yes");

	tree.lrn_iteration_raw_begin_removed ();
	tree.lrn_iteration ();
	System.out.println ("yes");
	System.out.println (tree.height ());
    }
}
