/******************************************************************************
 *  题目说明：给定一个数组，选择两个下标i和j,在满足a[i]<a[j]的前提下，使得差值j-i尽可能大
 *  解题思路一：蛮力法，时间复杂度：O(n^2)
 *  解题思路二：使用数组b[]来记录数组a的下标，b[0]表示a[0]中的数据的原始下标。对数组a排序，
 *             这时数组b会跟着数组a变动，求下标的最大差值变成了在i<j,求数组b[j]-b[i]的最大
 *             值问题，这个问题参考./../16.扩展_数组的最大差值
 *             排序的时间复杂度是O(nlogn),求数组最大差值的时间复杂度是O(n)
 *             所以，时间复杂度是：O(nlogn)，空间复杂度：O(n)
 *             注意：当数组a有重复数字的时候，因为条件是a[i]<a[j]，所以必须把下标大的
 *                   排在前面，但是使用的快速排序是不稳定的，无法保证在相等的情况下下标
 *                  大的排在前面，所以，我们在使用数组b的时候要把这种情况排除。
 *                   如果题目的条件是a[i]<=a[j]的时候就不用考虑排序稳定性问题
 *  解题思路三：从左向右扫描一遍，记录每个索引左边的最小值（包括自己），leftMin[0..n-1]
 *             从右向左扫描一遍，记录每个索引右边的最大值（包括自己），rightMax[0..n-1]
 *             要注意的是：
 *               对于leftMin[i]，其左边的leftMin[0..i-1]都大于等于leftMin[i]，其右边的left[i+1..n-1]都小于leftMin[i]
 *              对于rightMax[j]，其左边的rightMax[0..j-1]都大于等于rightMax[j]，其右边的rightMax[j+1..n-1]都小于rightMax[j]
 *　           对于leftMin[i] 和rightMax[j]
 *　             如果leftMin[i]<rightMax[j]，说明j的右边还可能存在值使rightMax>leftMin，记录当前的j-i，使++j
 *　             否则leftMin[i]>=rightMax[j], 则i的左边肯定都比rightMax[j]大，要增大++i，
 *             时间复杂度：O(n)，空间复杂度：O(n)
 *        参考： https://www.cnblogs.com/xiongqiangcs/p/3893447.html
******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// 快速排序
static void quick_sort(int a[], int b[],int l, int r)
{
   int i, j;
   int t1,t2;
   
   if(l < r)
   {
      i = l;
      j = r;
      t1 = a[i];
      t2 = b[i];
      
      while(i < j)
      {
         while ((i < j) && (a[j] > t1))//从右往左找到小于x的数
         {
            j--;
         }
         if (i < j)
         {
            a[i] = a[j];
            b[i] = b[j];
            i++;
         }
         
         while((i < j) && (a[i] < t1)) //从左往右找到大于x的数 
         {
            i++;
         }
         if (i < j)
         {
            a[j] = a[i];
            b[j] = b[i];
            j--;
         }
      }
      a[i] = t1;            //i = j的时候，将x填入中间位置 
      b[i] = t2;
      quick_sort(a,b,l,i-1); //对左边排序
      quick_sort(a,b,i+1,r);
   }
}

static int arrayMaxDiff(int a[], int len, int b[])
{
    int i,maxDiff, minValue;
    int minIndex;  // minValue对应的下标

    if (NULL == a || len < 2)
    {
        printf("ERROR!! input parameter error\n");
        return 0;
    }
    maxDiff = a[1] - a[0];
    minValue = (a[0] < a[1])? a[0] : a[1];
    minIndex = (a[0] < a[1])? 0 : 1;

    for (i = 2; i < len; i++)
    {
        if ((a[i] - minValue) > maxDiff)
        {
            if (b[i] != b[minIndex])  
                maxDiff = a[i] - minValue;
        }
        if (a[i] < minValue)
        {
            minValue = a[i];
            minIndex = i;
        }
    }
    return maxDiff;
}

int indexMaxDiff_2(int a[], int len)
{
    int *b;
    int i;
    int diff;

    if (NULL == a || len < 2)
    {
        printf("ERROR!! input parameter error\n");
        return 0;
    }

    b = (int *) malloc(len *sizeof(int));
    if (NULL == b)
    {
        printf("[%s],line:%d,malloc fail\n",__FUNCTION__,__LINE__);
        return 0;
    }
    for (i = 0; i < len; i++)
    {
        b[i] = i;
    }
    quick_sort(a,b,0,len-1);
    diff = arrayMaxDiff(b, len,a);

    free(b);

    return diff;
}

int indexMaxDiff_3(int a[], int len)
{
    int *leftMin, *rightMax;
    int diff;
    int i,j;

    if (NULL == a || len < 2)
    {
        printf("ERROR!! input parameter error\n");
        return 0;
    }
    leftMin = (int *) malloc(len * sizeof(int));
    if (NULL == leftMin)
    {
        printf("[%s],line:%d,malloc fail\n",__FUNCTION__,__LINE__);
        return 0;
    }
    rightMax = (int *) malloc(len * sizeof(int));
    if (NULL == rightMax)
    {
        free(leftMin);
        printf("[%s],line:%d,malloc fail\n",__FUNCTION__,__LINE__);
        return 0;
    }

    leftMin[0] = a[0];
    for (i = 1; i < len; i++)
    {
        if (a[i] < leftMin[i-1])
            leftMin[i] = a[i];
        else
            leftMin[i] = leftMin[i-1];
    }
    rightMax[len-1] = a[len-1];
    for (i = len - 2; i >= 0; i--)
    {
        rightMax[i] = (a[i] > rightMax[i+1])? a[i] : rightMax[i+1];
    }

    diff = -1;
    for (i = 0, j=0; i < len && j < len;)
    {
        if (leftMin[i] < rightMax[j])
        {
            if (diff < (j - i))
            {
                diff = j - i;
            }
            j++;
        }
        else
            i++;
    }

    free(leftMin);
    free(rightMax);

    return diff;
}

int main()
{
    int a[8] = {5,3,7,2,6,3,2,1};
    int diff1, diff2;

    diff2 = indexMaxDiff_3(a, 8);
    diff1 = indexMaxDiff_2(a, 8);

    if (diff1 != diff2)
        printf("ERROR!! diff1=%d,diff2=%d\n",diff1,diff2);
    else
        printf("index max difference:%d\n",diff1);
}
