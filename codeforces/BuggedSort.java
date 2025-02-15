import java.util.*;
/**
 * <a href="https://codeforces.com/contest/2060/problem/G">
 * https://codeforces.com/contest/2060/problem/G</a>
 *
 * <p>LaTeX:
 *
 * <p>
 * The swap operation on indices $i, j$, $u_{ij}$ can be decomposed as
 * two kinds of operations: $u_{ij} = s_i s_j x_{ij}$,
 * where $s_i$ represents swapping $a_i$ with $b_i$,
 * $x_{ij}$ represents swapping $a_i$ with $a_j$, and $b_i$ with $b_j$.
 * 
 * Note $u_{ij} = s_i x_{ij} s_i$. It can be seen that
 * $ u_{ik} u_{jk} u_{ik}
 * = s_k x_{ik} s_k s_k x_{jk} s_k u_{ik}
 * = s_k x_{ik} x_{jk} s_k u_{ik}
 * = s_k x_{ik} x_{jk} s_k s_k x_{ik} s_k
 * = s_k x_{ik} x_{jk} x_{ik} s_k
 * = s_k x_{ij} s_k
 * = x_{ij} s_k s_k
 * = x_{ij} $.
 * $s_i s_j = u_{ij} x_{ij}$.
 * Hence when there are more than 3 elements, there exist two more fundamental
 * operations: exchange $x_{ij}$ and pairwise spin (flip) $s_i s_j$.
 * As long as the number of inverted elements are even, the case is possible.
 * 
 * We can sort the sequences using exchanges and single spins, by
 * placing one smallest element per time. When have completed the sort,
 * an odd amount of spins might have been used. But in some cases we can transform the amount to be even.
 * It depends on the following condition:
 * in the sorted sequences, there is a range of an odd number of elements,
 * which are greater than all elements to their left and less than all elements to their right.
 * 
 * The above is my first method, involving a pre-tranverse of the sequences.
 * 
 * However we can use the following simpler method (I immediately came up with):
 * decide the relationship between two elements using such a criterion:
 * the relationship between the larger and the one between the smaller must be the same, otherwise
 * the sequences are not sortable.
 * 
 * And when we are sorting the sequences, the number of orientation mismatches ought to be recorded.
 * OK, let's abandon this method. First try to sort then try to test if the flips are plausible,
 * as is in the official solution.
 */
public class BuggedSort {
    public static boolean isBuggedSortable (int n, int[] a, int[] b) {
	
    }
    public static void main (String[] args) {
	Scanner s = new Scanner (System.in);
	int t = s.nextInt ();
	while (t-- > 0) {
	    int n = s.nextInt ();
	    int[] a = new int[n];
	    int[] b = new int[n];
	    System.out.println (isBuggedSortable (n, a, b) ? "YES" : "NO");
	}
    }
}
