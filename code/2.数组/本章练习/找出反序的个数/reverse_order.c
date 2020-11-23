/******************************************************************************
 *  题目说明：给定一整型数组，若数组中某个下标值大的元素值小于某个下标值比它小的元素值，
 *           称这是一个反序。即：数组a[]; 对于i < j 且 a[i] > a[j],则称这是一个反序。
             给定一个数组，要求写一个函数，计算出这个数组里所有反序的个数。
    解法：   利用归并排序，归并排序的核心算法中，合并两个前后两个序列的时候，可以统计
            这两个前后序列之间的逆序对，再加上每个序列的逆序对，就是一共的逆序对。
            归并排序的实现有两种，递归法和迭代法
    参考：  https://blog.csdn.net/luno1/article/details/8001892
******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// 蛮力法计算反序对，用于结果的验证
int calculateReversePair_bruteFarce(int a[], int len)
{
    int i,j;
    int count = 0;

    for (i = 0; i < len; i++)
    {
        for (j = i+1; j < len; j++)
        {
            if (a[i] > a[j])
                count++;
        }
    }
    return count;
}

/**
 * @函数名称: calculateReversePair
 * @功能描述: 计算数组中所有的反序对个数
 * @输入参数: 
 *      arr: 数组
 *      len: 数组长度
 * @输出参数: 
 *      arr: 排序后的数组
 * @返回值: 反序对个数
 * @其他说明: 使用归并排序，迭代法实现
 *           这个函数不仅计算了反序数，还对数组进行了排序   
 */
int calculateReversePair(int arr[], int len)
{
    int *a = arr;
    int *b = (int *)malloc(len *sizeof(int));
    int *tmp;
    int k = 0;
    int seg;
    int start,start1,start2,end1,end2;
    int count = 0;

    if (NULL == b)
    {
        printf("[%s],line:%d,malloc fail\n",__FUNCTION__,__LINE__);
        return 0;
    }

    for (seg = 1; seg < len; seg += seg)
    {
        for (start = 0; start < len; start += 2 * seg)
        {
            int low = start;
            int mid = (start+seg) < len? (start+seg) : len;
            int high = (start+2*seg) < len? (start+2*seg) : len;

            start1 = low; end1 = mid;
            start2 = mid; end2 = high;
            k = low;
            while(start1 < end1 && start2 < end2)
            {
                if (a[start1] <= a[start2]) 
                    b[k++] = a[start1++];
                else
                {
                    b[k++] = a[start2++];
                    count += end1 - start1;
                }
            }
            while (start1 < end1)
                b[k++] = a[start1++];
            while (start2 < end2)
                b[k++] = a[start2++];
        }
        // 交换 a和 b,a始终存放源数列，b存放归并后的数列
        tmp = a;
        a = b;
        b = tmp; 
    }

    if (a != arr)
    {
        for (k = 0; k < len; k++)
            b[k] = a[k];
        b = a;
    }
    free(b);

    return count;
}


int main()
{
    int a[] = {1,2,3,5,1,2,6,8,5,9};
    int count1,count2;

    count1 = calculateReversePair_bruteFarce(a, sizeof(a)/sizeof(a[0]));
    count2 = calculateReversePair(a, sizeof(a)/sizeof(a[0]));
    if (count1 != count2)
    {
        printf("ERROR!!!,count1 !=  count2\n");
    }
    printf("count1=%d,count2=%d\n",count1,count2);
    return 0;
}
