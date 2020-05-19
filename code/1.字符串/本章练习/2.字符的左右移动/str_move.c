/******************************************************************************
 *  题目说明：给定一个字符串，这个字符串由*号和26个字母组成，要求把字符串中的*移动到最
             左边，其他字符移动到最右边，而顺序不变，要求时间复杂度和空间复杂度最小
    解法：从右向左遍历字符串，遇到*号就右移左边的字符串，并记录*的个数，最后在左侧添加*
          号，这样不需要额外的空间，每个字符只移动了一次。空间复杂度O(1),时间复杂度O(n)
******************************************************************************/
#include <stdio.h>
#include <string.h>

void moveString(char *str, int len)
{
    int star_count = 0;
    int i = len - 1;
    char move_flag = 0;

    while(i >= 0)
    {
        if (str[i] == '*')
        {
            star_count++;
        }
        else if (star_count > 0)
        {
            str[i+star_count] = str[i]; // 右移star_count位
        }

        i--;
    }
    // 为前面star_count个字符赋值了*
    for (i = 0; i < star_count; i++)
    {
        str[i] = '*';
    }
}

int main()
{
    char str[100];

    printf("Input a string ");
    gets(str);
    moveString(str,strlen(str));
    printf("%s\n",str);
    return 0;
}
