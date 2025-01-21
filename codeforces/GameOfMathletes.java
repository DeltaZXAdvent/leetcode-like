import java.util.*;
/**
 * <a href="https://codeforces.com/contest/2060/problem/C">
 * https://codeforces.com/contest/2060/problem/C</a>
 */
public class GameOfMathletes {
    private record Key (int v) {}
    private record Counts (int minor, int major) {}
    public static int scoreUsingMap (int n, int k, int[] x) {
	Map <Key, Counts> counter = new HashMap <> ();
	int counterMid = 0;
	for (int i = 0; i < n; ++i) {
	    if (2 * x[i] < k) {
		Key key = new Key (x[i]);
		Counts counts = counter.get (key);
		counts = Optional.ofNullable (counts).orElse (new Counts (0, 0));
		counts = new Counts (counts.minor + 1, counts.major);
		counter.put (key, counts);
	    } else if (2 * x[i] == k) {
		++counterMid;
	    } else if (2 * x[i] > k) {
		Key key = new Key (k - x[i]);
		Counts counts = counter.get (key);
		counts = Optional.ofNullable (counts).orElse (new Counts (0, 0));
		counts = new Counts (counts.minor, counts.major + 1);
		counter.put (key, counts);
	    } else {}
	}
	return counter
	    .values ().stream ()
	    .mapToInt (counts -> Math.min (counts.minor, counts.major))
	    .sum () + counterMid / 2;
    }
    public static int scoreUsingSort (int n, int k, int[] x) {
	Arrays.sort (x);
	int i = 0, j = n - 1;
	int score = 0;
	while (i < j) {
	    if (x[i] + x[j] < k) {
		++i;
	    } else if (x[i] + x[j] == k) {
		++i;
		--j;
		++score;
	    } else if (x[i] + x[j] > k) {
		--j;
	    } else {}
	}
	return score;
    }
    public static void main (String[] args) {
	Scanner s = new Scanner (System.in);
	int t = s.nextInt ();
	while (t-- > 0) {
	    int n = s.nextInt ();
	    int k = s.nextInt ();
	    int[] x = new int[n];
	    for (int i = 0; i < n; ++i) {
		x[i] = s.nextInt ();
	    }
	    System.out.println (scoreUsingSort (n, k, x));
	}
    }
}
