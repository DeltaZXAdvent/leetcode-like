import java.util.*;
public class Solution {
    /**
     * Tries to conform with the standard doclet but may fail to do.
     */

    
    /**
     * https://leetcode.cn/problems/maximum-subarray-with-equal-products/
     * 
     * <p>Inquiry:
     * Such an subarray is either consist of only two elements,
     * one element 1, or relatively prime numbers
     * (Proof: factorize the numbers)
     * 
     * @return max (2, max length of relatively prime subarrays) for clarity
     *
     * <p>To determine the max length of relatively prime subarrays:
     * Lemma 1. Subarrays of a R.P. (relatively prime) array are R.P.
     * Heuristic 1. Whether another numbers is R.P. with a R.P. set is easy to determine,
     * using the product of the set
     *
     * <p>The possibly premature algorithm, while prematurity may be a unnecessary concern:
     * Traverse from the beginning of the array;
     * if finding an exception, that is, a non-R.P. number,
     * determine where the exception occurs, and start from that position.
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
    public static int gcd (int a, int b) {
	if (b == 0) return a;
	return gcd (b, a % b);
    }
    public static void main (String[] args) {
	System.out.println (gcd (1, 2));
    }

    /**
     * https://leetcode.cn/problems/find-mirror-score-of-a-string/description/
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

    public static char mirror (char ch) {
	return (char) ('a' + (25 - (ch - 'a')));
    }
    /**
     * order of the small letter
     */
    public static int no (char ch) {
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
     * https://leetcode.cn/problems/maximum-coins-from-k-consecutive-bags/
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
}
