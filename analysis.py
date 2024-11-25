def sum_pairs(nums):
    result = []
    for i in range(len(nums)):
        for j in range(i + 1, len(nums)):
            result.append(nums[i] + nums[j])
    return result

def contains_value(arr, target):
    for i in range(len(arr)):
        if arr[i] == target:
            return True
    return False

def prefix_sum(arr):
    result = [0] * len(arr)
    result[0] = arr[0]
    for i in range(1, len(arr)):
        result[i] = result[i - 1] + arr[i]
    return result

def print_pairs(arr):
    for i in range(len(arr)):
        for j in range(len(arr)):
            print(arr[i], arr[j])

def fibonacci(n):
    if n <= 1:
        return n
    else:
        return fibonacci(n - 1) + fibonacci(n - 2)
