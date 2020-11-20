#pragma once
/*
https://www.geeksforgeeks.org/maximum-sum-rectangle-in-a-2d-matrix-dp-27/

2维矩阵中的和最大的子矩阵


*/
#include<iostream> 

using namespace std;

#define ROW 4
#define COL 5

int calcSubMatrixSum(int M[][COL], int start_row, int start_col, int end_row, int end_col)
{
    int sum = 0;
    for (int i = start_col; i <= end_col; ++i)
    {
        for (int j = start_row; j <= end_row; ++j)
        {
            sum += M[j][i];
        }
    }
//    cout << sum << "\n";
    return sum;
}

/*
    简单算法，直接遍历全部子矩阵，找到和最大的
    时间复杂度O(n^6)
*/
void sample(int M[][COL])
{
    int maxSum = 0;
    int sR = 0;
    int sC = 0;
    int eR = 0;
    int eC = 0;
    for (int startRow = 0; startRow < ROW; ++startRow)
    {
        for (int startCol = 0; startCol < COL; ++startCol)
        {
            for (int endRow = startRow; endRow < ROW; ++endRow)
            {
                for (int endCol = startCol; endCol < COL; ++endCol)
                {
                    int sum = calcSubMatrixSum(M, startRow, startCol, endRow, endCol);
                    if (sum > maxSum)
                    {
                        maxSum = sum;
                        sR = startRow;
                        sC = startCol;
                        eR = endRow;
                        eC = endCol;
                    }
                }
            }
        }
    }
    cout << "sample : \n"
        << "maxSum:" << maxSum << "\n"
        << "sR:" << sR << "\n"
        << "sC:" << sC << "\n"
        << "eR:" << eR << "\n"
        << "eC:" << eC << "\n";
}

/*
    结合Kadane算法
    以列为基础，查找当前n列中的连续行中和最大的子矩阵
    时间复杂度O(n^3)
*/
// Implementation of Kadane's algorithm for
// 1D array. The function returns the maximum
// sum and stores starting and ending indexes
// of the maximum sum subarray at addresses
// pointed by start and finish pointers
// respectively.
int kadane(int* arr, int* start, int* finish, int n)
{
    // initialize sum, maxSum and
    int sum = 0, maxSum = INT_MIN, i;

    // Just some initial value to check
    // for all negative values case
    *finish = -1;

    // local variable
    int local_start = 0;

    for (i = 0; i < n; ++i)
    {
        sum += arr[i];
        if (sum < 0)
        {
            sum = 0;
            local_start = i + 1;
        }
        else if (sum > maxSum)
        {
            maxSum = sum;
            *start = local_start;
            *finish = i;
        }
    }

    // There is at-least one
    // non-negative number
    if (*finish != -1)
        return maxSum;

    // Special Case: When all numbers
    // in arr[] are negative
    maxSum = arr[0];
    *start = *finish = 0;

    // Find the maximum element in array
    for (i = 1; i < n; i++)
    {
        if (arr[i] > maxSum)
        {
            maxSum = arr[i];
            *start = *finish = i;
        }
    }
    return maxSum;
}

void findMaxSum_With_Kadane(int M[][COL])
{
    // Variables to store the final output
    int maxSum = INT_MIN,
        finalLeft,
        finalRight,
        finalTop,
        finalBottom;

    int left, right, i;
    int temp[ROW], sum, start, finish;

    // Set the left column
    for (left = 0; left < COL; ++left) {
        // Initialize all elements of temp as 0
        memset(temp, 0, sizeof(temp));

        // Set the right column for the left
        // column set by outer loop
        for (right = left; right < COL; ++right) {

            // Calculate sum between current left
            // and right for every row 'i'
            for (i = 0; i < ROW; ++i)
                temp[i] += M[i][right];

            // Find the maximum sum subarray in temp[].
            // The kadane() function also sets values
            // of start and finish. So 'sum' is sum of
            // rectangle between (start, left) and
            // (finish, right) which is the maximum sum
            // with boundary columns strictly as left
            // and right.
            sum = kadane(temp, &start, &finish, ROW);

            // Compare sum with maximum sum so far.
            // If sum is more, then update maxSum and
            // other output values
            if (sum > maxSum) {
                maxSum = sum;
                finalLeft = left;
                finalRight = right;
                finalTop = start;
                finalBottom = finish;
            }
        }
    }

    // Print final values
    cout << "(Top, Left) ("
        << finalTop << ", "
        << finalLeft
        << ")" << endl;
    cout << "(Bottom, Right) ("
        << finalBottom << ", "
        << finalRight << ")" << endl;
    cout << "Max sum is: " << maxSum << endl;
}


void MaximumSumRectangleInA2DMatrix()
{
    cout << "2.MaximumSumRectangleInA2DMatrix : \n";

    int M[ROW][COL] = 
    {
        { 1,   2, -1, -4, -20 },
        { -8, -3,  4,  2,  1 },
        { 3,   8,  10, 1,  3 },
        { -4, -1,  1,  7,  -6 }
    };

    sample(M);
    findMaxSum_With_Kadane(M);
}