import java.util.*;
/**
 * <a href="https://codeforces.com/contest/2064/problem/0">
 * https://codeforces.com/contest/2064/problem/0</a>
 */
public class BrogrammingContest {
    public static int brogrammingContest (String s) {
	boolean isZero = true;
	int moves = 0;
	for (int i = 0; i < s.length (); ++i) {
	    if (s.charAt (i) != (isZero ? '0' : '1')) {
		++moves;
		isZero = !isZero;
	    }
	}
	return moves;
    }
    public static void main (String[] args) {
	Scanner scanner = new Scanner (System.in);
	int t = scanner.nextInt ();
	while (t-- > 0) {
	    int n = scanner.nextInt ();
	    String s = scanner.next ();
	    System.out.println (brogrammingContest (s));
	}
    }
}
