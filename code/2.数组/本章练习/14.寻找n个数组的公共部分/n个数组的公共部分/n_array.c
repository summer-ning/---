/******************************************************************************
 *  题目说明：给定n个数组，每个数组中的元素都是递增的，现在要找出这n个数组中的公
            共元素，如何做？要求不能用额外辅助空间。
 *  解题思路：如果按照两个数组的方法，使用指针的方式，需要O(n)的辅助空间来记录下标。
 *          不使用辅助空间，我能想到的是使用二分查找，二分查找时间复杂度为O(logm)，所以
 *          总的时间复杂度O(nmlogm)
******************************************************************************/
#include <stdio.h>

#define   ARRAY_LEN     (10)
#define   ARRAY_NUM     (5)

/**
 * @函数名称: binarySearch
 * @功能描述: 二分查找
 * @输入参数: 
 *      a: 有序数组
 *      len: 数组的长度
 *      value: 查找的数据
 * @输出参数: void
 * @返回值: value在数组中的下标，如果数组中不存在value，返回-1
 * @其他说明: 数组a必须是升序排列的
 */
int binarySearch(int a[], int len, int value)
{
    int start = 0;
    int end = len - 1;
    int mid = (start + end) / 2;
    int index = -1;

    // 二分查找是否存在要找的值
    while (start <= end)
    {
        mid = (start + end) / 2;
        if (a[mid] > value)
        {
            end = mid - 1;
        }
        else if (a[mid] < value)
        {
            start = mid + 1;
        }
        else
        {
            return mid;
        }
    }

    return -1;
}

void getCommonElement(int (*a)[ARRAY_LEN], int n)
{
    int i,j;

    for (i = 0; i < ARRAY_LEN; i++)
    {
        for (j = 1; j < n; j++)
        {
            if (binarySearch(a[j], ARRAY_LEN, a[0][i]) < 0)
                break;
        }
        if (j == n)
        {
            printf("%d ", a[0][i]);
        }
    }
}

int main()
{
    int a[ARRAY_NUM][ARRAY_LEN] = {
        {1,2,4,5,7,8,9,10,11,15},
        {2,3,4,5,6,7,9,10,11,12},
        {3,4,5,6,7,8,9,10,11,12},
        {4,5,6,7,8,9,11,12,13,14},
        {6,7,8,9,10,11,12,13,14,18},
    };

    getCommonElement(a, ARRAY_NUM);

    return 0;
}
