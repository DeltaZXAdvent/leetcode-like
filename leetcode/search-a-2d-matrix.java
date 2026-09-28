class Solution {
    public boolean searchMatrix(int[][] matrix, int target) {
        return searchMatrix(matrix, target, 0, matrix.length * matrix[0].length);
    }
    public boolean searchMatrix(int[][] matrix, int target, int i, int j) {
        if (!(i < j)) return false;
        int mid = (i + j) / 2,
            checked = matrix[mid / matrix[0].length][mid % matrix[0].length];
        if (checked < target)
            return searchMatrix(matrix, target, mid + 1, j);
        else if (checked > target)
            return searchMatrix(matrix, target, i, mid);
        else return true;
    }
}
