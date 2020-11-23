/******************************************************************************
 *  题目说明：现有n个红白蓝三种不同颜色的小球，乱序排列在一起，请通过两两交换任意两个球，
 *           使得从左至右，依次是一些红球、一些白球、一些蓝球。
    解法：这个问题和奇偶排序的问题差不多，都用到快速排序的思想
          假设红白蓝球分别用0，1，2表示
          需要用到三个指针：一个前指针begin，一个中指针current，一个后指针end，
          current指针遍历整个数组序列，当
            current指针所指元素为0时，与begin指针所指的元素交换，而后current++，begin++ ；
            current指针所指元素为1时，不做任何交换（即球不动），而后current++ ；
            current指针所指元素为2时，与end指针所指的元素交换，而后，current指针不动，end-- 
******************************************************************************/
#include <stdio.h>

static void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void DutchFlag(int a[], int len)
{
    int *begin = a;
    int *current = a;
    int *end = a + len -1;

    while (current <= end)
    {
        if (*current == 0)
        {
            swap(current, begin);
            begin++;
            current++;
        }
        else if (*current == 2)
        {
            swap(current, end);
            end--;
        }
        else
        {
            current++;
        }
    }
}

int main()
{
    int a[10] = {0,1,2,2,1,2,0,1,0,0};

    DutchFlag(a, 10);
    for (int i = 0; i < 10; i++)
    {
        printf("%d ",a[i]);
    }
    printf("\n");
    
    return 0;
}
