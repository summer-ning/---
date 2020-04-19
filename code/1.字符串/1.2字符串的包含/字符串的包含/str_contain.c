/******************************************************************************
 *  题目说明：给定一个长字符串a和短字符产b，快速判断b中所有的字符都在a中。假设字符串a
             和b都只包含大写字母
    解法：位运算法
          先把长字符串a中的所有字符都放在散列表中，然后轮询b，看b中的每个字符是否都在
          散列表中
******************************************************************************/
#include <stdio.h>
#include <stdbool.h>


bool StringContain(char *a, char *b)
{
    int hash = 0;  // 26个字母需要26bit位

    if (NULL == a || NULL == b)
        return false;
    while(*a)
    {
        hash |=  1 << (*a - 'A');
        a++;
    }
    while(*b)
    {
        if ((hash & (1 << (*b - 'A'))) == 0)
            return false;
        b++;
    }
    return true;
}

int main()
{
    char a[100],b[100];

    printf("Input a long string: ");
    gets(a);
    printf("Input a short string: ");
    gets(b);
    printf("%s\n",StringContain(a,b)? "Yes" : "No");
    return 0;
}

