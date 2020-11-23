/******************************************************************************
 *  题目说明：从一列数中筛除尽可能少的数使得从左往右看，这些数是从小到大再从大到小的。
 *  解题思路： 从左向右查找递增序列，假设以i为结尾的递增序列长度为leftToright[i],那么，如果
 *            array[i+1] > array[i],那么，leftToright[i+1]=leftToright[i]+1,否则，
 *            leftToright[i+1]=1。注意,leftToright[i]=1
 *            同理，从右向左计算以i为结束的递增序列，
 *            然后在计算和的最大值,注意，在计算和的时候，不要考虑leftToright[i]=1或者
 *                rightToLeft[i]=1的情况，有一个等于1，表示序列是递增或递减的
 *            时间复杂度：O(n),空间复杂度：O(n)
******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int DoubleLIS(int a[], int len)
{
    int *leftToright, *rightToleft;
    int maxLen = 0;  //记录总共的(上升+下降)最长子序列长度
    int index;
    int i;

    leftToright = (int *) malloc(len * sizeof(int));
    if (leftToright == NULL)
    {
        printf("ERROR!! [%s],line:%d,malloc fail",__FUNCTION__,__LINE__);
        return -1;
    }
    rightToleft = (int *) malloc(len * sizeof(int));
    if (rightToleft == NULL)
    {
        printf("ERROR!! [%s],line:%d,malloc fail",__FUNCTION__,__LINE__);
        free(leftToright);
        return -1;
    }

    leftToright[0] = 1;
    for (i = 1; i < len; i++)
    {
        if (a[i] > a[i-1])
            leftToright[i] = leftToright[i-1] + 1;
        else
            leftToright[i] = 1;
    }
    rightToleft[len-1] = 1;
    for (i = len -2; i >= 0; i--)
    {
        if (a[i] > a[i+1])
            rightToleft[i] = rightToleft[i+1] + 1;
        else
            rightToleft[i] = 1;
    }
    for (i = 0; i < len; i++)
    {
        if (leftToright[i] != 1 && rightToleft[i] != 1)
        {
            if (maxLen < (leftToright[i] + rightToleft[i] - 1))
            {
                maxLen = leftToright[i] + rightToleft[i] -1;
                index = i;
            }
        }
    }
#if 1
    for (i = index-leftToright[index]+1; i < index+rightToleft[index]; i++)
    {
        printf("%d ",a[i]);
    }
    printf("\nmaxLen=%d\n",maxLen);
#endif
    free(leftToright);
    free(rightToleft);
    return maxLen;
}

int main()
{
    int a[10] = {1,5,3,4,6,5,3,1,2,4};

    DoubleLIS(a, 10);
    return 0;
}
