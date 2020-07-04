/******************************************************************************
 *  说明：给定一个字符串，将其中连续出现的空格压缩为一个后，将其中以空格分隔的每个字符
          逆序打印出来。
******************************************************************************/
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void strSpaceCompressionReverse(char *str, int len)
{
    int from;
    int i,j,k;
    char t;
    bool prevIsSpace = false; // 前一个字符是空格
    int spaceCount = 0;
    if (str == NULL)
        return;
    
    from = 0;
    for (i = 0; i < len; i++)
    {
        if (' ' == str[i])
        {
            if (false == prevIsSpace)  // 第一次出现空格
            {
                // 逆序前面的字符
                j = from;
                k = i - 1;
                while (j < k)
                {
                    t = str[j];
                    str[j++] = str[k];
                    str[k--] = t;
                }
                if (spaceCount > 0)
                {
                    // 左移
                    for (j = from; j <= i; j++)
                    {
                        str[j-spaceCount] = str[j];
                    }
                }
                from = i + 1;
                prevIsSpace = true;
                printf("string:%s\n",str);
            }
            else
            {
                // 连续空格
                from++;
                spaceCount++;
            }
        }
        else
        {
            prevIsSpace = false;
        }
    }
    if (from < len)  // 最后一个单词需要逆序
    {
        j = from;
        k = len - 1;
        while (j < k)
        {
            t = str[j];
            str[j++] = str[k];
            str[k--] = t;
        }
        if (spaceCount > 0)
        {
            // 左移
            for (j = from; j < len; j++)
            {
                str[j-spaceCount] = str[j];
            }
        }
    }
    str[len-spaceCount] = '\0';
}


int main()
{
    char str[100] = {0};
    printf("Input a sentence: ");
    gets(str);
    strSpaceCompressionReverse(str,strlen(str));
    printf("reverse: %s\n",str);
    return 0;
}


