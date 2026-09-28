import java.util.*;
/**
 * <a href="https://codeforces.com/contest/2269/problem/C">
 * https://codeforces.com/contest/2269/problem/C
 * </a>
 *
 * <script src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/4.0.0/tex-mml-chtml.js"></script>
 * 
 * <p>The final number of elements is \(n_0=k-1\). The number of
 * elements removed is \(n_1=n-n_0\). If \(n \ge 2n_1\), i.e. \(n \le
 * 2(k - 1)\), then it can be shown that the elements removed are
 * always the ones that reside, at the beginning, closer to the
 * boundary than the first two removal candidates.
 *
 * <p>If this is not the case, it will eventually become the
 * case. Before becoming the case, the removed elements will be those
 * that reside between the first two removal candidates, so which one
 * to remove is not relevant.
 *
 * <p>We only have to consider the policy for the first case. In that
 * case, every choice is between two candidates which are already
 * decided at the beginning, whose detail you can check.
 *
 * <p>So a greedy algorithm is enough.
 *
 * <p>I think a deletion-fast array is a <a
 * href="https://en.wikipedia.org/wiki/B-tree">B-tree</a>? Let's try
 * ArrayList. Although we don't need to simulate this actually.
 *
 * <p>ArrayList is enough to be accepted.
 */
public class KIsImportant {
    public static void main (String[] args) {
		Scanner s = new Scanner (System.in);
		int t = s.nextInt ();
		while (t-- > 0) {
			int n = s.nextInt(),
				k = s.nextInt();
			List<Integer> a = new ArrayList<>();
			for (int i = 0; i < n; ++i)
				a.addLast(s.nextInt());
			long score = 0;
			while (a.size() >= k) {
				int x = a.get(k - 1),
					m = a.size(),
					y = a.get(m - k);
				score += Math.max(x, y);
				a.remove(x >= y ? k - 1 : m - k);
			}
			System.out.println (score);
		}
    }
}
