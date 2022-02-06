import unittest
from quicksort import *
from order_stats import *

class TestQuicksort(unittest.TestCase):
    def test_quicksort_1(self):
        for i in range(0, 100):
            arr = random.sample(range(100), random.randint(10, 50))
            quicksort(arr, 0, len(arr)-1, version(1))
            self.assertEqual(arr, sorted(arr))
            # print(f"Test {i+1}: {arr == sorted(arr)}")
    
    def test_quicksort_2(self):
        for i in range(0, 100):
            arr = random.sample(range(100), random.randint(10, 50))
            quicksort(arr, 0, len(arr)-1, version(2))
            self.assertEqual(arr, sorted(arr))
            # print(f"Test {i+1}: {arr == sorted(arr)}")
    
    def test_quicksort_3(self):
        for i in range(0, 100):
            arr = random.sample(range(100), random.randint(10, 50))
            quicksort(arr, 0, len(arr)-1, version(3))
            self.assertEqual(arr, sorted(arr))
            # print(f"Test {i+1}: {arr == sorted(arr)}")

class TestOrderStats(unittest.TestCase):
    def test_order_stats_1(self):
        for i in range(0, 100):
            len_arr = random.randint(10, 50)
            arr = random.sample(range(100), len_arr)
            rank = random.randint(1, len_arr)
            self.assertEqual(sorted(arr)[rank-1], select(arr, 0, len(arr)-1, rank, version(1)))

    def test_order_stats_2(self):
        for i in range(0, 100):
            len_arr = random.randint(10, 50)
            arr = random.sample(range(100), len_arr)
            rank = random.randint(1, len_arr)
            self.assertEqual(sorted(arr)[rank-1], select(arr, 0, len(arr)-1, rank, version(2)))
    
    def test_order_stats_3(self):
        for i in range(0, 100):
            len_arr = random.randint(10, 50)
            arr = random.sample(range(100), len_arr)
            rank = random.randint(1, len_arr)
            self.assertEqual(sorted(arr)[rank-1], select(arr, 0, len(arr)-1, rank, version(3)))

if __name__ == "__main__":
    unittest.main()