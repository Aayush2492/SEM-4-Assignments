import random
from partition import *

def select(arr, p ,r, i, en_obj):
    if p==r:
        return arr[p]
    q = partition(arr, p, r, en_obj)
    rank_of_qth_elem = q - p + 1
    if rank_of_qth_elem == i:
        return arr[q]
    elif rank_of_qth_elem < i:
        return select(arr, q+1, r, i - rank_of_qth_elem, en_obj)
    else:
        return select(arr, p, q-1, i, en_obj)

def main():
    arr = random.sample(range(100), 10)
    rank = 3
    print("Unsorted:", arr)
    print("Sorted: ", sorted(arr))
    print(f"Element at rank {rank} is {select(arr, 0, len(arr)-1, rank, version.DETERMINISTIC_PIVOT)}")

if __name__ == "__main__":
    main()

