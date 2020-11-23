/******************************************************************************
 *  题目说明：有个长度为2n的数组{a1,a2,a3,...,an,b1,b2,b3,...,bn}，希望排序后
 *           {a1,b1,a2,b2,....,an,bn}，请考虑有无时间复杂度o(n)，空间复杂度0(1)的解法。
    解法一：蛮力法，时间复杂度：O(n^2)
            以每次让序列中最中间的元素进行交换达到目的例如：序列：a1，a2，a3，a4，b1，b2，b3，b4
                第①步：交换最中间的两个元素a4，b1，序列变成（待交换的元素用粗体表示）：
                    a1，a2，a3，b1，a4，b2，b3，b4
                第②步，让最中间的两对元素各自交换：
                    a1，a2，b1，a3，b2，a4，b3，b4
                第③步，交换最中间的三对元素，序列变成：
                    a1，b1，a2，b2，a3，b3，a4，b4
    解法二：完美洗牌算法
            时间复杂度：O(n)，空间复杂度：O(1)
            参考：https://wizardforcel.gitbooks.io/the-art-of-programming-by-july/content/02.09.html
                 https://blog.csdn.net/juzihongle1/article/details/76563336
******************************************************************************/
#include <stdio.h>
#include <string.h>

static void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void shuttle_bruteForce(int a[], int n)
{
    int left,right;

    for (int i = 0; i < n; i++)
    {
        left = n - i;
        right = n + i;

        for (int j = left; j < right; j += 2)
        {
            swap(&a[j], &a[j+1]);
        }
    }
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
    int next = (2 * from + 1) % mod; // 因为数组下标是从0开始，所以不是（2i）%mod

    while(next != from)
    {
        swap(&a[next], &a[from]);
        next = (2 * next + 1) % mod;
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
void perfectShuttle(int a[], int n)
{
    int len = 2 * n;
    int i,m,k;
    int start;

    if (n <= 0 || NULL == a)
    {
        printf("ERROR!! input parameter error\n");
        return;
    }

    while (n > 1)
    {
        // step 1 找到 2 m = 3^k - 1 
        m = 1;
        k = 0;
        len = 2*n;
        while((m-1) <= len)
        {
            k++;
            m *= 3;
        }
        m = (m / 3 -1 ) / 2;
        k--;
        // step 2: 把a[m+1,..,n,n+1,...,n + m]循环左移n-m（或者右移m）
        if (m != n)
        {
            // 注意：算法的下标是从1开始，但是实际存储是从0开始
            leftRotate(a, m, n+m-1, n-m); 
        }
        // step 3: 以 3^i -1(i= 0,1,...,k-1)为圈的起始位置，循环移动
        start = 1;
        while (k--)
        {
            cycleLeader(a, start - 1, 2*m+1);
            start *= 3;
        }
        // step4:最后剩余进行递归操作
        a += 2*m;
        n -= m;
    }
   
    if (1 == n)
    {
        int t = a[0];
        a[0] = a[1];
        a[1] = t; 
    }

}

void shuttle_perfect(int a[], int n)
{
    perfectShuttle(a, n);

    // 洗牌算法是a1 a2 a3 b1 b2 b3变成 b1 a1 b2 a3 b3 a3,所以要交换两个数顺序
    for (int i = 0; i < 2*n; i += 2)
    {
        swap(&a[i],&a[i+1]);
    }
}

#define   N     (5)
int main()
{
    int a[2*N] = {1,3,5,7,9, 2,4,6,8,10};
    int b[2*N];

    memcpy(b,a,2*N*sizeof(int));

    shuttle_bruteForce(a, N);
    shuttle_perfect(b, N);

    for (int i = 0; i < 2 * N; i++)
    {
        if (a[i] != b[i])
        {
            printf("i=%d,a[i]=%d,b[i]=%d\n",i,a[i],b[i]);
            break;
        }
    }

    for (int i = 0; i < 2*N; i++)
    {
        printf("%d ",b[i]);
    }
    printf("\n");
    return 0;
}
