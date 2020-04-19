/******************************************************************************
 *  题目说明：已知字符串的字符互不相同的，把他们任意排序，按照字典序输出所有的组合
             例如： 输入： "aa" 输出： "aa" "ab" "ba" "bb"
    解法：递归调用
******************************************************************************/
#include <stdio.h>
#include <string.h>

int charcmp(char *x, char *y)
{
    return *x - *y;
}

void PrintFullPermutation(const char * const perm, char *print_str, int from, int to)
{
    int i;
    static id = 0;

    for (i = 0; i <= to; i++)
    {
        print_str[from] = perm[i];
        if (from == to)
        {
            printf("%d.%s\n",id,print_str);
            id++;
        }
        else
            PrintFullPermutation(perm, print_str, from+1, to); 
    }
}

int main()
{
    char str[100],print_str[100];

    printf("Input a string: ");
    gets(str);
    // 字典序最小的排序
    qsort(str, strlen(str),sizeof(char),charcmp);
    // 打印字典序
    PrintFullPermutation(str, print_str,0,strlen(str)-1);
    return 0;
}
