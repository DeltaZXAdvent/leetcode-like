import java.util.*;
/**
 * <a href="https://codeforces.com/contest/2055/problem/A">
 * https://codeforces.com/contest/2055/problem/A </a>
 */
public class TwoFrogs {
    public static boolean winnable (int n, int a, int b) {
	return (b - a) % 2 == 0;
    }
    public static void main (String[] args) {
	Scanner s = new Scanner (System.in);
	int t = s.nextInt ();
	while (t-- > 0) {
	    int n = s.nextInt (),
		a = s.nextInt (),
		b = s.nextInt ();
	    System.out.println (winnable (n, a, b) ? "YES" : "NO");
	}
    }
}
