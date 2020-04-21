/******************************************************************************
 *  题目说明：打印如下序列
             (a), (b) ,(c)…………(z)
             (a,b), (a,c),(a,d),…………(y,z)
             ……
             ……
             (a,b,c …………,z)
    解法：本题要做的是有序的输出所有组合
          打印a-z所有组合，先打印一个字符的组合，然后打印2个字符的组合，移植到26个字符
          的组合。
          如果要从n(26个字母)个字符中选出m个字符的所有组合，第一步从n个中选取1个，然后从
          n-1个中选取第二个，……从n-m+1个中第m个数；因为我们是按顺序打印，第一个字符肯定
          小于第二个，第二个小于第三个，……。所以我们可以设计一个递归算法：
          从n个字符中选出m个字符的所有有序组合的方法：1.从1-n个字符中选出1个字
          符（假设是第k个字符），2.从k+1-n个字符中选出m-1个字符.
          当只需要选出一个字符的时候，就可以打印了
******************************************************************************/
#include <stdio.h>
#include <string.h>


/**********************************************************************
* 函数名称： PrintCombination
* 功能描述： 从字符串str中选出n个字符的排列并打印
* 输入参数： str：字符串指针
            print_buf: 记录要打印的字符
            from：可选字符的起始位置
            to：可选字符的结束位置
            n: 排列中的字符个数
            print_pos:打印的字符存放的位置
* 输出参数： str
* 返 回 值： void
* 其它说明： 
***********************************************************************/ 
void PrintCombination(const char *const str, char *print_buf,int from, int to, int n,int print_pos)
{
    int i;

    if ((to-from+1) < n || n <= 0) // 可选取的范围长度小于需要的长度返回错误
        return;
    if (print_pos == 0)  // 打印左括号
    {
        print_buf[print_pos++] = '(';
    }
    if (1 == n)  //从from到to中选取一个字符代表这是排列中的最后一个字符，开始打印
    {
        for (i = from; i < to; i++)
        {
            print_buf[print_pos] = str[i];
            print_buf[print_pos+1] = '\0';
            printf("%s), ",print_buf);
        }
        // 最后一个不需要打印逗号
        print_buf[print_pos] = str[i];
        print_buf[print_pos+1] = '\0';
        printf("%s) ",print_buf);
    }
    else 
    {
        for (i = from; i <= to; i++)
        {
            print_buf[print_pos] = str[i];
            print_buf[print_pos+1] = ',';
            PrintCombination(str,print_buf,i+1,to,n-1,print_pos+2);
        }
    }
}

int main()
{
    char str[] = "abcde";
    char print_buf[200] = {0};
    int len = strlen(str);
    int i;
    
    for (i = 1; i <= len; i++)
    {
        PrintCombination(str,print_buf,0,len-1,i,0);
        printf("\n");
    }
    return 0;
}
