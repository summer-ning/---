/******************************************************************************
 *  说明：用递归算法写一个函数，求字符串最长连续字符的长度，比如aaaabbcc的长度为4，
         aabb的长度为2，ab的长度为1。
******************************************************************************/
#include <stdio.h>
#include <string.h>

int LongestConsecutiveCharacters(char *str)
{
    int maxLen = 1, len = 1;

    if (NULL == str)
        return 0;
    if (*str == '\0')
        return 0;
    if (*(str+1) == '\0')
        return 1;
    while (*(str+1) != '\0' && *str == *(str+1))
    {
        maxLen++;
        str++;
    }
    len = LongestConsecutiveCharacters(str+1);
    return (len > maxLen)? len : maxLen;
}

int main()
{
    char str[100] = {0};
    printf("Input a string: ");
    gets(str);
    printf("longest consecutive characters:%d\n",
            LongestConsecutiveCharacters(str));

    return 0;
}