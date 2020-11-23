/******************************************************************************
 *  题目说明：求数组中两个数的最大差值（只能下标大的减去下标小的）
 *  解题思路：设置当前数组中的最小值为minValue，最大差值为maxDiff。然后依次遍历数组中
 *           的每一个元素，当遍历到一个元素时求出当前元素与之前的minValue差值，用该差值
 *           和当前最大的差值相比较，如果该差值大于当前最大差值，则更新当前最大差值。
 *           然后用该元素和当前最小的元素相比较。如果该元素小于当前最小元素，则更新当前最小元素
 *           时间复杂度：O(n)
******************************************************************************/
#include <stdio.h>

int arrayMaxDiff(int a[], int len)
{
    int i,maxDiff, minValue;

    if (NULL == a || len < 2)
    {
        printf("ERROR!! input parameter error\n");
        return 0;
    }
    maxDiff = a[1] - a[0];
    minValue = (a[0] < a[1])? a[0] : a[1];

    for (i = 2; i < len; i++)
    {
        if ((a[i] - minValue) > maxDiff)
        {
            maxDiff = a[i] - minValue;
        }
        if (a[i] < minValue)
            minValue = a[i];
    }
    return maxDiff;
}

int main()
{
    int a[8] = {3,9,4,5,7,8,2,6};

    printf("max difference:%d\n",arrayMaxDiff(a,8));
    return 0;
}