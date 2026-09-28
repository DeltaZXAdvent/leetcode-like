import java.util.*;
/**
 * <a href="https://codeforces.com/contest/2256/problem/E">
 * https://codeforces.com/contest/2256/problem/E</a>
 *
 * <script src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/4.0.0/tex-mml-chtml.js"></script>
 * 
 * <p>Investigation:
 * First, there can be \(n^2\) possibilities of \(x\).
 * ... Analysis of the validity of the size of probability
 * space seems not going anywhere...
 *
 * <p>Try 2:
 * In math: one-dimensional images with black sells of a prime number count
 * cannot be repeated by shift:
 * for the black sells form into congruence classes,
 * and every congruence class has the same element of numbers.
 * However for reflection it's not.
 *
 * <p>(Wrong!) Now consider the probability space:
 * For a fixed \(w\), there can be \({n^2\choose w}/(8n^2)\) possibilities.

 * <p>In two-dimensional, for shift it is while for rotation and reflection
 * it's not.
 *
 * <p>When the transformed image (while not swapped) is seen,
 * it is in the candidates of the possible rotations
 * and reflections.
 *
 * <p>Every image has a center position.
 *
 * <p>The black center multiplied by its weight added by the white center
 * multiplied by its weight, divided by \(n^2\) is at the image center
 *
 * <p>I misunderstood in the following:
 *
 * <p>\(c_1 w + c_2 (n^2 - w)) = c n^2 \Rightarrow
 * (c_1-c_2)/n^2=(c-c_2)/w\)
 *
 * <p>(I was wrong, you can actually determine the target cell based only on the shape,
 * see the following about "modulo center". And such shapes can be created
 * with only one move.)
 * This is kind of misleading? if images is not shared between the two,
 * there will be no way to determine the target cell because of the
 * size of the probability space.
 *
 * <p>Actually, the program can use the information from the swapper too...
 *
 * <p>The specification could be more simplistic?
 *
 * <p>OK. Have seen <a href=https://codeforces.com/blog/entry/155840>
 * the answer</a>. You can move the center to the target cell within
 * one swap. I thought it was impossible.
 *
 * <p>I misunderstood above.
 *
 * <p>The basic idea is to use the "modulo center" (I name it).
 *
 * <p>Still involves number theory or abstract algebra.
 * For example, computation of \(w^{-1}\).
 *
 * <p>The existence of the cell that, when swapped, moves center
 * to the target is also mathematically interesting.
 *
 * TODO Interesting
 */
public class EvenIfTheWorldTurns {
    public static void main (String[] args) {
	Scanner s = new Scanner (System.in);
	int t = s.nextInt ();
	while (t-- > 0) {
	    
	}
    }
}
