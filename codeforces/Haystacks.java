import java.util.*;
/**
 * <a href="https://codeforces.com/contest/2055/problem/E">
 * https://codeforces.com/contest/2055/problem/E</a>
 *
 * <p>If the sequence of the haystacks to be emptied is determined,
 * we can come up with an optimal strategy: If there are haystacks
 * ever emptied, move haybales from current haystack to be emptied
 * onto it, if there is space; otherwise move them onto the last
 * haystack to be emptied.
 *
 * TODO
 */
public class Haystacks {
    public static int haystacks (int n, int[] a, int[] b) {
    }
    public static void main (String[] args) {
	Scanner s = new Scanner (System.in);
	int t = s.nextInt ();
	while (t-- > 0) {
	    int n = s.nextInt ();
	    int[] a = new int[n];
	    int[] b = new int[n];
	    for (int i = 0; i < n; ++i) {
		a[i] = s.nextInt ();
		b[i] = s.nextInt ();
	    }
	    System.out.println (haystacks (n, a, b));
	}
    }
}
