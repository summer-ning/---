/******************************************************************************
 * 题目描述：给定一个字符串，长度不超过100，其中只包含字符0和1,并且字符0和1出现的次数
 *          都是偶数。你可以把字符串任意切分，把切分后的字符串任意分给两个人，让两个
 *          人得到的0的总个数相等，得到的1的总个数也相等。
 * 题目解析：假设将这个字符串的头与尾部相连接，那么构成一个字符串圆环，在这个圆环中存
 *          在这样一个规律：必定存在这样一条直径，以这条直径将圆环分成两部分，使得这
 *          两部分的0的个数相同，且1的个数相同。所以，最多需要两刀就能将字符串均分
 *          具体分析参考：
 *          https://blog.csdn.net/xhu_eternalcc/article/details/17609631?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-1.compare&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-1.compare
 * ****************************************************************************/

#include <stdio.h>
#include <string.h>

int howmany(char *str)
{
    int len;
    int count_L = 0;
    int count_R = 0;
    int i;

    if (str == NULL)
        return -1;
    len = strlen(str);
    if ((len % 2) != 0) // 不是偶数
    {
        printf("string length is not even\n");
        return -1;
    }
    for (i = 0; i < len/2; i++)
    {
        if (str[i] == '1')
            count_L++;
        if (str[len-1-i] == '1')
            count_R++;
    }
    if ((count_L + count_R)%2 != 0)
    {
        printf("'1' and '0' is not even\n");
        return -1;
    }
    if (count_L == count_R)
        return 1;
    else
        return 2;
}

int main()
{
    char str[100] = {0};
    printf("input a string containing only 0 and 1:");
    gets(str);
    printf("%d\n",howmany(str));
    return 0;
}

