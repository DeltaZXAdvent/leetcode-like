import java.util.*;
/**
 * <a href="https://codeforces.com/contest/2060/problem/F">
 * https://codeforces.com/contest/2060/problem/F</a>
 *
 * <p> Unfinished.
 * 
 * <p> I ever try to eliminate the sum from 1 to n by using this observation:
 * $ \sum P_k (n) = P_{k+1} (n) $
 *
 * <p> Refer to the official solution.
 */
public class MultiplicativeArrays {
    public static int multiplicativeArrays (int k, int n) {
	
    }
    private static int sameBallsIntoDifferentBoxes (int balls, int boxes) {
	
    }
    public static void main (String[] args) {
	Scanner s = new Scanner (System.in);
	int t = s.nextInt ();
	while (t-- > 0) {
	    int k = s.nextInt ();
	    int n = s.nextInt ();
	    
	}
    }
}
/**
 * Same balls into different boxes.
 */
class ArrangementCounter {
    private final int boxes;
    private List <Integer> memo;
    public ArrangementCounter (int boxes) {
	this.boxes = boxes;
	this.memo = new ArrayList <Integer> ();
	memo.add (Integer.valueOf (1));
    }
    /**
     * @return C(n+k-1,k) where n and k are the number of boxes and balls repectively.
     */
    public int arrangements (int balls) {
	if (balls >= memo.size ())
	    memo.add (Integer.valueOf (arrangements (balls - 1) * (n + balls - 1) / balls));
	return memo.get (balls).intValue ();
    }
}
class FactorTable {
    /**
     * The smallest factors for 1 to {@link k}, 1 for 1.
     */
    private List <Integer> smallestFactors;
    public FactorTable (int k) {
	smallestFactors = new ArrayList <Integer> (k + 1); // extra one for index 0
	for (int i = 1; i <= k; ++i)
	    smallestFactors.add (i, 0);
	for (int i = 1; i <= k; ++i) {
	    if (smallestFactors.get (i) == 0)
		for (int j = i; j <= k; j += i)
		    if (smallestFactors.get (j) == 0)
			smallestFactors.add (j, i);
	}
    }
    public int smallestFactor (int i) {
	return smallestFactors.get (i);
    }
}
