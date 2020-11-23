/******************************************************************************
 *  题目说明：输入一个整数数组，调整数组中数字的顺序，使得所有奇数位于数组的前半部分，
 *           所有偶数位于数组的后半部分。要求时间复杂度为O(n)。
    解法：快速排序思想
******************************************************************************/
#include <stdio.h>

void paritySort(int a[], int len)
{
    int left = 0;
    int right = len - 1;
    int tmp;

    while (left < right)
    {
        while ((left < right) && (1 == a[left] % 2))
            left++;
        while((left < right) && (0 == a[right] % 2))
            right--;
        if (left < right)
        {
            tmp = a[left];
            a[left] = a[right];
            a[right] = tmp;

            left++;
            right--;
        }
    }
}

int main()
{
    int a[10] = {1,4,8,5,7,6,9,10,2,3};

    paritySort(a, 10);
    for (int i = 0; i < 10; i++)
    {
        printf("%d ",a[i]);
    }
    printf("\n");
    return 0;
}
