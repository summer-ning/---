/******************************************************************************
 *  说明：给一篇文章，里面是由一个个单词组成，单词中间空格隔开，再给一个字符串指针数组，
         比如 char *str[]={"hello","world","good"};
          求文章中包含这个字符串指针数组的最小子串。注意，只要包含即可，没有顺序要求。
    思路：文章也可以理解为一个大的字符串数组，单词之前只有空格，没有标点符号。使用第4
          题中求子串的方法，求出数组中每个子串在文章中的位置，然后在找最短的长度      
******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


#define  STRING_LEN_MAX     100
#define  FILE_NAME          "./snowman.txt"
#define  FILE_MAX_SIZE      (5*1024)

static void getNextValue(char *subStr, int *next)
{
    int strLen;
    int i,j;

    if (subStr == NULL || next == NULL)
        return false;
    
    strLen = strlen(subStr);
    i = 0;
    next[0] = -1;
    j = -1;

    while(i < strLen)
    {
        if (j == -1 || subStr[i] == subStr[j])
        {
            i++;
            j++;
            if (subStr[i] != subStr[j])
                next[i] = j;
            else
                next[i] = next[j];
        }
        else
        {
            j = next[j];
        }
    }
}

/**********************************************************************
* 函数名称： subStringIndex
* 功能描述： 寻找子串的位置
* 输入参数： str:主串
            subStr:子串
* 输出参数： void 
* 返 回 值： -1:不存在子串
            >-1:子串在主串中第一次出现的位置
* 其他说明： KMP算法,时间复杂度O(m+n)
***********************************************************************/

int subStringIndex(char *str, char *subStr)
{
    int next[STRING_LEN_MAX];
    int strLen = strlen(str);
    int subStrLen = strlen(subStr);
    int i = 0;   // str的index
    int j = 0;   // subStr的index

    if (NULL == str || NULL == subStr)
        return -1;

    if (strlen(subStr) > STRING_LEN_MAX)
    {
        return -2;
    }

    getNextValue(subStr,next);

    while(i < strLen && j < subStrLen)
    {
        if (str[i] == subStr[j] || -1 == j)
        {
            i++;
            j++;
        }
        else
        {
            j = next[j];
        }
    }
    if (j == subStrLen)
        return i - subStrLen;
    else
        return -1;
}

int main()
{
    FILE *fd = NULL;
    char *str[]={"hello","world","good"};
    char buf[FILE_MAX_SIZE] = {0};
    int readLen;
    int strNum = sizeof(str) / 4;
    int pos[10][100];
    int num[10] = {0};
    int i,j,index = 0;
    char *p;
    int len;

    fd = fopen(FILE_NAME,"r");
    if (NULL == fd)
    {
        printf("open file fail\n");
        return -1;
    }

    readLen = fread(buf,1,FILE_MAX_SIZE,fd);
    for (i = 0; i < strNum; i++)
    {
        p = str[i];
        j = 0;
        len = 0
        while (len <= readLen)
        {
            index = subStringIndex(buf+len,p);
            if (index < 0)
            {
                break;
            }
            pos[i][j++] = index;
            len += index + strlen(p);
        }
        if (j == 0)  // 文章中没这个单词
        {
            printf("no word:%s\n",p);
            return -1;
        }
        num[i] = j;
    }

    fclose(fd);
    return 0;
}

