import java.util.*;
/**
 * <a href="https://codeforces.com/contest/2055/problem/B">
 * https://codeforces.com/contest/2055/problem/B </a>
 *
 * <p> There can be at most one insufficient material.
 */
public class Crafting {
    public static boolean canBeCrafted (int n, int[] a, int[] b) {
	int minSurplus = Integer.MAX_VALUE;
	int maxShortage = 0;
	for (int i = 0; i < n; ++i) {
	    int surplus = a[i] - b[i];
	    if (surplus >= 0)
		minSurplus = Math.min (minSurplus, surplus);
	    else {
		if (maxShortage == 0)
		    maxShortage = -surplus;
		else return false;
	    }
	}
	return maxShortage <= minSurplus;
    }
    public static void main (String[] args) {
	Scanner s = new Scanner (System.in);
	int t = s.nextInt ();
	while (t-- > 0) {
	    int n = s.nextInt ();
	    int[] a = new int[n];
	    for (int i = 0; i < n; ++i)
		a[i] = s.nextInt ();
	    int[] b = new int[n];
	    for (int i = 0; i < n; ++i)
		b[i] = s.nextInt ();
	    System.out.println (canBeCrafted (n, a, b) ? "YES" : "NO");
	}
    }
}
