import java.util.*;
/**
 * <a href="https://codeforces.com/contest/2269/problem/D">
 * https://codeforces.com/contest/2269/problem/D
 * </a>
 *
 * <script src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/4.0.0/tex-mml-chtml.js"></script>
 *
 * <p>The bit masks of \(3 \cdot k\): 0011 0110 1001 1100 1111. Any
 * bitmask with an even number of 1's can be composed from these, and
 * only those can be composed.
 *
 * <p>To be divisble by 3 is a tighter constraint than with an even
 * number of 1's. 0, 3, 5, 9, 6, 10, 12, 15. 0,3,5,6,9,10,12,15.  The
 * latter is equivalent with divisbility by 3 or 5. (Verified for
 * \(a_i &lt; 16\)).
 *
 * <p>Denote a number that is divisble by 3 as a liked number and a
 * number that is divisble by 3 or 5 as a good number.
 *
 * <p>If there is a segment of all good numbers, they can all be
 * transformed into zeroes with the last number good and possibly
 * liked.  Is it possible to transform a pair of an only good number
 * and a liked number to be both liked?
 *
 * <p>good = {unready, liked}
 *
 * <p>Every unready can be composed of two liked's.
 *
 * <p>Conclusion: we have only to check whether a number is divisible
 * by 3 or 5.
 *
 * <p>This is just abstract algebra?
 */
public class WhatASauSaGeItsAllMeat {
	static boolean isGood(int x) {
		return x % 3 == 0 || x % 5 == 0;
	}
    public static void main (String[] args) {
		Scanner s = new Scanner (System.in);
		int t = s.nextInt ();
		while (t-- > 0) {
			int n = s.nextInt(),
				q = s.nextInt();
			List<Integer> a = new ArrayList<>();
			int num = 0;
			for (int i = 0; i < n; ++i) {
				int x = s.nextInt();
				a.addLast(x);
				if (isGood(x))
					++num;
			}
			System.out.print (num);
			while (q-- != 0) {
				int p = s.nextInt(),
					x = s.nextInt();
				if (isGood(a.get(p - 1)))
					--num;
				if (isGood(x))
					++num;
				a.set(p - 1, x);
				System.out.printf (" %d", num);
			}
			System.out.println ();
		}
    }
}
