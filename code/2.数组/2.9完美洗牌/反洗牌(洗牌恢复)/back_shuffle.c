/******************************************************************************
 *  题目说明：既然完美洗牌问题是给定输入：a1,a2,a3,……aN,b1,b2,b3,……bN，要求输出：
 *           b1,a1,b2,a2,……bN,aN；那么有无考虑过它的逆问题：
 *           即给定b1,a1,b2,a2,……bN,aN,，要求输出a1,a2,a3,……aN,b1,b2,b3,……bN ？
    解法：这是洗牌的逆运算，洗牌算法的步骤：
          (1). 查找 2m= 3^k-1
          (2). 对[m+1,n+m]左移n-m位
          (3). 位置在i的数字移动到(2*i)%(2m+1)
          (4). 对剩下的数字继续洗牌
         所以逆运算就是：
          (1). 查找 2m= 3^k-1
          (2). 对剩下的数字继续逆洗牌
          (3). (2*i)%(n+1)移动到i
               如果j =(2*i)%(n+1),那么：
                    如果 j是偶数，i = j/2  
                    如果 j是奇数，i = (j+2m+1)/2
               注意：上面提交的i和j的范围是从1-n，但是代码中数组是从0-n-1，
          (4). 对[m+1,n+m]右移n-m位
******************************************************************************/
#include <stdio.h>
#include <string.h>

static void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}


// 翻转[from,to]。 abc -> cba
static void Reverse(int a[], int from, int to)
{
    int t;
    while (from < to)
    {
        t = a[from];
        a[from++] = a[to];
        a[to--] = t;
    }
}

static void cycleLeader(int *a, int from, int mod)
{
    int next = ((from + 1) % 2)? (from + 1 + mod) / 2 - 1 : (from + 1)/2 - 1;

    while(next != from)
    {
        swap(&a[next], &a[from]);
        next = ((next + 1) % 2)? (next + 1 + mod) / 2 - 1 : (next + 1)/2 - 1;
    }
}

/**
 * @函数名称: leftRotate
 * @功能描述: 循环左移
 * @输入参数: 
 *      a: 数组a
 *      start: 数组起始下标
 *      end: 数组结束下标
 *      n : 移动的长度
 * @输出参数: 
 *      a:数组a
 * @返回值: void
 * @其他说明: abc def->cba fed->defabc
 */
static void leftRotate(int a[], int start, int end, int n)
{
    n = n % (end - start + 1);

    Reverse(a, start, start + n - 1);
    Reverse(a, start + n, end);
    Reverse(a, start, end);
}

/**
 * @函数名称: rightRotate
 * @功能描述: 循环右移
 * @输入参数: 
 *      a: 数组a
 *      start: 数组起始下标
 *      end: 数组结束下标
 *      n : 移动的长度
 * @输出参数: 
 *      a:数组a
 * @返回值: void
 * @其他说明: abc def->cba fed->defabc
 */
static void rightRotate(int a[], int start, int end, int n)
{
    n = n % (end - start + 1);

    Reverse(a, start, end - n);
    Reverse(a, end - n + 1, end);
    Reverse(a, start, end);
}

/**
 * @函数名称: backPerfectShuttle
 * @功能描述: 恢复洗牌
 * @输入参数: 
 *      a: 数组a
 *      n: 数组的长度是2n
 * @输出参数: 
 *      a: 洗牌后的数组
 * @返回值: void
 * @其他说明: 
 *      输入：b1,a1,b2,a2,...,bn,an
 *      输出：a1,a2,...,an,b1,b2,...,bn
 */
void backPerfectShuttle(int a[], int n)
{
    int len = 2 * n;
    int i,m,k;
    int start;

    if (n < 0 || NULL == a)
    {
        printf("ERROR!! input parameter error\n");
        return;
    }
    // step 1 找到 2 m = 3^k - 1 
    m = 1;
    k = 0;
    while((m-1) <= len)
    {
        k++;
        m *= 3;
    }
    m = (m / 3 - 1) / 2;
    k--;

    // step4:最后剩余进行递归操作
    if (m != n)
	    backPerfectShuttle(&a[2*m],n-m);

    // step 2: 以 3^i -1(i= 0,1,...,k-1)为圈的起始位置，循环移动
    start = 1;
    while (k--)
    {
        cycleLeader(a, start - 1, 2*m+1);
        start *= 3;
    }

    // step 3: 把a[m+1,..,n,n+1,...,n + m]循环左移n-m（或者右移m）
    if (m != n)
    {
        // 注意：算法的下标是从1开始，但是实际存储是从0开始
        rightRotate(a, m, n+m-1, n-m); 
    }
}

#define  N      (16)
int main()
{
    int a[N] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};

    backPerfectShuttle(a, N/2);
    for (int i = 0; i < N; i++)
    {
        printf("%d ",a[i]);
    }
    printf("\n");
}