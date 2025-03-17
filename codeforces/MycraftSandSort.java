import java.util.*;
/**
 * <a href="https://codeforces.com/contest/2064/problem/E">
 * https://codeforces.com/contest/2064/problem/E</a>
 */
public class MycraftSandSort {
    public static void numOfPairs (int n, int[] p, int[] c) {
	
    }
    public static void main (String[] args) {
	Scanner s = new Scanner (System.in);
	int t = s.nextInt ();
	while (t-- > 0) {
	    int n = s.nextInt ();
	    int[] p = new int[n];
	    for (int i = 0; i < n; ++i) {
		p = s.nextInt ();
	    }
	    int[] c = new int[n];
	    for (int i = 0; i < n; ++i) {
		c = s.nextInt ();
	    }
	    System.out.println (numOfPairs (n, p, c));
	}
    }
}
