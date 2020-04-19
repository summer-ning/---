/******************************************************************************
 *  题目说明：输入一个字符串，打印出改字符串中字符的所有排列。
             例如： "abc" 输出： "abc" "acb" "bac" "bca" "cab" "cba"
    解法：字典序排列
          字典序的定义：两个字符串，从起点开始将对应的字符串逐个比较，先出现较小字符的
                       字典序较小
           算法起点：字典序最小的排列1-n，例如： "12345"
           算法终点：字典序最大的排列1-n, 例如： "54321"
           算法的执行过程：从当前排序生成字典序刚好比它大的下一个排序（c++标准库中
                         next_permutation函数的实现）
******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void swap(char *a, char *b)
{
    char t;
    t = *a; *a = *b; *b = t;
}

int charcmp(char *x, char *y)
{
    return *x - *y;
}

// 反转字符串str从from到to的字符
void ReverseString(char *str, int from, int to)
{
    char t;
    while (from < to)
    {
        t = str[from];
        str[from++] = str[to];
        str[to--] = t;
    }
}

// next_permutatiion算法的实现
bool CalcAllPermutation(char *perm, int num)
{
    int i,k;

    // 1. 从右往左扫描每个字符，看哪个能增大（如果这个字符右面有比它大的字符就可以增大）
    for (i = num -2; (i >= 0) && (perm[i] >= perm[i+1]); i--)
    {
        ;
    }

    if (i < 0)  // 已经是最大的排序
    {
        return false;
    }
    // 2. 找到排序中第i位右面比perm[i]大且最接近perm[i]的字符
    for (k = num -1; (k > i) && (perm[k] <= perm[i]); k--)
    {
        ;
    }
    // 3.交换perm[i] perm[k]
    swap(&perm[i],&perm[k]);
    // 4. 把第i+1到最后的字符翻转
    ReverseString(perm, i+1, num-1);
    return true;
}

int main()
{
    char str[100];
    int i = 0;

    printf("input a string: ");
    gets(str);
    // 字典序最小的排序
    qsort(str, strlen(str),sizeof(char),charcmp);

    printf("all permutation: \n");
    printf("%d. %s\n",i++,str);
    while(CalcAllPermutation(str,strlen(str)) == true)
    {
        printf("%d. %s\n",i++,str);
    }
    return 0;
}
