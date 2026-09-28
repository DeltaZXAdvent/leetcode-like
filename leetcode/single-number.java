// https://leetcode.cn/problems/single-number/description/?envType=study-plan-v2&envId=top-100-liked
// TODO https://raghu-vijaykumar.github.io/docs/docs/dsa/bit-manipulation/xor-algorithms/#1-single-number-xor-all-elements
class Solution {
    public int singleNumber(int[] nums) {
        int result = 0;
        for (int num: nums)
            result ^= num;
        return result;
    }
}
