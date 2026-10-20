import java.util.*;
/**
 * <a href="https://codeforces.com/contest/2261/problem/D1">
 * https://codeforces.com/contest/2261/problem/D1
 * </a>
 *
 * <script src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/4.0.0/tex-mml-chtml.js"></script>
 *
 * <p>Dynamic programming: If \(n = 1\), then there's no need for
 * detectors. If \(n > 1\), there's at least a detector at covers one
 * edge spot, so \(f(n) = \min_{1 \le k \le n - 1}^k\{f(k) + f(n -
 * k) + 1\}\).  We can also calculate the best \(k\) for each \(n\).
 *
 * <p>Oh shit, it's just \(\lceil\log_2 n\rceil\).
 *
 * <p>No, \(f(n) = f(\lceil n/2 \rceil) + f(\lfloor n/2 \rfloor) + 1\)
 *
 * <p>1 0, 2 1, 3 2, 4 3, 5 4, 6 5, 7 6, ...
 *
 * <p>Wrong! There are better solutions.
 *
 * <p>Note: For a fixed number of detectors, the maxmium number of
 * hiding areas is determined. And the construction of distinguished
 * areas can take a greedy approach. Adding one detector can at most
 * create two more dinstinguished areas (if there are already more
 * than two areas). So \(g(n+1)=g(n)+2\) for \(n\ge
 * 1\). \(g(1)=2\). \(f = \min_h\{g(h(n))\ge n\}\). Thus \(f(n)=\lceil
 * n/2 \rceil\).
 *
 * <p>\(f(1)=0\), which is special.
 *
 * <p>A very off-topic thing to note: \(g(0)=1\) rather than \(0\)?
 *
 * <p>For a way to install detectors, just make sure that after each
 * step, there's always two areas to divide if possible.
 *
 * <p>Thinking about the harder question: First select areas with most
 * spots to divide. (Need not two areas with most spots.) This can be
 * show with a proof of existence with better solutions. I haven't
 * done this rigorously.
 */
public class ComeBeMyFriendDontBeSoScaredEasyVersion {
    public static void main (String[] args) {
		Scanner s = new Scanner (System.in);
		int t = s.nextInt ();
		while (t-- > 0) {
			int n = s.nextInt(),
				m = s.nextInt();
			int k = n == 1 ? 0 : (n + 1) / 2;
			System.out.println(k);
			for (int i = 0; i < k; ++i)
				System.out.format("%d %d\n", 1 + i, n / 2 + i);
		}
    }
}
