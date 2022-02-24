def subset_sum(arr, T):
    if(T == 0):
        return True
    if(T < 0):
        return False
    if(len(arr) == 1):
        return arr[0] == T
    return(subset_sum(arr[0:-1], T) | subset_sum(arr[0:-1], T-arr[-1]))


def main():
    arr = [11, 6, 5, 1, 7, 13, 12]
    T = 15
    print(subset_sum(arr, T))


if __name__ == "__main__":
    main()
