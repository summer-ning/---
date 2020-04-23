/******************************************************************************
 *  题目说明：判断一个栈是否是回文
    解法： 将一个字符串压入栈，然后依次出栈，得到字符串的逆序，然后和原字符串比较
******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "stack.h"

int main()
{
    char str1[100], str2[100];
    SqStack S;
    int i,j;

    printf("Input a string: ");
    gets(str1);

    // 初始化栈
    InitStack(&S, 100);
    // 入栈
    for (i = 0; i < strlen(str1); i++)
    {
        Push(&S,str1[i]);
    }
    // 出栈
    i = 0;
    while(Pop(&S,&str2[i]))
    {
        i++;
    }
    str2[i] = '\0';
    // 比较两个字符串
    for(i = 0; i < strlen(str1); i++)
    {
        if (str1[i] != str2[i])
            break;
    }
    if (i == strlen(str1))
        printf("String is palindrome\n");
    else 
        printf("String is't palindrome\n");
    return 0;
}
