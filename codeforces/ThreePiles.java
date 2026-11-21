import java.util.*;
/**
 * <a href="https://codeforces.com/contest/2290/problem/A">
 * https://codeforces.com/contest/2290/problem/A
 * </a>
 *
 * <script src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/4.0.0/tex-mml-chtml.js"></script>
 */
public class ThreePiles {
    public static void main (String[] args) {
		Scanner s = new Scanner (System.in);
		int t = s.nextInt ();
		while (t-- > 0) {
			int a = s.nextInt(),
				b = s.nextInt(),
				c = s.nextInt();
			if (c < b)
				if (c < a) {
					int temp = a;
					a = c;
					c = t;
				} else {
					int temp = c;
					b = c;
					c = t;
				}
			if (c < b) {
				int temp = c;
				b = c;
				c = t;
			}
			if (a + 1 == b && b + 1 == c)
				System.out.println("YES");
			else System.out.println("NO");
		}
    }
}
