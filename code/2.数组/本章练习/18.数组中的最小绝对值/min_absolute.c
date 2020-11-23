/******************************************************************************
 *  题目说明：给定一个有序数组（从小到大排列），数组中的数有正有负，求这个数组中元素的最小绝对值。
 *  解题思路：求最接近0的数
******************************************************************************/
#include <stdio.h>

#define  ABS(a)     ((a) > 0 ? (a) : -(a))

/**
 * @函数名称: searchClosestValue
 * @功能描述: 寻找有序数组中最接近某个值的数
 * @输入参数: 
 *      a: 数组a,升序排列
 *      len:  数组长度
 *      value: 查找的值
 * @输出参数: 
 *      closest: 数组中最接近value的值
 * @返回值: 
 *      closest的下标（在数组中的位置）
 * @其他说明: 二分查找法，数组必须有序
 */
int searchClosestValue(int a[], int len, int value, int *closest)
{
    int start = 0;
    int end = len - 1;
    int mid = (start + end) / 2;
    int index;

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
            *closest = a[mid];
            return mid;
        }
    }
    // 查找最接近的数，此时start=end,最接近的数在start-1，start,start+1中
    index = start;
    *closest = a[start];
    if ((start - 1) >= 0)
    {
        if (ABS(*closest - value) > ABS(a[start - 1] - value))
        {
            index = start - 1;
            *closest = a[start - 1];
        }
    }
    if ((start + 1) < len)
    {
        if (ABS(*closest - value) > ABS(a[start + 1] - value))
        {
            index = start + 1;
            *closest = a[start + 1];
        }
    }
    return index;
}

int main()
{
    int a[10] = {-15,-8,-4,-3,-2,3,4,5,7,13};
    int closest,index;

    index = searchClosestValue(a, 10, 0, &closest);
    printf("min absolute is:%d,index=%d\n",closest,index);

    return 0;
}