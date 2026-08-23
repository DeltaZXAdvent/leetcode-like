import java.util.*;
/**
 * <a href="https://codeforces.com/contest/2256/problem/A">
 * https://codeforces.com/contest/2256/problem/A</a>
 *
 * <!-- Using defer will generate an error, so I used this CDN which does not require it. -->
 *
 * <script src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/4.0.0/tex-mml-chtml.js"></script>
 * 
 * Assume \(a\le b\le c\), \(\text{Ans}=min(c-a,b)\)
 * Proof: if \(a + b = c\), then whatever change won't improve
 * the minimum range. Thus only the first step matters.
 */
public class ThreeNumbersOnTheBlackboard {
    public static void main (String[] args) {
	Scanner s = new Scanner (System.in);
	int t = s.nextInt ();
	while (t-- > 0) {
	    List<Integer> a = new ArrayList<>(3);
	    for (int i = 0; i < 3; ++i)
		a.addLast(s.nextInt());
	    // bubble sort
	    if (a.get(0) > a.get(1))
		Collections.swap(a, 0, 1);
	    if (a.get(1) > a.get(2)) {
		Collections.swap(a, 1, 2);
		if (a.get(0) > a.get(1))
		    Collections.swap(a, 0, 1);
	    }
	    System.out.println(Math.min(a.get(2) - a.get(0), a.get(1)));
	}
    }
}
