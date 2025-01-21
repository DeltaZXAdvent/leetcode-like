import java.util.*;
import java.util.stream.*;
/**
 * <a href="https://codeforces.com/contest/2055/problem/C">
 * https://codeforces.com/contest/2055/problem/C </a>
 *
 * <p> (n + m) equations and (n + m - 1) variables.
 * It can be proven that the equations are not related,
 * by walking the path. Every step guarantees a restoration.
 * Assume the sums to be zero.
 *
 * <p> Time limit exceeded... But some people passed using Java...
 *
 * <p> Maybe there is a way to use smaller integer types for a
 * (use a better sum value), but let's not bother it...
 */
public class TheTrail {
    public static void restoreAltitudesAndPrint (int n, int m, String s, long a[][]) {
	int i = 0, j = 0;
	for (int k = 0; k < s.length (); ++k) {
	    switch (s.charAt (k)) {
	    case 'D':
		a[i][j] = -Arrays.stream (a[i]).sum ();
		printArray (a[i]);
		++i;
		break;
	    case 'R':
		a[i][j] = -columnStream (a, j).sum ();
		++j;
		break;
	    }
	}
	a[i][j] = -Arrays.stream (a[i]).sum ();
	printArray (a[i]);
    }
    private static void printArray (long a[]) {
	int j = 0;
	while (true) {
	    System.out.print (a[j]);
	    if (++j == a.length) break;
	    System.out.print (" ");
	}
	System.out.println ();
    }
    private static LongStream columnStream (long a[][], int j) {
	return Arrays.stream (a).mapToLong (row -> row[j]);
    }
    public static void main (String[] args) {
	Scanner scanner = new Scanner (System.in);
	int t = scanner.nextInt ();
	while (t-- > 0) {
	    int n = scanner.nextInt ();
	    int m = scanner.nextInt ();
	    String s = scanner.next ();
	    long a[][] = new long[n][m];
	    for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
		    a[i][j] = scanner.nextLong ();
	    restoreAltitudesAndPrint (n, m, s, a);
	}
    }
}
