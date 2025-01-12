import java.util.*;
public class Solution {
    /**
     * Tries to conform with the standard doclet but may fail to do.
     */

    
    /**
     * <a href="https://leetcode.cn/problems/maximum-subarray-with-equal-products/">
     * https://leetcode.cn/problems/maximum-subarray-with-equal-products/</a>
     * 
     * <p>Inquiry:
     * Such an subarray is either consist of only two elements,
     * one element 1, or relatively prime numbers
     * (Proof: factorize the numbers)
     * 
     * <p>To determine the max length of relatively prime subarrays:
     *
     * <ul>
     * <li>Lemma 1. Subarrays of a R.P. (relatively prime) array are R.P.
     * <li>Heuristic 1. Whether another numbers is R.P. with a R.P. set is easy to determine,
     * using the product of the set
     * </ul>
     *
     * <p>The possibly premature algorithm, while prematurity may be a unnecessary concern:
     * <br />Traverse from the beginning of the array;
     * if finding an exception, that is, a non-R.P. number,
     * determine where the exception occurs, and start from that position.
     * 
     * @return max (2, max length of relatively prime subarrays) for clarity
     */
    public static int maxLength (int[] nums) {
	int begin = 0,
	    product = 1,
	    end = 0,
	    result = 0;
	while (end < nums.length) {
	    if (gcd (product, nums [end]) == 1) {
		System.out.println ("yes");
		product *= nums [end];
		++end;
		result = Math.max (result, end - begin);
	    } else {
		System.out.println ("no");
		begin = end;
		product = 1;
		while (gcd (nums [begin - 1], nums [end]) == 1) {
		    --begin;
		    product *= nums [begin];
		}
	    }
	    System.out.println (begin);
	    System.out.println (end);
	}
	return Math.max (2, result);
    }
    private static int gcd (int a, int b) {
	if (b == 0) return a;
	return gcd (b, a % b);
    }
    public static void main (String[] args) {
	System.out.println (gcd (1, 2));
    }

    /**
     * <a href="https://leetcode.cn/problems/find-mirror-score-of-a-string/description/">
     * https://leetcode.cn/problems/find-mirror-score-of-a-string/description/</a>
     *
     * <p>Maybe static linked list is better.
     */
    public static long calculateScore (String s) {
	long score = 0;
	List <Stack <Integer>> positions = new ArrayList <> ();
	for (char ch = 'a'; ch <= 'z'; ++ch) {
	    positions.add (new Stack <Integer> ());
	}
	for (int i = 0; i < s.length (); ++i) {
	    Stack <Integer> mirrorStack = positions.get (no (mirror (s.charAt (i))));
	    if (mirrorStack.empty ()) {
		positions.get (no (s.charAt (i))).push (i);
	    } else {
		score += i - mirrorStack.pop ();
	    }
	    // System.out.println (positions);
	}
	return score;
    }

    private static char mirror (char ch) {
	return (char) ('a' + (25 - (ch - 'a')));
    }
    /**
     * order of the small letter
     */
    private static int no (char ch) {
	return ch - 'a';
    }
    /**
     * I thought this was what the problem wanted.
     */
    public long calculateScoreBF (String s) {
	boolean[] flags = new boolean [s.length ()];
	long score = 0;
	for (int i = 0; i < s.length (); ++i) {
	    for (int j = i - 1; j >= 0; --j) {
		if (!flags[j] && (s.charAt (i) - 'a') + (s.charAt (j) - 'a') == 'z' - 'a') {
		    flags[i] = flags[j] = true;
		    score += i - j;
		    break;
		}
	    }
	}
	return score;
    }

    /**
     * <a href="https://leetcode.cn/problems/maximum-coins-from-k-consecutive-bags/">
     * https://leetcode.cn/problems/maximum-coins-from-k-consecutive-bags/</a>
     * 
     * <p>The beginning of the k-interval is at the beginning of a coins interval,
     * or the end of the k-interval is at the end of a coins interval.
     *
     * <p>😅
     */
    public long maximumCoins (int[][] coins, int k) {
	Arrays.sort (coins,
		     (int[] lhsTriple, int[] rhsTriple) ->
		     { return lhsTriple[0] - rhsTriple[0]; });
	// for (int i = 0; i < coins.length; ++i) {
	//     for (int j = 0; j < coins[i].length; ++j)
	// 	System.out.println (coins[i][j]);
	//     System.out.println ();
	// }
	int begin = 1 - k, end = 0,
	    leftNextInterval = 0,
	    rightNextInterval = 0;
	boolean leftInGap = true,
	    rightInGap = true;
	long current = 0, result = 0;
	while (leftNextInterval < coins.length && rightNextInterval < coins.length) {
	    int leftDistance = coins [leftNextInterval] [0] - begin,
		rightDistance = coins [rightNextInterval] [1] - end;
	    int distance = Math.min (leftDistance, rightDistance);
	    // System.out.println (leftDistance < rightDistance);
	    if (leftDistance < rightDistance) {
		end += distance;
		if (rightInGap) {
		    if (end >= coins [rightNextInterval] [0]) {
			rightInGap = false;
			current += (end - coins [rightNextInterval] [0] + 1) * (long) coins [rightNextInterval] [2];
		    }
		} else
		    current += distance * (long) coins [rightNextInterval] [2];

		if (!leftInGap) {
		    int leftCurrentInterval = leftNextInterval - 1;
		    current -= (coins [leftCurrentInterval] [1] - begin + 1) * (long) coins [leftCurrentInterval] [2];
		} else {
		    leftInGap = false;
		}
		begin += distance;
		leftNextInterval += 1;
	    } else {
		if (rightInGap)
		    current += (coins [rightNextInterval] [1] - coins [rightNextInterval] [0] + 1) * (long) coins [rightNextInterval] [2];
		else {
		    current += (coins [rightNextInterval] [1] - end) * (long) coins [rightNextInterval] [2];
		    rightInGap = true;
		}
		end += rightDistance;
		rightNextInterval += 1;
		
		int nextBegin = begin + distance;
		if (!leftInGap) {
		    int leftCurrentInterval = leftNextInterval - 1;
		    if (nextBegin > coins [leftCurrentInterval] [1]) {
			current -= (coins [leftCurrentInterval] [1] - begin + 1) * (long) coins [leftCurrentInterval] [2];
			leftInGap = true;
		    } else
			current -= distance * (long) coins [leftCurrentInterval] [2];
		}
		begin = nextBegin;
	    }

	    result = Math.max (result, current);
	    // System.out.println (begin);
	    // System.out.println (end);
	    // System.out.println (result);
	}
	return result;
    }

