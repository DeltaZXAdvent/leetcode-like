import java.util.*;
/**
 * <a href="https://codeforces.com/contest/2060/problem/A">
 * https://codeforces.com/contest/2060/problem/A</a>
 */
public class Fibonacciness {
    public static void addOne (Map <Integer, Integer> counts, int i) {
	Integer key = Integer.valueOf (i);
	Integer ct = counts.get (key);
	int new_ct = ct == null ? 0 : ct.intValue ();
	ct = Integer.valueOf (new_ct + 1);
	counts.put (key, ct);
    }
    public static void main (String[] args) {
	Scanner s = new Scanner (System.in);
	int t = s.nextInt ();
	while (t-- > 0) {
	    int a1 = s.nextInt ();
	    int a2 = s.nextInt ();
	    int a4 = s.nextInt ();
	    int a5 = s.nextInt ();
	    int a3;
	    Map <Integer, Integer> counts = new HashMap <Integer, Integer> ();
	    a3 = a1 + a2;
	    addOne (counts, a3);
	    a3 = a4 - a2;
	    addOne (counts, a3);
	    a3 = a5 - a4;
	    addOne (counts, a3);
	    System.out.println (Collections.max (counts.values ()));
	}
    }
}
