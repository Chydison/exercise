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
                        sR = startRow+1;
                        sC = startCol+1;
                        eR = endRow+1;
                        eC = endCol+1;
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
    Kadane算法
*/

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
}