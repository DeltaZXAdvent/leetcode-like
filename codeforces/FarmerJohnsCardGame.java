import java.util.*;
/**
 * <a href="https://codeforces.com/contest/2060/problem/B">
 * https://codeforces.com/contest/2060/problem/B</a>
 */
public class FarmerJohnsCardGame {
    public static int[] winnablePermutation (int n, int m, int[][] cards) {
	int[] permutation = new int[n];
	for (int i = 0; i < n; ++i) {
	    permutation[cards[i][0] % n] = i;
	    for (int j = 1; j < m; ++j) {
		if ((cards[i][j] - cards[i][0]) % n != 0)
		    return null;
	    }
	}
	return permutation;
    }
    public static void main (String[] args) {
	Scanner s = new Scanner (System.in);
	int t = s.nextInt ();
	while (t-- > 0) {
	    int n = s.nextInt ();
	    int m = s.nextInt ();
	    int[][] cards = new int[n][m];
	    for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
		    cards[i][j] = s.nextInt ();
		}
	    }
	    int[] permutation = winnablePermutation (n, m, cards);
	    if (permutation == null)
		System.out.println (-1);
	    else {
		int i = 0;
		while (true) {
		    System.out.print (permutation[i] + 1);
		    if (++i == n) break;
		    System.out.print (" ");
		}
		System.out.println ();
	    }
	}
    }
}
