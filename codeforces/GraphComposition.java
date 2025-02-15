import java.util.*;
/**
 * <a href="https://codeforces.com/contest/2060/problem/E">
 * https://codeforces.com/contest/2060/problem/E</a>
 *
 * <p>Solution: just use disjoint sets, remove illegal
 * edges and add bridging edges at the end.
 */
public class GraphComposition {
    public static void main (String[] args) {
	Scanner s = new Scanner (System.in);
	int t = s.nextInt ();
	while (t-- > 0) {
	    int n = s.nextInt ();
	    int m1 = s.nextInt ();
	    int m2 = s.nextInt ();

	    // If funtionally, use a buffered stream instead.
	    int fu[] = new int[m1];
	    int fv[] = new int[m1];
	    for (int i = 0; i < m1; ++i) {
		fu[i] = s.nextInt ();
		fv[i] = s.nextInt ();
	    }
	    
	    DisjointSetForest gcomponents = new DisjointSetForest ();
	    DisjointSetForest.Element[] gelements = new DisjointSetForest.Element[n];
	    for (int k = 0; k < n; ++k) {
		gelements[k] = gcomponents.makeSet (k + 1);
	    }
	    for (int j = 0; j < m2; ++j) {
		int gu = s.nextInt ();
		int gv = s.nextInt ();
		gcomponents.union (gelements[gu - 1], gelements[gv - 1]);
	    }
	    
	    DisjointSetForest fcomponents = new DisjointSetForest ();
	    DisjointSetForest.Element[] felements = new DisjointSetForest.Element[n];
	    for (int k = 0; k < n; ++k) {
		felements[k] = fcomponents.makeSet (k + 1);
	    }
	    int removes = 0, adds;
	    for (int i = 0; i < m1; ++i) {
		if (gcomponents.findSet (gelements[fu[i] - 1]) != gcomponents.findSet (gelements[fv[i] - 1]))
		    ++removes;
		else fcomponents.union (felements[fu[i] - 1], felements[fv[i] - 1]);
	    }
	    adds = fcomponents.numberOfSets - gcomponents.numberOfSets;
	    int numberOfOperations = removes + adds;
	    // System.out.println (removes);
	    // System.out.println (adds);
	    // System.out.print (" ");
	    System.out.println (numberOfOperations);
	    // System.out.print ("!!!");
	    // System.out.println (fcomponents.numberOfSets);
	    // System.out.print ("!!!");
	    // System.out.println (gcomponents.numberOfSets);
	}
    }
}
/**
 * See <i>Introduction to Algorithms</i>.
 */
class DisjointSetForest {
    public int numberOfSets;
    public class Element {
	int object;
	Element p;
	int rank;
	public Element (int object) {
	    this.object = object;
	    this.p = this;
	    this.rank = 0;
	}
    }
    public DisjointSetForest () {
	numberOfSets = 0;
    }
    public Element makeSet (int object) {
	Element element = new Element (object);
	++numberOfSets;
	return element;
    }
    public void union (Element x, Element y) {
	Element xset = findSet (x);
	Element yset = findSet (y);
	if (xset != yset) {
	    link (xset, yset);
	}
    }
    private void link (Element x, Element y) {
	if (x.rank > y.rank)
	    y.p = x;
	else {
	    x.p = y;
	    if (x.rank == y.rank)
		y.rank += 1;
	}
	--numberOfSets;
    }
    /**
     * Find representative.
     */
    public Element findSet (Element x) {
	if (x != x.p)
	    x.p = findSet (x.p);
	return x.p;
    }
}
