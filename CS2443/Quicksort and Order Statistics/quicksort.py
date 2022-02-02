import random
from partition import *

def quicksort(arr, p, r, version):
    if version.value == 3:
        assert(len(arr) == len(set(arr)))
    if p < r:
        q = partition(arr, p, r, version)
        quicksort(arr, p, q-1, version)
        quicksort(arr, q+1, r, version)

if __name__ == "__main__":
    arr = random.sample(range(100), 10)
    # print("Unsorted:", arr)
    quicksort(arr, 0, len(arr)-1, version.DETERMINISTIC_PIVOT)
    # print("Sorted:", arr)
    print(arr == sorted(arr))