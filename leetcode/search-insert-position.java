class Solution {
    public int searchInsert(int[] nums, int target) {
        return searchInsert(nums, target, 0, nums.length);
    }
    public int searchInsert(int[] nums, int target, int i, int j) {
        if (!(i < j)) return i;
        int mid = (i + j) / 2;
        if (nums[mid] < target) return searchInsert(nums, target, mid + 1, j);
        else return searchInsert(nums, target, i, mid);
    }
}
