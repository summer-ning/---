/******************************************************************************
 *  题目说明：在给定数组中找出其和最接近K的两个值。
    解法：首先，对数组排序。使用快速排序，时间复杂度：O(nlogn)
          遍历数组中的每一个数值a[i],用二分查找找到最接近 K-a[i]的值。二分查找的时间
          复杂度是O(logn)，需要查找n次，所以是：O(nlogn)
          所以总的时间复杂度是：O(nlogn)
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

/**
 * @函数名称: sumCloseToCertainNumber
 * @功能描述: 在给定数组中找出其和最接近K的两个值。
 * @输入参数: 
 *      a: 数组a
 *      len：数组的长度
 *      k: 两数和
 * @输出参数: void
 * @返回值: void
 * @其他说明: 找到两个数，直接打印出来了
 */
void sumCloseToCertainNumber(int a[], int len, int k)
{
    int i;
    int closest, index,searchValue;
    int value1, value2;

    quick_sort(a, 0, len-1);

    value1 = a[0];
    value2 = a[1];
    for (i = 0; i < (len - 1); i++)
    {
        searchClosestValue(&a[i+1], len - i - 1, k - a[i], &closest);
        if (ABS(value1+value2-k) > ABS(a[i] + closest - k))
        {
            value1 = a[i];
            value2 = closest;
        }
    }
    printf("k=%d,value1=%d,value2=%d,sum=%d\n",k,value1,value2,value1+value2);
}

int main()
{
    int a[] = {1,-3,-5,-7,10,14,25};
    int closest, index;

    sumCloseToCertainNumber(a,7, 0);

    return 0;
}