    /**
     * <a href="https://leetcode.cn/problems/maximum-score-of-non-overlapping-intervals/">
     * https://leetcode.cn/problems/maximum-score-of-non-overlapping-intervals/</a>
     *
     * <p>Algorithm:
     * <br />Just sort and traverse and reuse former calculations.
     *
     * <p>The recorded results are
     * "starting from the ith interval the maximum weight achieved by choosing at most k intervals,
     * where 0 &lt;= i &lt; intervals.length and 1 &lt;= k &lt;= 4, and the indices of the succeeding intervals".
     *
     * <p>Let's try top-down first.
     *
     * <p>(Inquiry in vain) Properties of the optimal intervals:
     * 
     * <ul>
     * <li>Any of the optimal intervals cannot be replaced by another interval with a higher weight
     * or with a same weight but with a smaller order, without violating the non-overlapping
     * requirement.
     * </ul>
     */
    public int[] maximumWeight(List<List<Integer>> intervalsMutOrNot) {
	List <List <Integer> > intervals = new ArrayList <> (intervalsMutOrNot);
	Collections.sort (intervals,
			  (List <Integer> lhs, List <Integer> rhs) ->
			  {
			      for (int i = 0; i < 3; ++i) {
				  int difference = lhs.get (0) - rhs.get (0);
				  if (difference != 0)
				      return difference;
			      }
			      return 0;
			  });
	MaxWeightMemoEntry[][] memo = createMemo (intervals.size (), 4);
	setSingleIntervalMemoEntries (memo, intervals);
	List <Integer> result = new ArrayList <> ();
	result.add (getMemoEntry (memo, 0, 4).nextInterval);
	// TODO
	return null;
    }
    private static class MaxWeightMemoEntry {
	int weight;
	int nextInterval;
	MaxWeightMemoEntry (int weight, int nextInterval) {
	    this.weight = weight;
	    this.nextInterval = nextInterval;
	}
    }
    private static int intervalAfterPoint (List <List <Integer>> intervals, int point) {
	// TODO binary search
	return 0;
    }
    private static MaxWeightMemoEntry[][] createMemo (int intervalsSize, int numberOfIntervals) {
	return new MaxWeightMemoEntry[intervalsSize][numberOfIntervals];
    }
    private static MaxWeightMemoEntry getMemoEntry (MaxWeightMemoEntry[][] memo,
					    int startIndex,
					    int numberOfIntervals) {
	MaxWeightMemoEntry memoEntry = memo [startIndex] [numberOfIntervals - 1];
	if (memoEntry != null)
	    return memoEntry;
	if (numberOfIntervals == 1) {
	    return null;
	    // throw new Exception ("Please set single-interval memo entries first.");
	}
	// TODO
	return null;
    }
    private static void setMemoEntry (MaxWeightMemoEntry[][] memo,
			      int startIndex,
			      int numberOfIntervals,
			      MaxWeightMemoEntry memoEntry) {
	memo [startIndex] [numberOfIntervals - 1] = memoEntry;
    }
    private static void setSingleIntervalMemoEntries (MaxWeightMemoEntry[][] memo, List <List <Integer> > intervals) {
	int currentMaxWeight = 0,
	    currentMaxWeightInterval = intervals.size (); // wrong value, because Java forces initialization
	for (int i = intervals.size () - 1; i >= 0; ++i) {
	    int currentWeight = intervals.get (i).get (2);
	    if (currentWeight >= currentMaxWeight) {
		currentMaxWeight = currentWeight;
		currentMaxWeightInterval = i;
	    }
	    setMemoEntry (memo, i, 1, new MaxWeightMemoEntry (currentMaxWeight, currentMaxWeightInterval));
	}
    }
}
