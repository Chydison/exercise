#pragma once
/*
https://www.geeksforgeeks.org/largest-sum-contiguous-subarray/

最大总和的连续子数组

Kadane算法的简单思想是查找数组的所有正连续段（为此使用max_ending_here）。
并跟踪所有正分段中最大和连续分段（为此使用max_so_far）。每次我们得到一个正数总和时，
将它与max_so_far进行比较，如果它大于max_so_far，则更新max_so_far

Kadane是卡内基梅隆大学的教授，这个算法是为了解决最大子序列的和（maximum subarray）提出的

时间复杂度0(n)
*/
#include<iostream> 

using namespace std;

int maxSubArraySum(int a[], int size)
{
    int max_so_far = INT_MIN, max_ending_here = 0;

    for (int i = 0; i < size; i++)
    {
        max_ending_here = max_ending_here + a[i];
        if (max_so_far < max_ending_here)
            max_so_far = max_ending_here;

        if (max_ending_here < 0)
            max_ending_here = 0;
    }
    return max_so_far;
}

void LargestSumContiguousSubarray()
{
    int a[] = { -2, -3, 4, -1, -2, 1, 5, -3 };
    int n = sizeof(a) / sizeof(a[0]);
    int max_sum = maxSubArraySum(a, n);
    cout << "1.LargestSumContiguousSubarray : Maximum contiguous sum is " << max_sum << endl;
}
