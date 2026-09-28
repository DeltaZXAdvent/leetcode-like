// https://leetcode.cn/problems/next-permutation/?envType=study-plan-v2&envId=top-100-liked
// next(a,A)=if is_max(A)
// then (next_letter(a,A),ordered((a,A)/next_letter(a,A)))
// else (a,next(A))
class Solution {
    public void nextPermutation(int[] nums) {
        // last increasing digit
        int i;
        for (i = nums.length - 2; i >= 0; --i) {
            if (nums[i] < nums[i + 1]) break;
        }
        if (i == -1) reverse(nums, 0, nums.length - 1);
        else {
            reverse(nums, i + 1, nums.length - 1);
            // first major digit
            int j;
            for (j = i + 1; nums[j] <= nums[i]; ++j);
            swap(nums, i, j);
        }
    }
    public void reverse(int[] nums, int i, int j) {
        while (i < j) {
            swap(nums, i, j);
            ++i;
            --j;
        }
    }
    public void swap(int[] nums, int i, int j) {
        int tmp = nums[i];
        nums[i] = nums[j];
        nums[j] = tmp;
    }
}
