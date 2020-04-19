/******************************************************************************
 *  题目说明：给定一个字符串，要求把字符串前面的若干个字符移到字符串的尾部。
             例如:字符串"abcdef"前三个字符移动到尾部，得"defabc"
    解法：三步反转：把字符串分成两个部分，然后对两个部分分别反转，然后再对整个字符串反转
         abcdef --> cbafed  --> defabc
******************************************************************************/
#include <stdio.h>
#include <string.h>

// 反转字符串str从from到to的字符
void ReverseString(char *str, int from, int to)
{
    char t;
    while (from < to)
    {
        t = str[from];
        str[from++] = str[to];
        str[to--] = t;
    }
}

/**********************************************************************
* 函数名称： LeftRotateString
* 功能描述： 字符串循环左移
* 输入参数： str：字符串指针
            len: 字符串的长度
            m：移动的长度
* 输出参数： str
* 返 回 值： void
* 其它说明： 
***********************************************************************/
void LeftRotateString(char *str, int len, int m)
{
    // 如果左移大于len位，则与%len是等价的
    m %= len;
    ReverseString(str,0,m-1);
    ReverseString(str,m,len-1);
    ReverseString(str,0,len-1);
}

int main()
{
    char string[] = "abcdef";
    LeftRotateString(string,strlen(string),3);
    printf("%s\n",string);
    return 0;
}