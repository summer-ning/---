/******************************************************************************
 *  题目说明：有n个正实数，按从小从大的顺序升序排列，现给定一个实数m,请从数组中
             找出若干个数，满足这若干个数的和与K最为接近。
    解法：01背包问题
         考虑是否取当前数的策略, 问题可以转化为取当前值和不取当前值的区别.
            如果取当前值, 算法为 sumToK(k, sum+a[i]).
            如果不取当前值, 算法为sumToK(k, sum).
        如果只是求最接近的和，那么不需要排序，如果还要求出最少或最多数字组成的最接近的
        序列，那么需要排序
******************************************************************************/
#include <stdio.h>

#include "stack.h"

#define  ABS(a)     ((a) > 0 ? (a) : -(a))

static bool copyStack(LinkStack S1, LinkStack S2)
{
    SElemType e;
    StackNode *p;

    ClearStack(S1);

    p = S2->next;
    while(p)
    {
        Push(S1, p->data);
        p = p->next;
    }

    return true;
}


void sumToK(int a[], int len, int index, int k, int currSum, int *minDiff, 
                        LinkStack Stack, LinkStack minStack)
{
    int tmp;

    if (ABS(k-currSum) < *minDiff)
    {
        *minDiff = ABS(k-currSum);
        copyStack(minStack, Stack);
    }
    if (index >= len)
        return;
    Push(Stack, a[index]);
    sumToK(a, len, index + 1, k, currSum + a[index], minDiff, Stack, minStack);
    Pop(Stack, &tmp);
    sumToK(a, len, index + 1, k, currSum, minDiff, Stack, minStack);
}

void sumClosestToValue(int a[], int len, int k)
{
    LinkStack tmpStack, minStack;
    int minDiff = k;
    int val,sum = 0;

    InitStack(&tmpStack);
    InitStack(&minStack);

    sumToK(a, len, 0, k, 0, &minDiff, tmpStack, minStack);

    printf("cloasest %d:\n",k);
    while(Pop(minStack, &val))
    {
        printf("%d ",val);
        sum += val;
    }
    printf("\nsum:%d\n",sum);
}

int main()
{
    int a[10] = {5,11,10,27,43,21,32, 23};
    
    sumClosestToValue(a, 9, 99);
    return 0;
}
