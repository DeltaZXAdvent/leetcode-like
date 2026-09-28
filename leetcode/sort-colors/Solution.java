// https://leetcode.cn/problems/sort-colors/?envType=study-plan-v2&envId=top-100-liked
// Alternative solutions: https://leetcode.cn/problems/sort-colors/solutions/?envType=study-plan-v2&envId=top-100-liked
class Solution {
    public void sortColors(int[] nums) {
        int p2, p0, p1;
        p2 = p0 = p1 = 0;
        for (;;) {
            // java.util.Arrays.stream(nums).forEach(i -> System.err.printf("%d ", i));
            // System.err.printf("p2:%d,p0:%d,p1:%d", p2, p0, p1);
            // System.err.println();
            if (p2 == nums.length) break;
            switch (nums[p2]) {
            case 0:
                swap(nums, p2++, p1);
                swap(nums, p1++, p0);
                p0++;
                break;
            case 1:
                swap(nums, p2++, p1);
                p1++;
                break;
            case 2:
                p2++;
                break;
            }
        }
    }
    public void swap(int[] nums, int i, int j) {
        int tmp = nums[i];
        nums[i] = nums[j];
        nums[j] = tmp;
    }
    public static void main(String[] args) {
        test(new int[]{2,0,2,1,1,0});
        test(new int[]{2,0,1});
    }
    public static void test(int[] nums) {
        new Solution().sortColors(nums);
    }
}
