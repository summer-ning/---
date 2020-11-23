/******************************************************************************
 *  题目说明：输入一个整数n,求从1到n这n个整数的十进制表示中1出现的次数。例如，输入12,
 *           从1到12这些整数中包含1的数字有1、10、11和12,数字1一共出现了5次。
    解法：假设输入数字为abcdef,然后讨论个十百千……各个位上为1的情况，每种情况又分为大于1，
          等于1，等于0的情况
    参考：https://blog.csdn.net/wangbaochu/article/details/54176969
******************************************************************************/
#include <stdio.h>

// 计算n中有多少个1
static int NumberOfOne(int n)
{
    int count = 0;
    int pow1 = 1,pow2;
    while (n >= pow1)
    {
        pow2 = 10 * pow1;
        if (1 == ((n % pow2) / pow1))
            count++;
        pow1 *= 10;
    }
    return count;
}

// 使用蛮力算法来验证其他算法是否正确
int countOfOne_BruteForce(int n)
{
    int i;
    int count = 0;

    for (i = 1; i <= n; i++)
    {
        count += NumberOfOne(i);
    }
    return count;
}

// 计算从1-n中1出现的次数
int countOfOne(int n)
{
    int pow1 = 1;
    int pow2;
    int count = 0;

    while (n >= pow1)
    {
        pow2 = 10 * pow1;
        switch((n % pow2) / pow1)
        {
            case 0:
            {
                count += (n / pow2) * pow1;
            }
            break;
            case 1:
            {
                count += (n / pow2) * pow1;
                count += (n % pow1) + 1;
            }
            break;
            default:
            {
                count += (n / pow2 + 1) * pow1;
            }
        }
        pow1 *= 10;
    }
    return count;
}

int main()
{
    int i;
    int count1, count2;
#if 1
    for(i = 1; i < 9999; i++)
    {
        count1 = countOfOne(i);
        count2 = countOfOne_BruteForce(i);
        if (count1 != count2)
        {
            printf("ERR,i=%d,count1=%d,count2=%d\n",i,count1,count2);
            break;
        }
    }
#else
    count1 = countOfOne(2);
    printf("count1=%d\n",count1);
#endif
    printf("test end\n");
    
    return 0;
}
