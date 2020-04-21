/******************************************************************************
 *  题目说明：求字符串的所有组合
             例如： 输入 "abc" 输出 "a" "b" "c" "ab" "ac" "bc" "abc"
    解法：组合是没有顺序的。根据组合公式，共有2^n中组合，去掉长度为0的共有2^n -1中组合
         我们用1个bit位来代替一个字符，0表示字符不在组合中，1表示不在。
         "abc"的所有组合可以表示成001-111；我们只需要打印bit位为1对应的字符
******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <math.h>

// 参数str必须没有重复的字符
void PrintCombination(char *str)
{
    int len = strlen(str);
    int i,j;
    int num = pow(2,len);

    for (i = 1; i < num; i++)
    {
        for (j = 0; j < len; j++)
        {
            if ((1 << j) & i)
            {
                putchar(str[j]);
            }
        }
        putchar('\n');
    }
}

int main()
{
    char str[100];

    printf("Input a string,Don't have repeated characters:");
    scanf("%s",str);
    PrintCombination(str);
    return 0;
}
