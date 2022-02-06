#include <stdio.h>
#include <limits.h>

class sub_array_info
{
public:
    unsigned left_index, right_index;
    int max_sum;

    sub_array_info(unsigned left_index, unsigned right_index, int max_sum)
    {
        this->left_index = left_index;
        this->right_index = right_index;
        this->max_sum = max_sum;
    }
};

sub_array_info *get_max_crossing_sub_array(int arr[], unsigned low, unsigned high)
{
    unsigned mid = (low + high) / 2;
    // get subarray with max sum with indices between low,high(both incl) with max sum s.t.arr[mid], arr[mid+1] are there in subarray

    int left_sum = arr[mid];
    int sum = 0;
    unsigned left_index = mid;
    for (int i = (int)mid; i >= (int)low; i--)
    {
        sum = sum + arr[i];
        if (sum > left_sum)
        {
            left_sum = sum;
            left_index = (unsigned)i;
        }
    }

    sum = 0;
    unsigned right_index = mid + 1;
    int right_sum = arr[mid + 1];
    for (unsigned i = mid + 1; i <= high; i++)
    {
        sum = sum + arr[i];
        if (sum > right_sum)
        {
            right_sum = sum;
            right_index = i;
        }
    }

    sub_array_info *ptr = new sub_array_info(left_index, right_index, left_sum + right_sum);
    return (ptr);
}

sub_array_info *maximum_sub_array(int arr[], unsigned low, unsigned high)
{
    if (low == high)
    {
        sub_array_info *ptr = new sub_array_info(low, high, arr[low]);
        return ptr;
    }

    unsigned mid = (low + high) / 2;

    sub_array_info *left = maximum_sub_array(arr, low, mid);
    sub_array_info *middle = get_max_crossing_sub_array(arr, low, high);
    sub_array_info *right = maximum_sub_array(arr, mid + 1, high);

    if (left->max_sum > middle->max_sum)
    {
        if (left->max_sum > right->max_sum)
        {
            return left;
        }
        else // right->max_sum >= left->max_sum
        {
            return (right);
        }
    }
    else
    {
        if (middle->max_sum > right->max_sum)
        {
            return middle;
        }
        else
        {
            return right;
        }
    }
}

sub_array_info *maximum_sub_array_linear(int arr[], unsigned N)
{
    unsigned left_index = 0, right_index = 0, temp_left_index = 0;
    int max_sum = INT_MIN, current_sum = 0;

    for (unsigned i = 0; i <= N - 1; i++)
    {
        current_sum += arr[i];
        if (current_sum > max_sum)
        {
            max_sum = current_sum;
            right_index = i;
            left_index = temp_left_index;
        }

        if (current_sum < 0)
        {
            current_sum = 0;
            temp_left_index = i + 1;
        }
    }

    sub_array_info *ptr = new sub_array_info(left_index, right_index, max_sum);
    return ptr;
}

int main()
{
    int arr[] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
    // int arr[] = {-3, 2, -1};
    unsigned length_of_array = sizeof(arr) / sizeof(arr[0]);

    sub_array_info *ptr = maximum_sub_array(arr, 0, length_of_array - 1);
    sub_array_info *ptr_l = maximum_sub_array_linear(arr, length_of_array);

    printf("%u %u\n", ptr->left_index, ptr->right_index);
    printf("%u %u\n", ptr_l->left_index, ptr_l->right_index);

    return 0;
}