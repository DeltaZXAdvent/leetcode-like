import java.util.*;
/**
 * <a href="https://codeforces.com/contest/2066/problem/B">
 * https://codeforces.com/contest/2066/problem/B</a>
 */
public class WhiteMagic {
    public static void maxLenOfMagicalSubseq (int n, int[] a) {
	
    }
    public static void main (String[] args) {
	Scanner s = new Scanner (System.in);
	int t = s.nextInt ();
	while (t-- > 0) {
	    int n = s.nextInt ();
	    int[] a = new int [n];
	    for (int i = 0; i < n; ++i) {
		a[i] = s.nextInt ();
	    }
	    System.out.println (maxLenOfMagicalSubseq (n, a));
	}
    }
}
