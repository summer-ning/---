/******************************************************************************
 *  题目说明：a1,a2,a3,b1,b2,b3,c1,c2,c3 变成 c1,b1,a1,c2,b2,a2,c3,b3,a3
    解法：步骤：
          (1). 查找 3m= 7^k-1
          (2). 对[m+1,n+m]左移n-m位，
          (3). 对[2m+1,2n+m]左移2(n-m)位
          (4). 位置在i的数字移动到(3*i)%(3m+1)
          (4). 对剩下的数字继续洗牌
    参考：https://blog.csdn.net/juzihongle1/article/details/76563336
******************************************************************************/
#include <stdio.h>

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
    int t = a[from];
    int index = from;
    int next = (3 * from + 2) % mod; // 因为数组下标是从0开始，所以不是（2i）%mod

    while(next != from)
    {
        swap(&a[next], &a[from]);
        next = (3 * next + 2) % mod;
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
 * @函数名称: perfectShuttle
 * @功能描述: 完美洗牌算法
 * @输入参数: 
 *      a: 数组a
 *      n: 数组的长度是2n
 * @输出参数: 
 *      a: 洗牌后的数组
 * @返回值: void
 * @其他说明: 
 *      输入：a1,a2,...,an,b1,b2,...,bn
 *      输出：b1,a1,b2,a2,...,bn,an
 */
void threePerfectShuttle(int a[], int n)
{
    int len = 3 * n;
    int i,m,k;
    int start;

    if (n < 0 || NULL == a)
    {
        printf("ERROR!! input parameter error\n");
        return;
    }
    while (n > 1)
    {
        // step 1 找到 3 m = 7^k - 1 
        m = 1;
        k = 0;
        while((m-1) <= len)
        {
            k++;
            m *= 7;
        }
        m = (m / 7 - 1) / 3;
        k--;
        // step 2: 把a[m+1,..,n,n+1,...,n + m]循环左移n-m（或者右移m）
        if (m != n)
        {
            // 注意：算法的下标是从1开始，但是实际存储是从0开始
            leftRotate(a, m, n+m-1, n-m); 
        }

        // step 3: 把a[2m+1,..,2n,2n+1,...,2n + m]循环左移2(n-m)（或者右移m）
        if (m != n)
        {
            // 注意：算法的下标是从1开始，但是实际存储是从0开始
            leftRotate(a, 2*m,2* n+m-1, 2*(n-m)); 
        }
        // step 4: 以 3^i -1(i= 0,1,...,k-1)为圈的起始位置，循环移动
        start = 1;
        while (k--)
        {
            cycleLeader(a, start - 1, 3*m+1);
            start *= 7;
        }
        // step5:最后剩余进行递归操作
        a += 3*m;
        n -= m;
    }
    if (n == 1)   // n=1的情况要单独处理
    {
        int t = a[0];
        a[0] = a[2];
        a[2] = t;
    }
}

#define   N    (5)
int main()
{
    int a[3*N] = {1,2,3,4,5,  11,12,13,14,15,  21,22,23,24,25}; 

    threePerfectShuttle(a, N);
    for (int i = 0; i < 3*N; i++)
    {
        printf("%d ",a[i]);
    }
    printf("\n");
    return 0;
}