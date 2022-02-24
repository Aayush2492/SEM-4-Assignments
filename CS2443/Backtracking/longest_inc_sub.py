arr = []

# Returns the length of LIS from A[j....len-1] s.t. all > A[i]
def long_inc_sub_2(i, j):
    global arr
    if j >= len(arr):
        return 0
    if arr[j] <= arr[i]:
        return long_inc_sub_2(i, j+1)
    else:
        return(max(1+long_inc_sub_2(j, j+1), long_inc_sub_2(i, j+1)))

# Returns the length of LIS from A[i+1....len-1] that includes A[i]
def long_inc_sub(i):
    global arr
    longest = 0
    for j in range(i+1, len(arr)):
        if arr[j] > arr[i]:
            longest = max(longest, long_inc_sub(j))
    return 1+longest

def main():
    global arr
    arr = [3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 8, 9, 7, 9, 3, 2, 3, 8, 4, 6, 2, 6]
    arr.insert(0, -10)
    print(long_inc_sub(0)-1)
    print(arr)
    print(long_inc_sub_2(0,1))

if __name__ == '__main__':
    main()
