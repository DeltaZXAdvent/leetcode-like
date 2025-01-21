import java.util.*;
/**
 * <a href="https://codeforces.com/contest/2055/problem/D">
 * https://codeforces.com/contest/2055/problem/D </a>
 *
 * <p>Inquiry:
 *
 * <ul>
 * <li> Rule: A scarecrow that has got before the crow cannot become after it.
 * <li> The scarecrows before the crow can continuously push the crow forward.
 * <li> The scarecrows should try best to make the crow jump ahead distances of k,
 * by approaching the crow from front.
 * </ul>
 *
 * <p> Hence,
 * 
 * <ul>
 * <li> When a scarecrow is the nearest among the ones after the crow,
 * it should try best to get before the crow.
 * <li> When a scarecrow after the crow is not the nearest,
 * it should try to keep a distance of k from its left neighbor.
 * </ul>
 *
 * <p> The algorithm:
 *
 * Keep track of the following states: total time elapsed,
 * number of scarecrows that have got behind the crow,
 * the current position of the crow.
 */
public class Scarecrow {
    public static int scarecrow (int n, int k, int l, int[] a) {
	int twiceTime = 0;
	int twicePosition = -2 * a[0];
	for (int i = 0; i < n; ++i) {
	    if (2 * a[i] < twicePosition - twiceTime) {
		twicePosition = 2 * a[i] + twiceTime + 2 * k;
	    } else if (twicePosition - twiceTime <= 2 * a[i] && 2 * a[i] < twicePosition + twiceTime) {
		twicePosition += 2 * k;
	    } else {
		int twiceExtraTime = (2 * a[i] - twiceTime - twicePosition) / 2;
		twiceTime += twiceExtraTime;
		twicePosition += twiceExtraTime;
		if (twicePosition >= 2 * l) return twiceTime - (twicePosition - 2 * l);
		twicePosition += 2 * k;
	    }
	    if (twicePosition >= 2 * l) return twiceTime;
	}
	return twiceTime + 2 * l - twicePosition;
    }
    public static void main (String[] args) {
	Scanner s = new Scanner (System.in);
	int t = s.nextInt ();
	while (t-- > 0) {
	    int n = s.nextInt ();
	    int k = s.nextInt ();
	    int l = s.nextInt ();
	    int[] a = new int[n];
	    for (int i = 0; i < n; ++i) {
		a[i] = s.nextInt ();
	    }
	    System.out.println (scarecrow (n, k, l, a));
	}
    }
}
