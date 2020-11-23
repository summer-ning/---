/******************************************************************************
 *  题目说明：在给定数组中找出其和最接近0的两个值。
    解法：1. 排序，使用快速排序，时间复杂度： O(nlogn)
         2. 设置两个游标，一个指向第一个数，另一个指向最后一个数，之后进行如下操作：
            把游标处的两个数相加取绝对值，与记录当前已经得到的最小绝对值比较，小则记录。
            之后对游标处的数的绝对值进行比较，移动指向数字绝对值较大的游标(如果是左面的
            游标指向的数字绝对值大，则向右移动，否则右面的游标向左移动)。循环此步骤，
            直至找到最小绝对值0或者游标相遇。时间复杂度：O(n)
        所以整体的时间复杂度为：O(nlogn)
    参考：https://blog.csdn.net/martin_liang/article/details/37914869
******************************************************************************/
#include <stdio.h>

#define  ABS(a)     ((a) > 0 ? (a) : -(a))

// 快速排序
static void quick_sort(int a[], int l, int r)
{
   int i, j;
   int t;
   
   if(l < r)
   {
      i = l;
      j = r;
      t = a[i];
      
      while(i < j)
      {
         while ((i < j) && (a[j] > t))//从右往左找到小于x的数
         {
            j--;
         }
         if (i < j)
         {
            a[i++] = a[j];
         }
         
         while((i < j) && (a[i] < t)) //从左往右找到大于x的数 
         {
            i++;
         }
         if (i < j)
         {
            a[j--] = a[i];
         }
      }
      a[i] = t;            //i = j的时候，将x填入中间位置 
      quick_sort(a,l,i-1); //对左边排序
      quick_sort(a,i+1,r);
   }
}

void closeToZeroNumber(int a[], int n)
{
    int *p = a;
    int *q = a + n -1;
    int closeZero, tmp;
    int value1, value2;

    quick_sort(a, 0, n-1);
    value1 = *p; value2 = *q;
    closeZero = value1 + value2;
    while(p < q)
    {
        tmp = *p + *q;
        if (ABS(tmp) < ABS(closeZero))
        {
            value1 = *p;
            value2 = *q;
            closeZero = tmp;
        }
        if (ABS(*p) > ABS(*q))
        {
            p++;
        }
        else
        {
            q--;
        }
    }
    printf("close to 0 number:%d,%d\n",value1,value2);
}

#if 0
int main()
{
    int a[] = {5,-3,7,2,6,9,3};

    closeToZeroNumber(a, sizeof(a)/sizeof(a[0]));

    return 0;
}
#endif
