
/******************************************************************************
 *  题目说明：给定一张直方图，每一小块的高由n个非负整数所确定，每一小块的宽都为1,请找
 *           出直方图中面积最大的矩形。例如，如图2-17所示，直方图中每一块的宽度都是1,
 *           每一块给定的高度分别是2,1,5,6,2,3,那么在这张直方图中，面积最大的矩形便是
 *           阴影部分，面积等于10个单位
 *  解题思路：使用栈，时间复杂度：O(n)，空间复杂度：O(n)
 *  参考： https://blog.csdn.net/u012534831/article/details/74356851?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-2.channel_param&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-2.channel_param
******************************************************************************/
#include <stdio.h>

#include "stack.h"

int findMaxArea(int a[], int len)
{
    SqStack stack;
    int i, index;
    int maxArea = 0, area;
    int left,right;

    if (NULL == a || len < 1)
    {
        printf("ERROR!! input parameter fail\n");
        return 0;
    }

    InitStack(&stack, len);

    Push(&stack, 0);
    for (i = 1; i < len; i++)
    {
        while (GetTop(&stack, &index) == true)
        {
            if (a[i] > a[index])  // // a[i] 与栈顶元素比较。如果a[i] 大，那么将其入栈
            {
                Push(&stack, i);
                break;
            }
            else if (a[i] < a[index])
            {
                Pop(&stack, &index);
                if (GetTop(&stack, &left) == false)
                {
                    left = 0;
                }
                else
                {
                    left = left + 1;
                }
                right = i - 1;
                area = a[index] * (right - left + 1);
                if (area > maxArea)
                    maxArea = area;
            }
            else    // 两者相等，跳过，继续下一个元素
            {
                ;
            }
        }
        if (GetTop(&stack, &index) == false) // 空栈， i入栈
        {
            Push(&stack, i);
        }
    }
    while (Pop(&stack, &index) == true)
    {
        if (GetTop(&stack, &left) == false)
            left = 0;
        else
            left = left + 1;
        right = i - 1;
        area = a[index] * (right - left + 1);
        if (area > maxArea)
            maxArea = area;
    }
    DestoryStack(&stack);
    return maxArea;
}

int main()
{
    int a[] = {2,1,5,6,2,3};
    int maxArea;

    maxArea = findMaxArea(a, sizeof(a)/sizeof(a[0]));
    printf("max Area:%d\n",maxArea);
    return 0;
}

