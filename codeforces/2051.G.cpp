/**
 * https://codeforces.com/contest/2051/problem/G
 *
 * If snake i is succeeded by j, i on the left,
 * then the space between them should be kept in:
 * the max difference between enlarging times of i and shrinking times of j
 * spaces. Set zero if negative.
 *
 * To achieve the minimum score, the rightmost snake should have a minimum sum of
 * its enlarging times and its initial position.
 *
 * I guess it can be proved that only a condense initial position is needed.
 *
 * ~~Yes. Because the space expanded is fixed. We only have to make sure~~
 * ~~the initial space allocated is minimum.~~
 * ?TODO
 *
 * The initial space needed for every pair can be calculated,
 * in one pass of the events.
 *
 * It is a square matrix, from which $n-1$ cells have to be chosen,
 * in different rows and columns.
 *
 * There are $n!$ kinds of arrangements. It seems a bad method.
 *
 * ------------------------------------------------------------
 *
 * Things to note:
 * - Shrinking times cannot be larger than enlarging times
 */
#include <iostream>
using namespace std;
int main (int argc, char *argv[])
{
  
  return 0;
}
