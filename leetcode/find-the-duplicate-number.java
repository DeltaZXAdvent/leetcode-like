// https://leetcode.cn/problems/find-the-duplicate-number/?envType=study-plan-v2&envId=top-100-liked
// XOR numbers: 0(0) 1(1) 2(3) 0(3) 4(4) 1(5) 7(6) 0(7) 8(8) 1(9) 11(10) ...
//
// For all numbers, k, 1 <= k <= n
// count{x <= k} <= k (k < target)
// count{x <= target} >= target
// count{x <= k} >= k (k > target)
//
// No. Think more clearly:
// If k < target, count{x <= k} <= k, count{x >= k} > n - k + 1;
// if k > target, count{x <= k} > k, count{x >= k} <= n - k + 1;
// if k == target, count{x <= k} > k, count{x >= k} > n - k + 1.
//
// target is the least k that satisfies count{x <= k} > k
class Solution {
    public int findDuplicate(int[] nums) {
        // XOR based don't work
        // int result = 0;
        // for (int i = 0; i < nums.length; ++i)
        //     result ^= nums[i] ^ i;
        // return result;

        return findDuplicate(nums, 0, nums.length);
    }
    // In (i,j]
    public int findDuplicate(int[] nums, int i, int j) {
        if (i + 1 == j) return j;
        int count = 0,
            mid = (i + j) / 2;
        for (int num: nums) {
            if (num <= mid)
                ++count;
        }
        return count <= mid ?
            findDuplicate(nums, mid, j) :
            findDuplicate(nums, i, mid);
    }
}
