import java.util.*;
/**
 * <a href="https://codeforces.com/contest/2256/problem/D">
 * https://codeforces.com/contest/2256/problem/D</a>
 *
 * <script src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/4.0.0/tex-mml-chtml.js"></script>
 *
 * <p>Investigation:
 * 
 * \(a R b S c T d \rightarrow
 * c \bar S b \bar R a T d \rightarrow
 * c \bar S d \bar T a R b\);
 *
 * \(a R b S c T d \rightarrow
 * a R d \bar T c \bar S b \rightarrow
 * c T d \bar R a \bar S b\).
 *
 * The order does matter.
 *
 * <p>Noted things:
 * 1. The number of maximal homogeneous substrings is fixed;
 * 2. The kind of the first substring is fixed.
 *
 * <p>Let \(i,I\) be the number of 0 and 0-substrings,
 * and \(j,J\) be those of 1.
 * 
 * <p>The answer is \({i - 1\choose I-1} \times {j - 1\choose J-1}\).
 *
 * <p>Determining the parameters: traversal.
 *
 * <p>\((P \mod i) + \)
 */
public class ARibbonForTomorrow {
    public static void main (String[] args) {
	// https://codeforces.com/blog/entry/155840
	// Precompute inverses (this is a new thing I suppose)
	int N = 1000000;
	int[] inverses = new int[N + 1];
	inverses[1] = 1;
	for (int idx = 2; idx <= N; ++idx) {
	    inverses[idx] = Math.floorMod((long) -inverses[998244353 % idx] * (998244353 / idx), 998244353);
	}
	
	Scanner s = new Scanner (System.in);
	int t = s.nextInt ();
	while (t-- > 0) {
	    int n = s.nextInt();
	    String str = s.next();
	    int ind = 0;
	    int i = 0;
	    int I = 0;
	    int j = 0;
	    int J = 0;
	    for (;;) {
		char c = str.charAt(ind);
		if (c == '0') ++i; else ++j;
		if (++ind >= n) {
		    if (c == '0') ++I; else ++J;
		    break;
		}
		if (str.charAt(ind) != c) {
		    if (c == '0') ++I; else ++J;
		}
	    }
	    
	    // System.err.println("debug");
	    // System.err.println(i);
	    // System.err.println(I);
	    // System.err.println(j);
	    // System.err.println(J);

	    long ans = 1;
	    for (ind = 1; ind <= I - 1; ++ind) {
		ans = ans * (i - I + ind) % 998244353;
		ans = (ans * inverses[ind]) % 998244353;
	    }
	    for (ind = 1; ind <= J - 1; ++ind) {
		ans = (ans * (j - J + ind)) % 998244353;
		ans = (ans * inverses[ind]) % 998244353;
	    }
	    System.out.println(ans);
	}
    }
}
