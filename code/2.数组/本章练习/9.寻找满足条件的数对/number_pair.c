/******************************************************************************
 *  题目说明：给定一个数组，输出满足2a=b(a和b代表数组中的数）的数对，要求时间复杂度尽量低。
    解法：使用哈希表
          时间复杂度O(n)  空间复杂度：O(n)
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define  ARRAY_MAX_VALUE        (99)  // 数组值的最大值

void findSequence(int a[], int len)
{
    int i;
    int *hashTable = (int *)malloc((ARRAY_MAX_VALUE+1) * sizeof(int));

    if (NULL == hashTable)
    {
        printf("[%s],line:%d,malloc fail\n",__FUNCTION__,__LINE__);
        return;
    }
    // 创建hash表
    memset(hashTable, 0, ARRAY_MAX_VALUE * sizeof(int));
    for (i = 0; i < len; i++)
    {
        hashTable[a[i]] = 1;
    }

    // 查找满足2a=b的数对
    for (i = 0; i < len; i++)
    {
        int b = 2 * a[i];
        if (b > ARRAY_MAX_VALUE)
        {
            // a[i]的最大值小于 ARRAY_MAX_VALUE，所以满足条件的b一定小于ARRAY_MAX_VALUE
            continue;
        }
        if (hashTable[b] == 1)
        {
            printf("\t(%d,%d)\n",a[i],b);
            hashTable[b] = 0;  // 去重
        }
    }
    free(hashTable);
}

int main()
{
    int a[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};

    findSequence(a, sizeof(a)/sizeof(a[0]));

    return 0;
}