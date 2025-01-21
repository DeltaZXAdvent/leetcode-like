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
     * <p>The lexicographic order in the problem specification refers to that of the index arays.
     *
     * <p>Algorithm:
     * <br />Just sort and traverse and reuse former calculations. (Dynamic programming)
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
     *
     * <p>Efficiency sucks. Here is a good solution:
     * <a href="https://leetcode.cn/problems/maximum-score-of-non-overlapping-intervals/solutions/3039058/dong-tai-gui-hua-er-fen-cha-zhao-you-hua-wmuy/">
     * https://leetcode.cn/problems/maximum-score-of-non-overlapping-intervals/solutions/3039058/dong-tai-gui-hua-er-fen-cha-zhao-you-hua-wmuy/</a>
     * I give up cleaning the code. Lessons learnt for Java:
     *
     * <ul>
     * <li>Use records.
     * </ul>
     *
     * <p>Branch and cut?
     *
     * <p> <strong> OK... Actually my equation has a bad complexity... 🤣</strong>
     *
     * <p> Weights must be positive or some functions will have little errors.
     */
    public int[] maximumWeight(List<List<Integer>> intervalsMutOrNot) {
	List <NumberedInterval> intervals = new ArrayList <> ();
	for (int i = 0; i < intervalsMutOrNot.size (); ++i) {
	    intervals.add (new NumberedInterval (i, intervalsMutOrNot.get (i)));
	}
	Collections.sort (intervals,
			  (NumberedInterval lhs, NumberedInterval rhs) ->
			  {
			      return lhs.get (0) - rhs.get (0);
			      // for (int i = 0; i < 3; ++i) {
			      // 	  int difference = lhs.get (i) - rhs.get (i);
			      // 	  if (difference != 0)
			      // 	      return difference;
			      // }
			      // return 0;
			  });
	// System.out.println (intervals);
	// System.out.println (intervals);
	MaxWeightMemo maxWeightMemo = new MaxWeightMemo (intervals, 4);
	for (int k = 2; k <= 4; ++k) {
	    for (int i = intervals.size () - 1; i >= 0; --i)
		maxWeightMemo.setMemoEntryBottomUp (i, k);
	}
	return maxWeightMemo.getMaxWeightIntervals (0, 4);
    }
    private static class NumberedInterval {
	int index;
	List <Integer> interval;
	public NumberedInterval (int index, List <Integer> interval) {
	    this.index = index;
	    this.interval = interval;
	}
	/**
	 * Idk whether there is a way to directly expose the class's field as the interface
	 */
	Integer get (int i) {
	    return interval.get (i);
	}
	public String toString () {
	    String res = "";
	    res += "[";
	    for (int i = 0; i < this.interval.size (); ++i) {
		res += String.valueOf (get (i));
		res += " ";
	    }
	    res += "]";
	    res += String.format (" at %d", index);
	    
	    return res;
	}
    }
    private static class MaxWeightMemoEntry {
	long weight;
	int nextInterval;
	int[] indices;
	MaxWeightMemoEntry (long weight, int nextInterval, int[] indices) {
	    this.weight = weight;
	    this.nextInterval = nextInterval;
	    this.indices = indices;
	}
	public String toString () {
	    String indiceString = "[";
	    for (int i = 0; i < indices.length; ++i) {
		indiceString += String.valueOf (indices[i]);
		indiceString += " ";
	    }
	    indiceString += "]";
	    return String.format ("weight: %d, order: %d, ", weight, nextInterval)
		+ "indices: " + indiceString + "\n";
	}
    }
    private static class MaxWeightMemo {
	List <NumberedInterval> intervals;
	MaxWeightMemoEntry[][] memo;
	int[] indicesAfterInterval;
	int numberOfIntervals;
	/**
	 * @param intervals sorted
	 * @param numberOfIntervals should be positive
	 */
	public MaxWeightMemo (List <NumberedInterval> intervals, int numberOfIntervals) {
	    this.intervals = intervals;
	    this.numberOfIntervals = numberOfIntervals;
	    memo = new MaxWeightMemoEntry[this.intervals.size () + 1][numberOfIntervals];
	    indicesAfterInterval = new int [this.intervals.size ()];
	    for (int i = 0; i < indicesAfterInterval.length; ++i) {
		indicesAfterInterval[i] = intervalAfterPoint (intervals, intervals.get (i).get (1));
	    }
	    setNoIntervalMemoEntries ();
	    setSingleIntervalMemoEntries ();
	}
	public int[] getMaxWeightIntervals (int startIndex, int wantedNumberOfIntervals) {
	    return getMemoEntry (startIndex, wantedNumberOfIntervals).indices;
	}
	/**
	 * Should be obsoleted.
	 * 
	 * <p> I guess an Iterator version could be written.
	 */
	public int[] getMaxWeightIntervalsFromScratch (int startIndex, int wantedNumberOfIntervals) {
	    List <Integer> wanted = new ArrayList <> ();
	    while (wantedNumberOfIntervals > 0) {
		MaxWeightMemoEntry memoEntry = getMemoEntry (startIndex, wantedNumberOfIntervals);
		if (memoEntry.nextInterval == intervals.size ())
		    break;
		// System.out.println (String.valueOf (memoEntry) + " " + intervals.get (memoEntry.nextInterval));
		wanted.add (Integer.valueOf (intervals.get (memoEntry.nextInterval).index));
		startIndex = indicesAfterInterval[memoEntry.nextInterval];
		--wantedNumberOfIntervals;
	    }
	    int[] ans = new int[wanted.size ()];
	    for (int i = 0; i < ans.length; ++i)
		ans[i] = wanted.get (i).intValue ();
	    Arrays.sort (ans);
	    return ans;
	}
	private void setSingleIntervalMemoEntries () {
	    int currentMaxWeight = 0,
		currentMaxWeightInterval = intervals.size (); // wrong value, because Java forces initialization
	    for (int i = intervals.size () - 1; i >= 0; --i) {
		int currentWeight = intervals.get (i).get (2);
		if (currentWeight > currentMaxWeight
		    || currentWeight == currentMaxWeight
		    && intervals.get (i).index < intervals.get (currentMaxWeightInterval).index) {
		    currentMaxWeight = currentWeight;
		    currentMaxWeightInterval = i;
		}
		int[] indices = new int[] {intervals.get (currentMaxWeightInterval).index};
		setMemoEntry (i, 1, new MaxWeightMemoEntry (currentMaxWeight, currentMaxWeightInterval, indices));
	    }
	}
	private void setNoIntervalMemoEntries () {
	    for (int i = 1; i <= numberOfIntervals; ++i) {
		setMemoEntry (intervals.size (), i, new MaxWeightMemoEntry (0, intervals.size (), new int[0]));
	    }
	}
	/**
	 * @param wantedNumberOfIntervals in 1..{@link #numberOfIntervals numberOfIntervals}
	 */
	public MaxWeightMemoEntry getMemoEntry (int startIndex, int wantedNumberOfIntervals) {
	    // System.out.println (String.format ("entry startIndex: %d, wantedNumberOfIntervals: %d",
	    // 				       startIndex, wantedNumberOfIntervals));
	    MaxWeightMemoEntry memoEntry = memo [startIndex] [wantedNumberOfIntervals - 1];
	    if (memoEntry != null) {
		// System.out.println (String.format ("return startIndex: %d, wantedNumberOfIntervals: %d",
		// 				   startIndex, wantedNumberOfIntervals));
		return memoEntry;
	    }
	    if (numberOfIntervals == 1) {
		return null;
		// throw new Exception ("Please set single-interval memo entries first.");
	    }
	    long maxTotalWeight = 0;
	    int nextInterval = intervals.size ();
	    int[] bestIndices = new int[0];
	    for (int i = startIndex; i < intervals.size (); ++i) {
		MaxWeightMemoEntry entry = getMemoEntry (indicesAfterInterval[i], wantedNumberOfIntervals - 1);
		long totalWeight = intervals.get (i).get (2) + entry.weight;
		int[] newIndices = sortedArrayAdd (entry.indices, intervals.get (i).index);
		if (totalWeight > maxTotalWeight
		    || totalWeight == maxTotalWeight
		    && compareLexicographically (newIndices,
						 bestIndices) < 0) {
		    // if (totalWeight == maxTotalWeight && maxTotalWeight != 0)
		    // 	System.out.print (String.format ("better start interval: %d, original: %d\n"
		    // 					 + "startPosition: %d, wantedNumberOfIntervals: %d\n"
		    // 					 + "totalWeight: %d\n"
		    // 					 + "bestIndices: %s, newIndices: %s\n",
		    // 					 intervals.get (i).index,
		    // 					 intervals.get (nextInterval).index,
		    // 					 intervals.get (startIndex).get (0),
		    // 					 wantedNumberOfIntervals,
		    // 					 totalWeight,
		    // 					 bestIndices, newIndices));
		    maxTotalWeight = totalWeight;
		    nextInterval = i;
		    bestIndices = newIndices;
		}
	    }
	    MaxWeightMemoEntry newMemoEntry = new MaxWeightMemoEntry (maxTotalWeight, nextInterval, bestIndices);
	    setMemoEntry (startIndex, wantedNumberOfIntervals,
			  newMemoEntry);
	    // System.out.println (String.format ("Set! startIndex: %d, startPosition: %d, wantedNumberOfIntervals: %d",
	    // 				       startIndex, intervals.get (startIndex).index, wantedNumberOfIntervals));
	    // System.out.println (newMemoEntry);
	    // System.out.println (String.format ("return startIndex: %d, wantedNumberOfIntervals: %d",
	    // 				       startIndex, wantedNumberOfIntervals));
	    return newMemoEntry;
	}
	public void setMemoEntryBottomUp (int startIndex, int wantedNumberOfIntervals) {
	    MaxWeightMemoEntry candidateMemoEntry = new MaxWeightMemoEntry (0, intervals.size (), new int [0]);
	    for (int i = startIndex; i < intervals.size (); ++i) {
		MaxWeightMemoEntry entry = getMemoEntryBottomUp (indicesAfterInterval[i], wantedNumberOfIntervals - 1);
		long totalWeight = intervals.get (i).get (2) + entry.weight;
		int[] newIndices = sortedArrayAdd (entry.indices, intervals.get (i).index);
		if (totalWeight > candidateMemoEntry.weight
		    || totalWeight == candidateMemoEntry.weight
		    && compareLexicographically (newIndices,
						 candidateMemoEntry.indices) < 0) {
		    candidateMemoEntry.weight = totalWeight;
		    candidateMemoEntry.nextInterval = i;
		    candidateMemoEntry.indices = newIndices;
		}
	    }
	    setMemoEntry (startIndex, wantedNumberOfIntervals,
			  candidateMemoEntry);
	}
	public MaxWeightMemoEntry getMemoEntryBottomUp (int startIndex, int wantedNumberOfIntervals) {
	    return memo [startIndex] [wantedNumberOfIntervals - 1];
	}

	public void setMemoEntry (int startIndex,
					  int wantedNumberOfIntervals,
					  MaxWeightMemoEntry memoEntry) {
	    memo [startIndex] [wantedNumberOfIntervals - 1] = memoEntry;
	}
    }
    /**
     * @param point exclusive starting point
     */
    private static int intervalAfterPoint (List <NumberedInterval> intervals, int point) {
	int negativeIndex =
	    Collections.binarySearch (intervals, new NumberedInterval (0, List.of (point, 0, 0)),
				      (NumberedInterval interval, NumberedInterval intervalFromPoint) ->
				      {
					  return 2 * (interval.get (0) - intervalFromPoint.get (0)) - 1; // make 0 negative
				      });
	return -(negativeIndex + 1);
    }
    private static int[] sortedArrayAdd (int[] array, int element) {
	int[] res = new int[array.length + 1];
	int i = 0;
	for (; i < array.length; ++i) {
	    if (array[i] < element)
		res[i] = array[i];
	    else break;
	}
	res[i] = element;
	++i;
	for (; i < res.length; ++i) {
	    res[i] = array[i - 1];
	}
	return res;
	// List <Integer> lst = new ArrayList <> ();
	// for (int i = 0; i < array.length; ++i) {
	//     lst.add (Integer.valueOf (array[i]));
	// }
	// lst.add (Integer.valueOf (element));
	// Collections.sort (lst);
	// int[] res = new int[lst.size ()];
	// for (int i = 0; i < res.length; ++i)
	//     res[i] = lst.get (i).intValue ();
	// return res;
    }
    /**
     * May need better literature, but let's write it quick currently
     */
    private static int compareLexicographically (int[] lhs, int[] rhs) {
	int i = 0;
	while (true) {
	    if (i >= lhs.length && i < rhs.length)
		return -1;
	    if (i < lhs.length && i >= rhs.length)
		return 1;
	    if (i >= lhs.length && i >= rhs.length)
		return 0;
	    if (lhs[i] == rhs[i]) {
		++i;
		continue;
	    }
	    return lhs[i] - rhs[i];
	}
    }
}
