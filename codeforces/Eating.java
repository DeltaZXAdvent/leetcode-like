import java.util.*;
/**
 * <a href="https://codeforces.com/contest/2064/problem/D">
 * https://codeforces.com/contest/2064/problem/D</a>
 *
 * TODO
 * Ouch, bitwise XOR can be optimized but I have no time for revision.
 * You don't have to XOR with every element for each query.
 * (Wait a minute, maybe not? I should have used C++?)
 */
public class Eating {
    public static int score (int n, int[] w, int x) {
	int until;
	for (until = n - 1; until >= 0; --until) {
	    if (w[until] > x)
		break;
	    x ^= w[until];
	}
	// System.err.print ("until: ");
	// System.err.println (until);
	return n - (until + 1);
    }
    public static int scoreOptimized (int n, int[] wOptimized, int x) {
	int[] w = wOptimized;
	
    }
    public static void main (String[] args) {
	Scanner s = new Scanner (System.in);
	int t = s.nextInt ();
	while (t-- > 0) {
	    int n = s.nextInt ();
	    int q = s.nextInt ();
	    int[] w = new int[n + 1];
	    for (int i = 0; i < n; ++i) {
		w[i] = s.nextInt ();
	    }
	    w[i] = 0;
	    while (true) {
		int x = s.nextInt ();
		System.out.print (score (n, w, x));
		if (--q <= 0)
		    break;
		System.out.print (" ");
	    }
	    System.out.println ();
	}
    }
}
