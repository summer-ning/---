/******************************************************************************
 *  题目说明：给定一个字符串，求它的最长回文子串的长度
    解法：方法一：中心扩展法
             将子串分为单核和双核的情况，单核即指子串长度为奇数，双核则为偶数
             枚举中心位置，然后再在该位置上扩展，并记录最长回文串的长度
             复杂度O(n^2)
          方法二：Manacher算法
             1.将原字符串S的每个字符间都插入一个永远不会在S中出现的字符（本例中用“#”表示），
               在S的首尾也插入该字符，使得到的新字符串S_new长度为2*S.length()+1，保证Len
               的长度为奇数
             2.根据S_new求出以每个字符为中心的最长回文子串的最右端字符距离该字符的距离，
               存入Len数组中，即S_new[i]到S_new[r]为S_new[i]的最长回文子串的右段
               （S_new[2i-r]到S_new[r]为以S_new[i]为中心的最长回文子串），
                Len[i] = r - i + 1; Len数组性质：Len[i] - 1即为以Len[i]为中心的最长回文
                子串在S中的长度。在S_new中，以S_new[i]为中心的最长回文子串长度为
                2Len[i] - 1，由于在S_new中是在每个字符两侧都有新字符“#”，观察可知“#”的数量
                一定是比原字符多1的，即有Len[i]个，因此真实的回文子串长度为Len[i] - 1，最长
                回文子串长度为Math.max(Len) - 1
             3.Len数组求解（线性复杂度（O(n)））：
               a.遍历S_new数组，i为当前遍历到的位置，即求解以S_new[i]为中心的最长回文子串的Len[i];
               b.设置两个参数：sub_midd = Len.indexOf(Math.max(Len)表示在i之前所得到的Len
                 数组中的最大值所在位置、sub_side = sub_midd + Len[sub_midd] - 1表示以
                 sub_midd为中心的最长回文子串的最右端在S_new中的位置。起始sub_midd和sub_side
                 设为0，从S_new中的第一个字母开始计算，每次计算后都需要更新sub_midd和sub_side；
               c.当i <= sub_side时，取i关于sub_midd的对称点j（j = 2sub_midd - i，由于i <= sub_side，
                 因此2sub_midd - sub_side <= j <= sub_midd);当Len[j] < sub_side - i + 1时，即
                 以S_new[j]为中心的最长回文子串是在以S_new[sub_midd]为中心的最长回文子串的内部，再
                 由于i、j关于sub_midd对称，可知Len[i] = Len[j];
               d.当Len[j] >= sub.side - i时说明以S_new[i]为中心的回文串可能延伸到sub_side之
                 外，而大于sub_side的部分还没有进行匹配，所以要从sub_side+1位置开始进行匹配，
                 直到匹配失败以后，从而更新sub_side和对应的sub_midd以及Len[i]；
               e.当i > sub_side时，则说明以S_new[i]为中心的最长回文子串还没开始匹配寻找，因此
                 需要一个一个进行匹配寻找，结束后更新sub_side和对应的sub_midd以及Len[i]。
        本书的解释不够详细，所以我参考了：
             https://blog.csdn.net/qq_32354501/article/details/80084325

******************************************************************************/
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define STRING_MAX_LEN      (100)

int longstrPalindrome(const char *str, int len)
{
    int i, j, c;
    int max = 0;

    if (NULL == str || len < 1)
        return 0;

    for (i = 0; i < len; i++)  // 以i为回文的中心位置
    {
        // 回文长度为奇数
        for (j = 0; ((i-j) >= 0) && ((i+j) < len);j++) // j表示向左向右扩展的长度
        {
            if(str[i-j] != str[i+j])
                break;
            c = 2 * j + 1;  // 以i为中心的奇数回文长度
        }
        if (c > max)
            max = c;
        // 回文长度为偶数
        for (j = 0; ((i - j) > 0) && ((i+j+1) < len); j++)
        {
            if(str[i-j] != str[i+j+1])
                break;
            c = 2 * j + 2;
        }
        if (c > max)
            max = c;
    }
    return max;
}

int Manacher_longstrPalindrome(const char *str, int len)
{
    char new_str[2*STRING_MAX_LEN+1];
    char p[2*STRING_MAX_LEN+1] = {0}; // p[i]表示以i为中心的最长回文子串最右端到中心点的距离
    int new_str_len = 2*len+1;
    int i,j = 0;
    int sub_mid, sub_side;

    if (NULL == str || len < 1)
        return 0;

    // 1 插入'#'，构建新的字符串
    new_str[j++] = '#';
    for (i = 0; i < len; i++)
    {
        new_str[j++] = str[i];
        new_str[j++] = '#';
    }

    // 2 求p[i]和p[i]的最大值
    p[0] = 1; 
    sub_mid = 0; 
    sub_side = sub_mid + p[sub_mid] -1;
    for(i = 1; i < new_str_len; i++)
    {
        if (i <= sub_side)
        {
            j = 2*sub_mid - i;  // i 关于sub_mid的对称点
            if (p[j] < (sub_side - i + 1)) // 以j点为中心的最长回文串在以sub_mid点为中心的回文串内部
                p[i] = p[j];
            else
                p[i] = sub_side - i + 1;
        }
        else
        {
            p[i] = 1;
        }
        for (j = p[i]; (i-j) >= 0 && (i+j) < new_str_len; j++)
        {
            if (new_str[i-j] != new_str[i+j])
                break;
            p[i] += 1;
        }
        if (p[i] > p[sub_mid])
        {
            sub_mid = i;
            sub_side = sub_mid + p[sub_mid] -1;
        }
    }
/*
    for (i = 0; i < new_str_len; i++)
        printf("%d ",p[i]);
    printf("\n");
*/
    return p[sub_mid] - 1;
    
}

int main()
{
    char str[STRING_MAX_LEN];
    int max,max2;

    printf("Input a string: ");
    gets(str);
    max = longstrPalindrome(str,strlen(str));
    printf("maximum palindrome sub string length:%d\n",max);
    max2 = Manacher_longstrPalindrome(str,strlen(str)); 
    if (max != max2)
    {
        printf("Manacher error,max2=%d\n",max2);
    }
    return 0;
}

