// https://blog.csdn.net/2301_76848549/article/details/135223251?csdn_share_tail=%7B%22type%22%3A%22blog%22%2C%22rType%22%3A%22article%22%2C%22rId%22%3A%22135223251%22%2C%22source%22%3A%222301_76848549%22%7D
// Equivalent: An array of arrays, every array having some properties, find the shortest subarray containing the specified properties
// Solution: There are only \Theta(n^2) subarrays
// Fix the right index, we can always find the least left index which can contain a satisfying subarray
// And if the right index is larger, then the best left index can only be larger
// Therefore only one traverse is needed
//
// When pushing every element (a column), update the rightmost position of a containing column for every property.
// If all the properties can be satisfied by a more left left boundary, increment the left boundary to that position.
//
// The algorithm is essentially a branch and cut nested loop:
// The outer loop loops against the right index, the inner the left.
