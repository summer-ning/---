/******************************************************************************
 *  题目说明：输入一个由数字组成的字符串，请把它转换成整数输出
    解法： 本题的关键是处理溢出问题
******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h> 

/*
bool isspace(char c)
{
    return (c == ' ');
}

bool isdigit(char c)
{
    return (c >= '0' && c <= '9');
}
*/
int StrToInt(const char *str)
{
    static const int MAX_INT = (int)((unsigned)~0 >> 1);
    static const int MIN_INT = -(int)((unsigned)~0 >> 1) -1;
    int sign = 1, c;
    unsigned int n = 0;
    
    // 判断输入是否为空
    if (NULL == str)
        return 0;
    // 处理空格
    while (isspace(*str))
        str++;
    // 处理正负号
    if (*str == '+' || *str == '-')
    {
        if (*str == '-')
            sign = -1;
        str++;
    }
    while(isdigit(*str))
    {
        c = *str - '0';
        if (sign > 0 && (n > MAX_INT/10 || (n == MAX_INT/10 && c > MAX_INT % 10)))
        {
            n = MAX_INT;
            break;
        }
        else if (sign < 0 && (n > (unsigned)MIN_INT/10 || (n == (unsigned)MIN_INT/10 
                 && c > (unsigned)MIN_INT % 10)))
        {
            n = MIN_INT;
            break;
        }
        n = n * 10 + c;
        str++;
    }
    return sign > 0 ? n : -n;
}

int main()
{
    char str[16];

    printf("Input a number: ");
    gets(str);
    printf("string to int:%d\n",StrToInt(str));
    return 0;
}
