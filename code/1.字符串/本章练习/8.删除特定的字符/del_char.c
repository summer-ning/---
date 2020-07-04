/******************************************************************************
 *  说明：给定一个原始字符串和模式字符串，要求在原始字符串中删除所有在模式字符串中出现
          的字符。如原始字符串是 "They are students.", 模式字符串是 "aeiou", 删除之
          后得到的字符串是 "Thy r stdnts."
    解法: 1.对模式字符串建立哈希表，键为字符，值为1。这样只要遍历一遍就能找到所有要删除的字符
          2.删除字符，后面的字符要向前移动，需要尽量减少移动的次数。假设需要删除n个字符，
          那么，在第一个删除字符前面的字符需要向前移动0位，第一个和第二个删除字符之间的字符
          需要向前移动1位，第k和k+1个删除字符之间的字符需要向前移动k位
******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define HASH_TABLE_SIZE     (128)  // ASCII码的个数是128

bool DeletePatternChar(char *sourceString, char *patternstr)
{
    char hashTable[HASH_TABLE_SIZE] = {0};
    char *p = patternstr;
    int delCount = 0;

    if (NULL == sourceString || NULL == patternstr)
    {
        return false;
    }

    // 1.建立哈希表
    while (*p != '\0')
    {
        hashTable[*p++] = 1;
    }
    // 2.删除字符
    p = sourceString;
    while (*p != '\0')
    {
        if (1 == hashTable[*p])
        {
            delCount++;
        }
        else   // 没被删除的字符需要向前移动
        {
            *(p - delCount) = *p;
        }
        p++;
    }
    *(p - delCount) = '\0';
}

int main()
{
    char sourceStr[100];
    char patterStr[128];

    printf("Input a source string: ");
    gets(sourceStr);
    printf("Input a pattern string: ");
    gets(patterStr);

    DeletePatternChar(sourceStr, patterStr);
    printf("The delete string:%s\n",sourceStr);

    return 0;
}

