/******************************************************************************
 *  说明：由小写字母组成的字符串，对连续出现的字符进行压缩
          aaaabcccdefffg -->   4ab3cde3fg
******************************************************************************/
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void stringCompression(char *str, int len)
{
    int i = 1,j = 0;
    int count = 1;

    if (NULL == str)
        return;
    while (i <= len)
    {
        if (str[i] == str[i-1])
        {
            count++;
        }
        else
        {
            if (count > 1)
            {
                str[j++] = count + '0';
                str[j++] = str[i-1];
                count = 1;
            }
            else
                str[j++] = str[i-1];
        }
        i++;
    }
    str[j] = '\0';
}

int main()
{
    char str[100] = {0};
    printf("Input a sentence: ");
    gets(str);
    stringCompression(str,strlen(str));
    printf("compression: %s\n",str);
    return 0;
}