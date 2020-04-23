/****************************************************************************
 * 栈
 * 共享栈：如果有两个数据类型相同的栈，各自开辟数组空间，可能出现一个栈满，另一个还有
 *        很多的空间，所以，可以让这两个栈共用一个空间，一个从栈顶开始，一个从栈底开
 *        始。通常都是两个栈空间有相反的关系的时候使用，一个栈增长，另一个缩短。
 * **************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "stack.h"

//#define  USE_LINK_STACK

#ifndef USE_LINK_STACK
/***********************顺序存储栈*********************************/
bool InitStack(SqStack *S,int size)
{
    if (NULL == S)
        return false;
    
    S->base = (SElemType *)malloc(size * sizeof(SElemType));
    if (NULL == S->base)
        return false;
    S->top = S->base;
    S->StackSize = size;
    return true;
}

// 入栈
bool Push(SqStack *S, SElemType e)
{
    if (NULL == S)
        return false;
    if ((S->top - S->base) == S->StackSize)   // 栈满
        return false;

    *S->top = e;
    S->top++;
    return true;
}

// 出栈
bool Pop(SqStack *S, SElemType *e)
{
    if (NULL == S || NULL == e)
        return false;
    if (S->top == S->base)  // 空栈
        return false;
    S->top--;
    *e = *S->top;
    return true;
}

// 获取栈顶元素，不改变指针
bool GetTop(SqStack *S, SElemType *e)
{
    if (NULL == S || NULL == e)
        return false;
    if (S->top == S->base)  // 空栈
        return false;
    *e = *(S->top - 1);
    return true;
}

bool DestoryStack(SqStack *S)
{
    free(S->base);
    return true;
}

bool PrintStack(SqStack *S)
{
    SElemType *p;

    if (NULL == S)
        return false;

    for (p = S->top - 1; p >= S->base; p--)
    {
        printf("%d  ",*p);
    }
    printf("\n");

    return true;
}
/***********************顺序栈*********************************/


#else

/***********************链式存储栈*********************************/
bool InitStack(LinkStack *S)
{
    if (NULL == S)
        return false;
    
    *S = (LinkStack) malloc(sizeof(LinkStack)); // 头结点
    if (NULL == *S)
        return false;
    (*S)->next = NULL;
    return true;
}

// 入栈
bool Push(LinkStack S, SElemType e)
{
    StackNode *p;

    if (NULL == S)
        return false;

    p = (StackNode *) malloc(sizeof(StackNode));
    if (NULL == p)
        return false;

    p->data = e;
    p->next = S->next;
    S->next = p;

    return true;
}

// 出栈
bool Pop(LinkStack S, SElemType *e)
{
    StackNode *p;

    if (NULL == S || NULL == e)
        return false;
    if (NULL == S->next)  // 空栈
        return false;
    
    p = S->next;
    *e = p->data;
    S->next = p->next;
    free(p);

    return true;
}

// 获取栈顶元素，不改变指针
bool GetTop(LinkStack S, SElemType *e)
{
    StackNode *p;

    if (NULL == S || NULL == e)
        return false;
    if (NULL == S->next)  // 空栈
        return false;
    
    p = S->next;
    *e = p->data;
    
    return true;
}

bool PrintStack(LinkStack S)
{
    StackNode *p;

    if (NULL == S)
        return false;

    p = S->next;
    while(p)
    {
        printf("%d  ",p->data);
        p = p->next;
    }
    printf("\n");

    return true;
}
/***********************链式存储栈*********************************/
#endif


/***********************共享栈*********************************/
bool InitShareStack(ShareSqStack *S,int size)
{
    if (NULL == S)
        return false;
    
    S->base = (SElemType *)malloc(size * sizeof(SElemType));
    if (NULL == S->base)
        return false;
    S->top1 = S->base;
    S->top2 = S->base + size - 1;
    S->StackSize = size;

    return true;
}

// 入栈
bool ShareStackPush(ShareSqStack *S, SElemType e,int stackNum)
{
    if (NULL == S)
        return false;
    if (stackNum != 1 || stackNum != 2)
        return false;
    if (S->top1 > S->top2)   // 栈满
        return false;

    if (1 == stackNum)
    {
        *S->top1 = e;
        S->top1++;
    }
    else
    {
        *S->top2 = e;
        S->top2--;
    }
    
    return true;
}

// 出栈
bool ShareStackPop(ShareSqStack *S, SElemType *e,int stackNum)
{
    if (NULL == S)
        return false;
    if (stackNum != 1 || stackNum != 2)
        return false;

    if (1 == stackNum)
    {
        if (S->top1 == S->base)  // 栈空
            return false;
        S->top1--;
        *e = *S->top1;
    }
    else
    {
        if (S->top1 == (S->base + S->StackSize -1))// 栈空
            return false;
        S->top2++;
        *e = *S->top2;
    }
    
    return true;
}

// 获取栈顶元素，不改变指针
bool ShareStackGetTop(ShareSqStack *S, SElemType *e,int stackNum)
{
    if (NULL == S)
        return false;
    if (stackNum != 1 || stackNum != 2)
        return false;

    if (1 == stackNum)
    {
        if (S->top1 == S->base)  // 栈空
            return false;
        *e = *(S->top1 - 1);
    }
    else
    {
        if (S->top1 == (S->base + S->StackSize -1))// 栈空
            return false;

        *e = *(S->top2 + 1);
    }
    
    return true;
}

/***********************共享栈*********************************/
