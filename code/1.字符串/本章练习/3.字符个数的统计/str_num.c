/******************************************************************************
 *  题目说明：给定字符串，查找出该字符串每个字符出现的次数，要求区分大小写，时间复杂度为O(n)
    解法：定义一个包含数组记录每个字符出现的次数
******************************************************************************/
#include <stdio.h>
#include <string.h>

#define   CHAR_NUMBER_MAX       (0x80)   // ASCII码个数

void StringCharNumber(const char *str, int len, int count[])
{
    int i;

    if (NULL == str || count == NULL || len < 1)
        return;

    memset(count,0,CHAR_NUMBER_MAX*sizeof(int));

    for (i = 0; i < len; i++)
    {
        count[str[i]]++;
    }
}

int main()
{
    char str[100];
    int count[CHAR_NUMBER_MAX];
    int i;

    printf("Input a string: ");
    gets(str);
    StringCharNumber(str,strlen(str),count);
    for (i = 0; i < CHAR_NUMBER_MAX; i++)
    {
        if (count[i] != 0)
        {
            printf("%c:  %d\n",i,count[i]);
        }
    }

    return 0;
}
