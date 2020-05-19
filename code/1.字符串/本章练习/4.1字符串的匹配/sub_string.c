/****************************************************************************
 * 串的模式匹配
 * 子串的定位操作通常被称为串的模式匹配
 * 两种算法，蛮力算法和KMP算法（参考《数据结构 C语言版》P95）
 * KMP算法的核心思想就是：每当一趟匹配过程中出现字符比较不等时，不需回溯l指针，
 *                      而是利用已经得到的 “部分匹配” 的结果将模式向右“滑动”尽
 *                      可能远的一段距离后，继续进行比较。
 * 虽然BF（蛮力）算法的时间复杂度是O(nm), 但 在一般情况下，其实际的执行时间近似于O(n + m), 
 * 因此至今仍被采用。KMP算法仅当 模式与主串之间存在许多 “部分匹配” 的情况下，才显得
 * 比BF算法快得多。但是KMP算法的最大特点是指示主串的指针不需回溯，整个匹配过程中，对
 * 主串仅需从头至尾扫描一遍，这对处理从外设输入的庞大文件很有效，可以边读入边匹配，而无需回头重读。
 * **************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define  STRING_LEN_MAX     100

static void getNextValue(char *subStr, int *next)
{
    int strLen;
    int i,j;

    if (subStr == NULL || next == NULL)
        return false;
    
    strLen = strlen(subStr);
    i = 0;
    next[0] = -1;
    j = -1;

    while(i < strLen)
    {
        if (j == -1 || subStr[i] == subStr[j])
        {
            i++;
            j++;
            if (subStr[i] != subStr[j])
                next[i] = j;
            else
                next[i] = next[j];
        }
        else
        {
            j = next[j];
        }
    }
}

/**********************************************************************
* 函数名称： subStringIndex
* 功能描述： 寻找子串的位置
* 输入参数： str:主串
            subStr:子串
* 输出参数： void 
* 返 回 值： -1:不存在子串
            >-1:子串在主串中第一次出现的位置
* 其他说明： KMP算法,时间复杂度O(m+n)
***********************************************************************/

int subStringIndex(char *str, char *subStr)
{
    int next[STRING_LEN_MAX];
    int strLen = strlen(str);
    int subStrLen = strlen(subStr);
    int i = 0;   // str的index
    int j = 0;   // subStr的index

    if (NULL == str || NULL == subStr)
        return -1;

    if (strlen(subStr) > STRING_LEN_MAX)
    {
        return -2;
    }

    getNextValue(subStr,next);

    while(i < strLen && j < subStrLen)
    {
        if (str[i] == subStr[j] || -1 == j)
        {
            i++;
            j++;
        }
        else
        {
            j = next[j];
        }
    }
    if (j == subStrLen)
        return i - subStrLen;
    else
        return -1;
}

int main()
{
    char str[100] = {0};
    char subStr[50] = {0};

    while(1)
    {
        printf("input string: ");
        scanf("%s",str);
        printf("input sub string: ");
        scanf("%s",subStr);

        printf("subStr postion=%d\n",subStringIndex(str,subStr));
    }
    return 0;
}