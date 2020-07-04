/******************************************************************************
 *  说明：在一个字符串中找出第一个只出现一次的字符
    解法：哈希表，键为字符，值为出现的个数。第一次遍历，建立哈希表，然后第二次遍历找出
         第一个出现一个的字符
******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define  TABLE_SIZE         128  // ASCII码的个数

char FirstNotRepeatChar(char *str)
{
    int hashTable[TABLE_SIZE] = {0};
    char *p = str;

    if (str == NULL)
        return '\0';
    
    while (*p != '\0')
    {
        hashTable[*p]++;
        p++;
    }
    p = str;
    while(*p != '\0')
    {
        if (hashTable[*p] == 1)
            return *p;
        p++;
    }
    return '\0';
}

int main()
{
    char str[100] = {0};
    char c;

    printf("Input a string: ");
    gets(str);
    c = FirstNotRepeatChar(str);
    printf("First not repeat char is \'%c\',%d\n",c,c);
    return 0;
}
