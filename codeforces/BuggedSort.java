import java.util.*;
/**
 * <a href="https://codeforces.com/contest/2060/problem/G">
 * https://codeforces.com/contest/2060/problem/G</a>
 */
public class BuggedSort {
    public static boolean isBuggedSortable (int n, int[] a, int[] b) {
	
    }
    public static void main (String[] args) {
	Scanner s = new Scanner (System.in);
	int t = s.nextInt ();
	while (t-- > 0) {
	    int n = s.nextInt ();
	    int[] a = new int[n];
	    int[] b = new int[n];
	    System.out.println (isBuggedSortable (n, a, b) ? "YES" : "NO");
	}
    }
}
