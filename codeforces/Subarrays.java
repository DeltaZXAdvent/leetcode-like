import java.util.*;
/**
 * <a href="https://codeforces.com/contest/2276/problem/C">
 * https://codeforces.com/contest/2276/problem/C
 * </a>
 *
 * <script src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/4.0.0/tex-mml-chtml.js"></script>
 */
public class Subarrays {
    public static void main (String[] args) {
		Scanner s = new Scanner (System.in);
		int t = s.nextInt ();
		while (t-- > 0) {
			int n = s.nextInt(),
				k = s.nextInt();
			List<Integer> a = new ArrayList<>(n);
			for (int i = 0; i < n; ++i) {
				a.addLast(s.nextInt());
			}
			List<Integer> S = new ArrayList<>(n + 1);
			int sum = 0;
			S.addLast(sum);
			for (int i = 0; i < n; ++i) {
				sum += a.get(i);
				sum %= k;
				S.addLast(sum);
			}
			List<Integer> count = new ArrayList<>(k);
			for (int i = 0; i < k; ++i) {
				count.addLast(0);
			}
			long result = 0;
			for (int i = k; i <= n; ++i) {
				result += count.get(S.get(i));
				count.set(S.get(i - k), count.get(S.get(i - k)) + 1);
			}
			System.out.println(result);
		}
    }
}
