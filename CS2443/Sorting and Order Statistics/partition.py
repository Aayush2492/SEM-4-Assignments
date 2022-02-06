import random
from enum import Enum

class version(Enum):
    LAST_AS_PIVOT = 1
    RANDOM_PIVOT = 2
    DETERMINISTIC_PIVOT = 3

def get_optimum_pivot(arr):
    arr_len = len(arr)
    mod_len = arr_len % 5

    assert(arr_len > 0)
    if arr_len <= 5:
        return arr[arr_len // 2]
    
    medians = []
    for i in range(0, arr_len-(5 - mod_len) + 1, 5):
        arr[i:i+5] = sorted(arr[i:i+5])
        medians.append(arr[i+2])
    if mod_len != 0:
        arr[arr_len - mod_len :] = sorted(arr[arr_len - mod_len:])
        medians.append(arr[arr_len - mod_len + mod_len // 2])
    return get_optimum_pivot(medians)

def partition(arr, p, r, en_obj):
    if en_obj.name == "LAST_AS_PIVOT":
        pivot = arr[r]
    elif en_obj.name == "RANDOM_PIVOT":
        pivot_index = random.randint(p,r)
        pivot = arr[pivot_index]
        arr[pivot_index], arr[r] = arr[r], arr[pivot_index]
    elif en_obj.name == "DETERMINISTIC_PIVOT":
        pivot_index = arr.index(get_optimum_pivot(arr[p:r+1]))
        pivot = arr[pivot_index]
        arr[pivot_index], arr[r] = arr[r], arr[pivot_index]
    i = p
    for j in range(p, r):
        if(arr[j] < pivot):
            arr[i], arr[j] = arr[j], arr[i]
            i+=1
    arr[i], arr[r] = arr[r], arr[i]
    return i