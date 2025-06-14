/**
 * https://codeforces.com/contest/2114/problem/F
 *
 * Note that taking the largest factor does not help,
 * e.g. 75^4 = 81 * 25 * 25 * 25 * 25 = 75 * 75 * 75 * 75
 * though 81 is larger, selecting 75 as the largest factor will benefit
 * (divide 75^4 into products of numbers no greater than 81)
 *
 * f (x, y, k) = f (x / gcd, 1, k) + f (1, y / gcd, k)
 * f (x, 1, k) = f(1, x, k)
 */
