import java.util.*;
/**
 * <a href="https://codeforces.com/contest/2064/problem/B">
 * https://codeforces.com/contest/2064/problem/B</a>
 *
 * Maximize the score: Don't delete any repeated element
 * Minimise the length: choose a longest segment
 */
public class VarietyIsDiscouraged {
    public static void main (String[] args) {
	Scanner s = new Scanner (System.in);
	int t = s.nextInt ();
	while (t-- > 0) {
	    int n = s.nextInt ();
	    int[] a = new int[n];
	    for (int i = 0; i < n; ++i)
		a[i] = s.nextInt ();
	    Map <Integer, Boolean> isRepeated = new HashMap <> ();
	    for (int i = 0; i < n; ++i) {
		Integer key = Integer.valueOf (a[i]);
		if (isRepeated.containsKey (key)) {
		    isRepeated.put (key, Boolean.TRUE);
		} else {
		    isRepeated.put (key, Boolean.FALSE);
		}
	    }
	    int l = 0, r = 0;
	    int maxLen = 0;
	    int left = 0;
	    for (int right = 0; right < n; ++right) {
		if (isRepeated.get (Integer.valueOf (a[right])).booleanValue ()) {
		    left = right + 1;
		} else {
		    int newLen = right + 1 - left;
		    if (newLen > maxLen) {
			maxLen = newLen;
			l = left + 1;
			r = right + 1;
		    }
		}
	    }
	    if (maxLen == 0) {
		System.out.println (0);
	    } else {
		System.out.print (l);
		System.out.print (" ");
		System.out.println (r);
	    }
	}
    }
}
