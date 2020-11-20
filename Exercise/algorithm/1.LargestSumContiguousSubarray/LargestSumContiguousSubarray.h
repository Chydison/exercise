#pragma once
/*
https://www.geeksforgeeks.org/largest-sum-contiguous-subarray/

����ܺ͵�����������

Kadane�㷨�ļ�˼���ǲ�������������������Σ�Ϊ��ʹ��max_ending_here����
�������������ֶ������������ֶΣ�Ϊ��ʹ��max_so_far����ÿ�����ǵõ�һ�������ܺ�ʱ��
������max_so_far���бȽϣ����������max_so_far�������max_so_far

Kadane�ǿ��ڻ�÷¡��ѧ�Ľ��ڣ�����㷨��Ϊ�˽����������еĺͣ�maximum subarray�������

ʱ�临�Ӷ�0(n)
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
    cout << "1.LargestSumContiguousSubarray : Maximum contiguous sum is " << max_sum << "\n";
}