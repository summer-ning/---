/******************************************************************************
 *  题目说明：给定一个字符串，判断是否是回文串
    解法： 两个分别指向字符串头和为的指针，往中间扫描
******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool IsPalindrome(const char *str, int len)
{
    const char *head, *tail;

    if (NULL == str || len < 1)
        return false;
    head = str;
    tail = str + len -1;

    while (tail > head)
    {
        if (*tail != *head)
            return false;
        tail--;
        head++;
    }
    return true;
}

int main()
{
    char str[100];

    printf("Input a string: ");
    gets(str);
    if (IsPalindrome(str,strlen(str)))
    {
        printf("String is palindrome\n");
    }
    else
    {
        printf("String is't palindrome\n");
    }
    return 0;
}