/**********************************************************************
 * 说明：五笔编码使用a-y的25个字母，1-4位编码，如果把编码按照字典序排序，放到
 *       一个数组，如：a,aa,aaa,aaaa,aaab,.....,b,ba,baa,baaa,.....,yyyx,yyyy,
 *       其中a的下标是0，aa是1，.....
 *      (1).输入任意的编码，输出对应的数组下标。如aaaa,输出3
 *      (2).输入任意的数组下标，输出对应的编码，如3，输出aaaa
 * 解法：（1）输入编码，输出下标
 *          根据排列组合，编码总个数=4位编码个数+3位编码个数+2位+1位编码=25^4+25^3+25^2+25^1
 *           假设编码只有一位x1,如果x1=c,那么所有在x1=a或b的编码都在它前面，
 *           一共有2*(25^3)个，如果两位，假设x2=d,那么所有在x1=x1,x2=a或b或c
 *           的编码也都在它前面，一共有3*(25^2)+1+(x1-a)(25^3)+1,以此类推，.....
 *           求下标的公式（x1-x4存在且不为a）：
 *                  x1x2x3x4=(x1-a)*25^3+(x2-a)*25^2+1+(x3-a)*25+1+(x4-a)+1    
 * *******************************************************************/

#include <stdio.h>
#include <string.h>
#include <math.h>

#define     CODING_DIGIT_MAX        (4)   // 编码最大的位数
#define     CODING_CHAR_NUM         (25)  // 编码使用的字符数

#define     POWER(x,n)              pow(x,n)   // x的n次方

// 计算系数
int CalculateCoefficient(int pos,int end_flag)
{
    int value = 0;
    int len = CODING_DIGIT_MAX - pos;
    int i;
    int power = CODING_CHAR_NUM; // 次幂

    if (end_flag)
        power++;

    for (i = 0; i < len; i++)
    {
        value += POWER(power,i);
    }
    return value;
}

// 计算五笔编码的下标，成功返回下标值，失败（输入数据错误）返回-1
int CalculateSubscript(char *coding)
{
    int len = strlen(coding);
    int i;
    int subscript = -1;

    if (len > 4)
        return -1;
    for (i = 0; i < len; i++)
    {
        subscript += (coding[i] - 'a') * POWER(CODING_CHAR_NUM,CODING_DIGIT_MAX-i-1) + 1;
    }
    if (len > 1 && (len < 4 || (len == 4 && coding[len-1] != 'a')))
        subscript += coding[len-1] - 'a';
  /*  
    if (coding[0] == 'a')
        subscript--;
    */
    return subscript;
}

int main()
{
    char coding[16] = {0};
    int subscript = 0;
    char flag[4];
    int i = 0;

    while (1)
    {
        printf("Input type(s,c,q)\ns:subscript\nc:coding\nq:quit\n");
        gets(flag);
        if (flag[0] == 'c')
        {
            printf("Input coding: ");
            gets(coding);
            subscript = CalculateSubscript(coding);
            if (subscript != -1)
                printf("coding %s subscript is:%d\n",coding,subscript);
            else
                printf("err coding\n");
            
        }
        else if (flag[0] == 's')
        {

        }
        else if (flag[0] == 'q')
        {
            break;
        }
        else
        {
            printf("Input error,please enter again\n");
        }
        for (i = 0; i < 9999; i++);  // 延时
    }

    return 0;
}

