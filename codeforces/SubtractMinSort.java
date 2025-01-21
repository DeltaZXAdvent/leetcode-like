import java.util.*;
/**
 * <a href="https://codeforces.com/contest/2060/problem/D">
 * https://codeforces.com/contest/2060/problem/D</a>
 */
public class SubtractMinSort {
    public static boolean subtractMinSortable (int n, int[] a) {
	for (int i = 0; i <= n - 2; ++i) {
	    if (a[i] <= a[i + 1]) {
		a[i + 1] -= a[i];
		a[i] = 0;
	    } else {
		return false;
	    }
	}
	return true;
    }
    public static void main (String[] args) {
	Scanner s = new Scanner (System.in);
	int t = s.nextInt ();
	while (t-- > 0) {
	    int n = s.nextInt ();
	    int[] a = new int[n];
	    for (int i = 0; i < n; ++i)
		a[i] = s.nextInt ();
	    System.out.println (subtractMinSortable (n, a) ? "YES" : "NO");
	}
    }
}
