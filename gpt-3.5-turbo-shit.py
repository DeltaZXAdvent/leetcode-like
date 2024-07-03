# Requirement: add two arrays, minimize the maximum of the sum array
def add_arrays_minimize_max(arr1, arr2):
    max_sum = float('-inf')
    result = []
    for i in range(len(arr1)):
        sum_value = arr1[i] + arr2[i]
        result.append(sum_value)
        max_sum = max(max_sum, sum_value)
    
    return max_sum

# Example usage:
if False:
    array1 = [1, 5, 3]
    array2 = [2, 4, 6]

    max_sum = add_arrays_minimize_max(array1, array2)
    print("Maximum sum:", max_sum)
    quit ()

# Prompt: You do not have to group the elements according to indice
def add_arrays_minimize_max(arr1, arr2):
    sum_array = [x + y for x, y in zip(arr1, arr2)]
    sum_array.sort(reverse=True)

    min_max = float('inf')
    for i in range(1, len(sum_array)):
        min_max = min(min_max, max(sum_array[:i]) - min(sum_array[i:]))

    return min_max

# Example usage:
array1 = [1, 5, 3]
array2 = [2, 4, 6]

min_max = add_arrays_minimize_max(array1, array2)
print("Minimum maximum sum:", min_max)
quit ()

# Requirement: Minimize the max of the sum arrays of two arrays with permutation allowed
def minimize_max_sum(arr1, arr2):
    arr1.sort()  # Sort the first array in non-decreasing order
    arr2.sort()  # Sort the second array in non-decreasing order

    pointer1 = 0
    pointer2 = 0
    min_max = float('inf')

    while pointer1 < len(arr1) and pointer2 < len(arr2):
        curr_sum = arr1[pointer1] + arr2[pointer2]
        min_max = min(min_max, curr_sum)

        if arr1[pointer1] < arr2[pointer2]:
            pointer1 += 1
        else:
            pointer2 += 1

    # Handle remaining elements in either array
    while pointer1 < len(arr1):
        curr_sum = arr1[pointer1] + arr2[-1]
        min_max = min(min_max, curr_sum)
        pointer1 += 1

    while pointer2 < len(arr2):
        curr_sum = arr1[-1] + arr2[pointer2]
        min_max = min(min_max, curr_sum)
        pointer2 += 1

    return min_max

# Example usage:
array1 = [1, 5, 3]
array2 = [2, 4, 6]

min_max = minimize_max_sum(array1, array2)
print("Minimum maximum sum:", min_max)

