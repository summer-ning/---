/******************************************************************************
 *  题目说明：有20个数组，每个数组里面有500个数，降序排列，每个数是32位的无符号
             整型数，请求出这10000个数字中最大的500个。
    解法一：对所有的数组进行归并
            先对第1和第2个数组归并，得到最大的500个数，然后再把结果和第三个数组归并，
            一直到第20个数组
    解法二： 使用堆
            因为20个数组是有序的，所以最大值肯定在20个数组的第一个元素中，第二大的元素
            在剩下19个或者是第一大元素的后一个元素中
            我们取每个数组的第一个元素创建一个大顶堆，堆的根节点就是最大的元素，取出最大
            元素，然后加入这个元素所在数组的下一个元素，重新进行堆排序，根节点就是第二大
            元素，一次类推，取出500个元素。时间复杂度：500*log(20)
******************************************************************************/
#include <stdio.h>
#include <string.h>

// 便于测试改小一些，500个数改为5个，20个数组给为5个
#define  ARRAY_LEN      (20) 
#define  ARRAY_NUM      (5)

typedef struct{
    int arrayNum; // 数组编号(数字来自哪个数组)，0-19
    int index;    // 数字在数组中的下标，0-499
    unsigned int value;
}HEAP_NODE_T;

/**
 * @函数名称: mergeArray
 * @功能描述: 归并两个有序数组（降序排列）
 * @输入参数: 
 *      array1：第一个数组
 *      array2: 第二个数组
 *      n:      输入数组和输出数组的长度
 * @输出参数: 
 *      merge: 归并后的数组
 * @返回值: void
 * @其他说明: 
 */ 
void mergeArray(unsigned int array1[], unsigned int array2[], unsigned int merge[], int n)
{
    int i,j,k;

    i = j = k = 0;
    while (i < n && j < n && k < n)
    {
        if (array1[i] > array2[j])
        {
            merge[k++] = array1[i++];
        }
        else
        {
            merge[k++] = array2[j++];
        }
    }
}

// 方法一，归并
void findMax500Number(unsigned int a[ARRAY_NUM][ARRAY_LEN], unsigned int max[])
{
    unsigned int merge[2][ARRAY_LEN];  // 归并后的数组，因为要对此归并，所以要多申请一块内存
    int i, k = 0;

    mergeArray(a[0],a[1],merge[k],ARRAY_LEN);
    for (i = 2; i < ARRAY_NUM; i++)
    {
        mergeArray(a[i],merge[k],merge[(k+1)%2],ARRAY_LEN);
        k = (k + 1) % 2;
    }
    memcpy(max, merge[k], ARRAY_LEN * sizeof(unsigned int));
}

/**
  * 当a[i,...,n-1]是堆，改变a[i](把a[i]看成根节点)，使重新成为一个堆
  * @param  i: 堆的根节点
            n: 堆的右边界
  */
void heapAdjust_up(HEAP_NODE_T a[], int i, int n)
{
    int father = i;
    int child = 2 * father + 1; // 左子节点
    HEAP_NODE_T tmp;

    tmp = a[father];
    while (child < n)
    {
        if ((child + 1) < n)  // 存在右子节点
        {
            if (a[child + 1].value > a[child].value)
                child += 1;
        }
        if (a[child].value > tmp.value) // 子节点大于父节点,交换
        {
            a[father]= a[child];
            // a[child] = tmp;

            //子节点已经改变，把当前的子节点作为父节点，继续上面的过程
            father = child;
            child = father * 2 + 1;
        }
        else
        {
            break;
        }
    }
    a[father] = tmp;
}

/**
 * @函数名称: findMax500Number_heap
 * @功能描述: 寻找最大的500个数
 * @输入参数: 
 *      a: 由n个长度为ARRAY_LEN的一维数组组成的二维数组
 * @输出参数: 
 *      max:二维数组中最大的ARRAY_LEN个数
 * @返回值: void
 * @其他说明: 使用解法二，堆排序，时间复杂度：ARRAY_LEN*log(n)
 */
void findMax500Number_heap(unsigned int a[ARRAY_NUM][ARRAY_LEN], unsigned int max[])
{
    HEAP_NODE_T heap[ARRAY_NUM];
    int i;
    int heapLen = ARRAY_NUM;
    int count = 0;

    // 1.创建堆
    for (i = 0; i < heapLen; i++)
    {
        heap[i].arrayNum = i;
        heap[i].index = 0;
        heap[i].value = a[i][0];
    }
    // 数组是从0开始计数，所以左子节点为2*i+1，右子节点为2*i+2
    for (i = heapLen/2 -1; i >= 0; i--)
    {
        heapAdjust_up(heap, i, heapLen);
    }

    // 2.取出堆顶元素，然后加入新元素，堆重新排序
    for (i = 0; i < ARRAY_LEN; i++)
    {
        max[i] = heap[0].value;
        heap[0].value = a[heap[0].arrayNum][heap[0].index + 1];
        heap[0].index += 1;
        heapAdjust_up(heap, 0, heapLen);
    }
}

int main()
{
    unsigned int tst[ARRAY_NUM][ARRAY_LEN];
    unsigned int max1[ARRAY_LEN], max2[ARRAY_LEN];
    int i, j;

    // 创建测试数组
    for (i = 0; i < ARRAY_NUM; i++)
    {
        tst[i][0] = 10000 - i;
        for (j = 1; j < ARRAY_LEN; j++)
        {
            tst[i][j] = tst[i][j-1] - i - 1;
        }
    }

    // 用两种方式验证算法是否正确
    findMax500Number(tst,max1);
    findMax500Number_heap(tst,max2);
    for (i = 0; i < ARRAY_LEN; i++)
    {
        if (max1[i] != max2[i])
        {
            printf("ERROR!!! max1 != max2\n");
            break;
        }
    }
    if (i != ARRAY_LEN)
    {
        printf("max2:");
        for (i = 0; i < ARRAY_LEN; i++)
        {
            printf("%d ",max2[i]);
        }
        printf("\n");
    }
    printf("max1:");
    for (i = 0; i < ARRAY_LEN; i++)
    {
        printf("%d ",max1[i]);
    }
    printf("\n");

    return 0;
}