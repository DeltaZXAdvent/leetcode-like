import java.util.*;
/**
 * <a href="https://codeforces.com/contest/2290/problem/C">
 * https://codeforces.com/contest/2290/problem/C
 * </a>
 *
 * <script src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/4.0.0/tex-mml-chtml.js"></script>
 *
 * TODO check solution code style and compare
 */
public class BooksOnAShelf {
    public static void main (String[] args) {
		Scanner s = new Scanner (System.in);
		int t = s.nextInt ();
		while (t-- > 0) {
			int n = s.nextInt();
			int[] h = new int[n];
			for (int i = 0; i < n; ++i)
				h[i] = s.nextInt();
			Arrays.sort(h);
			int k = 1;
			if (1 < n)
				++k;
			for (int i = 2; i < n; ++i)
				if (h[i] > h[i - 1] || h[i] > h[i - 2])
					++k;
			System.out.println (k);
			int[] arr = new int[n];
			int left = 0, right = n - 1;
			arr[left++] = h[0];
			for (int i = 1; i < n; ++i) {
				if (h[i] > h[i - 1])
					arr[left++] = h[i];
				else
					arr[right--] = h[i];
			}
			for (int i = 0; i < n - 1; ++i) {
				System.out.format("%d ", arr[i]);
			}
			System.out.println (arr[n - 1]);
		}
    }
}
