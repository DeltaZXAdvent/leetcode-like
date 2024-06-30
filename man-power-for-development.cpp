// https://blog.csdn.net/2301_76848549/article/details/136021875?csdn_share_tail=%7B%22type%22%3A%22blog%22%2C%22rType%22%3A%22article%22%2C%22rId%22%3A%22136021875%22%2C%22source%22%3A%222301_76848549%22%7D
// What a poor specification.
// Stupidity: man-month is not a requirement on the simultaneous developers needed ^^;
// Remapping: time: m, the number of requirements: n, the requirements: a_i
// Distribute an array of n elements into m boxes, no box containinig more than 2 elements.
// Minimize the maximum number of elements in one box.
// Solution:
// (Method A) if m = n, sol = max{a_i} (to be denoted as sol (m))
// if m = n - 1, sol (n - 1) = max (sol (n), min1 + min2) (Recursion is usually useful but always?)
// ...
//
// (Method B) Lemma: All the two-element boxes can contain the smallest elements
// Proof, Suppose there is one small enough element that occupies a single box, exchange the position of it
// with another.
// So the problem only has to solve the case when m = n / 2;
// Then just put the largest and the smallest into the same box. (I guess true.)
// Proof, permutation model etc.
//
// Let's see the standard answer: double pointers blahblah, garbage, why always fancy names? Stupid.
//
// Let's write these programs in Haskell, because these algorithms are purely functional.


