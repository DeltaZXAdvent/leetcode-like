// https://leetcode.cn/problems/majority-element/description/?envType=study-plan-v2&envId=top-100-liked
class Solution {
    public int majorityElement(int[] nums) {
        int times = 0;
        int candidate = 0;
        for (int i = 0; i < nums.length; ++i) {
            if (times == 0)
                candidate = nums[i];
            times += nums[i] == candidate ? 1 : -1;
        }
        return candidate;
    }
}
