/******************************************************************************
 *  题目说明：在一个数组里，有三个数只出现一次，其他数都是出现两次的，找出这三个只
             出现一次的数
    解法：1.先找到一个只出现一次的数
            首先，原数组的个数一定是奇数。所以，按照某一位是1还是0分为两个数组：分成两个
            数组一个是奇数个元素，一个是偶数个元素 ，相同的数字一定会被分到同一组里。
            分出来的两个数组各自异或的结果，奇数个数的数组肯定不为0（包含1个或3个不重复
            的元素）。偶数个数的数组可能为0（不包含不重复的元素），可能不为0（包含2个不
            重复的元素）。如果偶数个数的数组异或结果为0，表示三个不重复的数都被分到奇数组中了，
            如果偶数个数的数组异或结果不为0，表示偶数个数的数组里包含2个出现一次的数，
            那么奇数个数的数组中只包含一个不重复的数，由于相同元素异或为0，相抵消，奇数
            个数的数组所有数的异或结果就为那个不重复的数。
         2. 剩下的问题就是在数组中找到啷个只出现一次的问题，可以参考 two.c 中的分析
******************************************************************************/
#include <stdio.h>

void findThreeNumber(int a[], int len, int *num1, int *num2, int *num3)
{
    int result,result0,result1;  // 异或结果
    int count0,count1;
    int i,j;
    int pos;

    if (0 == (len % 2))  // 数组元素个数必须是奇数
    {
        printf("error,the number of array elements is even\n");
        return;
    }

    // 1. 找到第一个只出现一次的数字
    for (i = 0; i < sizeof(int); i++)  // 按位分组
    {
        result0 = result1 = 0;
        count0 = count1 = 0;
        for (j = 0; j < len; j++)
        {
            if (a[j] & (0x01 << i))  // 对第i位为1的数字异或
            {
                result1 ^= a[j];
                count1++;
            }
            else
            {
                result0 ^= a[j];
                count0++;
            }            
        }
        if (count0 % 2)   // i位为0的数组元素个数是奇数
        {
            if (result1 != 0)  // i位为1的数组元素异或结果不为0
            {
                *num1 = result0;
                break;
            }
        }
        else
        {
            if (result0 != 0)
            {
                *num1 = result1;
                break;
            }
        } 
    }
    if (sizeof(int) == i)  // 说明数组中只有一个数字只出现了一次
    {
        printf("input array error1，the array has only one distinct number !!!\n");
        return;
    }

    // 2.查找两个只出现一次的数字
    result = 0;
    for (i = 0; i < len; i++)
    {
        result ^= a[i];
    }
    result ^= *num1; // 让 num1 在数组中也出现两次，那么，相当于数组中只有两个只出现一次的数组
    if (result == 0)
    {
        printf("input array error2,the array has only one distinct number !!!\n");
        return;
    }
    for (i = 0; i < sizeof(int); i++)
    {
        if (result & (0x01 << i))
            break;
    }
    pos = i;

    *num2 = *num3 = 0;
    for (i = 0; i < len; i++)
    {
        if (a[i] & (0x01 << pos))
        {
            *num2 ^= a[i];
        }
        else
        {
            *num3 ^= a[i];
        }
    }
    // 和 *num1异或才相当于只有两个不同
    if (*num1 & (0x01 << pos))
        *num2 ^= *num1;
    else
        *num3 ^= *num1;
}


int main()
{
    int tst[] = {1,2,3,4,5,6,6,7,0,1,2,3,4,5,8};
    int num1, num2, num3;

    findThreeNumber(tst,sizeof(tst)/sizeof(tst[0]),&num1, &num2, &num3);
    printf("three number:%d,%d,%d\n",num1,num2,num3);
    return 0;
}