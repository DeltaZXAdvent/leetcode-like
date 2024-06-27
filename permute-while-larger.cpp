// https://blog.csdn.net/2301_76848549/article/details/138115234?csdn_share_tail=%7B%22type%22%3A%22blog%22%2C%22rType%22%3A%22article%22%2C%22rId%22%3A%22138115234%22%2C%22source%22%3A%222301_76848549%22%7D
// Change symbols: a -> A, b -> B
// If B is permuted, the result will be the same
// Sort the B in descending order, compute the number of elements in A which is greater than B_i, let it be C_i
// C_i <= C_{i+1}
// The solution is only dependent on C_i
// For every array {C_i} with positive length, it can be seen that solution({C_i}) = C_1 * solution({C_i} - 1)
// where {C_i} - 1 represents for an array with length and all the elements decreased by 1
// Let solution({C_i}) be 1 if the length is 1 and C_1 is 1
// Or let solution({C_i}) be 1 if the length is zero
//
// we can optimize when there is no solution?
