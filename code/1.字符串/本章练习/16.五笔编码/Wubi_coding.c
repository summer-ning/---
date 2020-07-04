/**********************************************************************
 * 说明：五笔编码使用a-y的25个字母，1-4位编码，如果把编码按照字典序排序，放到
 *       一个数组，如：a,aa,aaa,aaaa,aaab,.....,b,ba,baa,baaa,.....,yyyx,yyyy,
 *       其中a的下标是0，aa是1，.....
 *      (1).输入任意的编码，输出对应的数组下标。如aaaa,输出3
 *      (2).输入任意的数组下标，输出对应的编码，如3，输出aaaa
 * 解法：（1）输入编码，输出下标
 *          根据排列组合，编码总个数=4位编码个数+3位编码个数+2位+1位编码=25^4+25^3+25^2+25^1
 *           假设编码只有一位x1,如果x1=c,那么所有在x1=a或b的编码都在它前面，
 *           一共有T1=2*(25^3+25^2+25^1+25^0)个，如果两位，假设x2=d,那么所有在x1=x1,x2=a或b或c
 *           的编码也都在它前面，一共有T2=3*(25^2+25^1+25^0)+1+T1,以此类推，.....
 *           求下标的公式（x1-x4存在,不存在对应的Tn为0）：
 *                  T = T1+T2+T3+T4=(x1-a)(25^3+25^2+25^1+25^0)+(x2-a)(25^2+25^1+25^0)+1
                                   +(x3-a)(25^1+25^0)+1+(x4-a)(25^0)+1
         （2）已知下标求编码，其实就是上面的逆运算
              假设x1x2x3x4的下标是T(x1x2x3x4)，那么根据(1)中的公式
                T(a)=0;T(b)=(b-a)(25^3+25^2+25^1+25^0)=16276;T(c)=32552=2*16276;......T(y)=(y-a)*16276
                所以用第一个编码x1=T(x1x2x3x4)/16276+'a'
                同理：x2=(T(x1x2x3x4)-T1-1)/(25^2+25^1+25^0)+'a'     (T(x1x2x3x4)-T1-1 >= 0)
 * *******************************************************************/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define     CODING_DIGIT_MAX        (4)   // 编码最大的位数
#define     CODING_CHAR_NUM         (25)  // 编码使用的字符数

#define     POWER(x,n)              pow(x,n)   // x的n次方

// 计算系数
int CalculateCoefficient(int pos)
{
    int value = 0;
    int len = CODING_DIGIT_MAX - pos;
    int i;

    for (i = 0; i < len; i++)
    {
        value += POWER(CODING_CHAR_NUM,i);
    }
    return value;
}

// 计算五笔编码的下标，成功返回下标值，失败（输入数据错误）返回-1
int CalculateSubscript(char *coding)
{
    int len = strlen(coding);
    int i;
    int subscript = 0;

    if (len > 4 || len <= 0)
        return -1;

    for (i = 0; i < len; i++)
    {
        if (coding[i] >= 'a' && coding[i] <= 'y')
        {
            subscript += (coding[i] - 'a') * CalculateCoefficient(i);
            if (i != 0)
                subscript++;
        }
        else
        {
            subscript = -1;
            break;
        }
    }
    return subscript;
}

bool getCoding(int subscript, char *coding)
{
    int i = 0;
    if (coding == NULL)
        return false;
    while (subscript >= 0 && i < 4)
    {
        coding[i] = subscript / CalculateCoefficient(i) + 'a';
        if (coding[i] > 'y')
            return false;
        subscript = subscript - (coding[i] - 'a') * CalculateCoefficient(i) - 1;
        i++;
    }
    if (i == 4 && subscript >= 0)
        return false;
    return true;
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
            printf("Input subscript: ");
            scanf("%d",&subscript);
            memset(coding,0,sizeof(coding));
            if (getCoding(subscript,coding) == true)
            {
                printf("%d coding is:%s\n",subscript,coding);
            }
            else
            {
                printf("%d is error\n",subscript);
            }
            gets(flag); // 读出回车
        }
        else if (flag[0] == 'q')
        {
            break;
        }
        else
        {
            printf("Input error,please enter again\n");
        }
        printf("\n\n");
    }

    return 0;
}

