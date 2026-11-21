import java.util.*;
/**
 * <a href="https://codeforces.com/contest/2290/problem/B">
 * https://codeforces.com/contest/2290/problem/B
 * </a>
 *
 * <script src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/4.0.0/tex-mml-chtml.js"></script>
 */
public class StubbornPen {
    public static void main (String[] args) {
		Scanner s = new Scanner (System.in);
		int t = s.nextInt ();
		while (t-- > 0) {
			int n  = s.nextInt();
			String str = s.next();
			int sw = 0;
			if (str.charAt(0) == 'B')
				++sw;
			for (int i = 1; i < n; ++i) {
				if (str.charAt(i) == str.charAt(i - 1))
					++sw;
			}
			System.out.println(sw);
		}
    }
}
