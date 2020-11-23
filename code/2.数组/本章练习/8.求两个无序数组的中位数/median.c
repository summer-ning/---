/******************************************************************************
 *  题目说明：给定两个无序数组分别叫A和B,长度分别是m和n,求这两个无序数组的中位数，要
 *           求时间复杂度为O(m+n),空间复杂度为0(1).
    解法：快速选择算法（求第K小的数）
          快速选择算法类似于快速排序，使用分治思想。平均时间复杂度为O(n)，但是最差情
          况是O(n^2)。
          两个数组和一个数组本质是一样的，只不过当i >n的时候，使用b数组的值
******************************************************************************/
#include <stdio.h>


/**
 * @函数名称: quickSelection
 * @功能描述: 找到一个无序数组中第K小的树
 * @返回值:   第k小的数值
 * @其他说明: 快速选择算法，分治思想
 *            注意：数组的顺序会被改变         
 */
int quickSelection(int a[], int start, int end, int k)
{
    int i, j;
    int t;

    if (start >= end)
        return 0;

    i = start;
    j = end;
    t = a[i];
    while (i < j)
    {
        while((i < j) && (a[j] > t)) //从右往左找到小于t的数
        {
            j--;
        }
        if (i < j)
            a[i] = a[j];
        
        while(i < j && a[i] < t)   //从左往右找到大于t的数 
        {
            i++;
        }
        if (i < j)
            a[j] = a[i];
    }
    a[i] = t;
    if (i < k)
    {
        return quickSelection(a, i+1, end, k);
    }
    else if (i > k)
    {
        return quickSelection(a, start, i-1, k);
    }
    else
    {
        return a[i];
    }
}

/**
 * @函数名称: quickSearchMedian
 * @功能描述: 在两个无序数组中找到第K小的数
 * @输入参数: 
         a: 第一个无序数组
         b: 第二个无序数组
         a_len: 数组a的长度
         start: 开始下标，下标的范围[0, a_len+b_len-1]
         end: 结束下标，下标的范围[0, a_len+b_len-1]
         k:  排序序号
 * @输出参数: 
 * @返回值: 第K小的值
 * @其他说明: 
 */
int quickSearchMedian(int a[], int b[], int a_len, int start, int end, int k)
{
    int i, j;
    int t, x;

    if (start >= end)
        return 0;

    i = start;
    j = end;
    if (i >= a_len)
    {
        t = b[i - a_len];
    }
    else
    {
        t = a[i];
    }

    while(i < j)
    {
        while(i < j) //从右往左找到小于t的数
        {
            if (j < a_len)
                x = a[j];
            else
                x = b[j - a_len];
            if (x > t)
                j--;
            else
                break;
        }
        if (i < j)
        {
            if (i >= a_len)
            {
                b[i - a_len] = x;
            }
            else
            {
                a[i] = x;
            }
        }
        
        while(i < j)   //从左往右找到大于t的数 
        {
            if (i < a_len)
                x = a[i];
            else
                x = b[i - a_len];
            if (x < t)
                i++;
            else
                break;
        }
        if (i < j)
        {
            if (j < a_len)
            {
                a[j] = x;
            }
            else
            {
                b[j - a_len] = x;
            }
        }
    }
    if (i < a_len)
        a[i] = t;
    else
        b[i - a_len] = t;
    if (i < k)
    {
        return quickSearchMedian(a, b, a_len, i+1, end, k);
    }
    else if (i > k)
    {
        return quickSearchMedian(a, b, a_len, start, i-1, k);
    }
    else
    {
        return t;
    }
}


int main()
{
    int a[5] = {8,2,4,6,5};
    int b[6] = {3,7,9,1,10};
    int median;

    median = quickSearchMedian(a,b,5,0,9,5);
    printf("median = %d\n",median);

    return 0;
}