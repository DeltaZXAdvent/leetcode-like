import java.util.*;
/**
 * <a href="https://codeforces.com/contest/2064/problem/C">
 * https://codeforces.com/contest/2064/problem/C</a>
 *
 * NOTE you can just omit my first step and add extra coins later
 */
public class RemoveTheEnds {
    public static long maxNumOfCoins (int n, int[] a) {
	int firstTry = 0;
	long bestCoins = 0;
	for (; firstTry < n; ++firstTry) {
	    if (a[firstTry] > 0)
		bestCoins += a[firstTry];
	    else {
		for (int j = firstTry; j < n; ++j) {
		    if (a[j] < 0)
			bestCoins -= a[j];
		}
		break;
	    }
	}
	// System.err.print ("firstTry: ");
	// System.err.println (firstTry);
	// System.err.print ("bestCoins: ");
	// System.err.println (bestCoins);
	int i = firstTry;
	long coins = bestCoins;
	while (i < n) {
	    coins += a[i++];
	    bestCoins = Math.max (bestCoins, coins);
	}
	return bestCoins;
    }
    public static void main (String[] args) {
	Scanner s = new Scanner (System.in);
	int t = s.nextInt ();
	while (t-- > 0) {
	    int n = s.nextInt ();
	    int[] a = new int[n];
	    for (int i = 0; i < n; ++i) {
		a[i] = s.nextInt ();
	    }
	    System.out.println (maxNumOfCoins (n, a));
	}
    }
}
