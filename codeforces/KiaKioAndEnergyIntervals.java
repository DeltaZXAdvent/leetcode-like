import java.util.*;
/**
 * <a href="https://codeforces.com/contest/2269/problem/E">
 * https://codeforces.com/contest/2269/problem/E
 * </a>
 *
 * <script src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/4.0.0/tex-mml-chtml.js"></script>
 *
 * <p>If \(l\) can be equal to \(r\), the result is just the maximum
 * element.
 *
 * <p>A general method is divide and conquer. And this requires that
 * concatenation of two segments creates a segment whose score can be
 * easily calculated from the scores of the two segments, I think.
 *
 * <p>Why \(m\) may not be the maximum element: 110,101,110.
 *
 * <p>Determining the maximum XOR result?
 *
 * <p>Maximum XOR result of one element: First calculate the XOR's of
 * the first \(k\) elements, \(0 \le k \le n\). Then find the maximum
 * XOR of any two of the XOR results.
 *
 * <p>A more symmetric problem: Maximum XOR result of a segment of
 * elements in a cyclic array? This will involve bitwise inversion if
 * using a similar approach to the above. So I think this method is
 * more specific to sums instead of XOR's? However the property that
 * the XOR of concatenation of two segments is the XOR of the XOR's of
 * the two segments may still be useful.
 *
 * <p>Using divide and conquer to find the maximum XOR? No clue...
 *
 * <p>The solution is seemingly brute-force or direct...
 */
public class KiaKioAndEnergyIntervals {
    public static void main (String[] args) {
		Scanner s = new Scanner (System.in);
		int t = s.nextInt ();
		while (t-- > 0) {
			int n = s.nextInt();
			List<Integer> a = new ArrayList<>();
			for (int i = 0; i < n; ++i)
				a.addLast(s.nextInt());
			// TODO
		}
    }
}
