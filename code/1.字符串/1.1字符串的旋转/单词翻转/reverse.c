/******************************************************************************
 *  说明：输入一个英文句子，翻转句子中的单词顺序。要求单词内字符的顺序不变，句子中单词
        以空格隔开。例如 "I am a student." -> "student. a am I"
     思路：先把每个单词翻转，然后把整个句子翻转
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

void ReverseSentences(char *str, int n)
{
    int i, from;

    from = 0;
    for (i = 0; i< n; i++)
    {
        // 遇到空格，翻转前面的单词
        if (' ' == str[i])
        {
            ReverseString(str, from, i-1);
            from = i+1; // 下一个单词的起始位置
        }
    }
    ReverseString(str, from, n-1);  // 翻转最后一个单词
    ReverseString(str, 0, n-1);     // 翻转整个句子
}

int main()
{
    char str[100] = {0};
    printf("Input a sentence: ");
    gets(str);
    ReverseSentences(str,strlen(str));
    printf("reverse: %s\n",str);
    return 0;
}
