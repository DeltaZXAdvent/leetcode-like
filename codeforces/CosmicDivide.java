import java.util.*;
/**
 * <a href="https://codeforces.com/contest/2055/problem/F">
 * https://codeforces.com/contest/2055/problem/F</a>
 *
 * <p>Inquiry:
 * <br/> It's the same as dividing every row intervals into two,
 * the left ones and the right ones belonging to two partitions
 * respectively. (The left and right relation cannot vary otherwise
 * the partitioned polyominoes will not be self-connected.)
 *
 * <p>The two partitions must be also convex,
 * for which I have a not so rigorous proof.
 *
 * <p>There are supposedly two methods of thinking the problem:
 * margin-based and interval-based.
 *
 * TODO
 */
public class CosmicDivide {
    public static boolean canBePartitionedCongruently (int n, int[] l, int[] r) {
    }
    public static void main (String[] args) {
	Scanner s = new Scanner (System.in);
	int t = s.nextInt ();
	while (t-- > 0) {
	    int n = s.nextInt ();
	    int[] l = new int[n];
	    int[] r = new int[n];
	    for (int i = 0; i < n; ++i) {
		l[i] = s.nextInt ();
		r[i] = s.nextInt ();
	    }
	    System.out.println (canBePartitionedCongruently (n, l, r)
				? "YES" : "NO");
	}
    }
}
