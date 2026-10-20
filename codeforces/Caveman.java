import java.util.*;
/**
 * <a href="https://codeforces.com/contest/2276/problem/D">
 * https://codeforces.com/contest/2276/problem/D
 * </a>
 *
 * <script src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/4.0.0/tex-mml-chtml.js"></script>
 *
 * Find a minimum span tree for each graph component, there is always
 * at least a coloring, except for the case when there are components
 * with single nodes.
 *
 * The number of colorings must be even -- you can swap reds and blues.
 *
 * If there is a path longer than 2, there is more than one type of
 * coloring. To prove this, consider a simple kind of coloring where
 * the colors are based on parent relationship of a minimum spanning
 * tree.
 *
 * The official tutorial seems to have another kind of solution.  --
 * Just use degrees! I firstly mistake for that there can be many
 * components and find using degress is not enough...
 *
 * To test if there is only one type of coloring: If there are more
 * than 1 edge, we can determine the center node; if there are only 1
 * edge, make sure there are two nodes; if there are no edge, ...
 */
public class Caveman {
    public static void main (String[] args) {
		Scanner s = new Scanner (System.in);
		int t = s.nextInt ();
		while (t-- > 0) {
			int n = s.nextInt(),
				m = s.nextInt();
			List<Integer> parent = new ArrayList<>();
			List<Integer> rank = new ArrayList<>();
			List<Boolean> isolated = new ArrayList<>();
			int components = n;
			parent.add(0);
			rank.add(0);
			isolated.add(true);
			for (int i = 1; i <= n; ++i) {
				parent.add(i);
				rank.add(0);
				isolated.add(true);
			}
			boolean not_star_shaped = false;
			int center = 0, candidate = 0;
			for (int i = 0; i < m; ++i) {
				int u = s.nextInt(),
					v = s.nextInt();

				// Update isolated
				isolated.set(u, false);
				isolated.set(v, false);

				// Test if star-shaped '*'
				if (i == 0) {
					center = u;
					candidate = v;
					// System.err.format("center: %d, candidate: %d\n", center, candidate);
				} else if (i == 1) {
					if (u == center || u == candidate)
						center = u;
					else if (v == center || v == candidate)
						center = v;
					else
						not_star_shaped = true;
					// System.err.format("u: %d, v: %d, center: %d\n", u, v, center);
				} else {
					// System.err.format("center: %d\n", center);
					if (u != center && v != center)
						not_star_shaped = true;
				}

				// Test if connected

				// u = Find(u)
				while (parent.get(u) != u) {
					parent.set(u, parent.get(parent.get(u)));
					u = parent.get(u);
				}

				// v = Find(v)
				while (parent.get(v) != v) {
					parent.set(v, parent.get(parent.get(v)));
					v = parent.get(v);
				}

				// Union(u, v)
				if (u != v) {
					--components;
					if (rank.get(u) < rank.get(v)) {
						int tmp = u;
						u = v;
						v = tmp;
					}
					parent.set(v, u);
					if (rank.get(u) == rank.get(v))
						rank.set(u, rank.get(u) + 1);
				}
			}
			boolean has_isolated = false;
			for (int i = 1; i <= n; ++i) {
				if (isolated.get(i)) {
					has_isolated = true;
					break;
				}
			}
			System.out.println(has_isolated ? "Brain Melt" :
							   (components == 1 && !not_star_shaped ? "2" : "Many"));
		}
    }
}
