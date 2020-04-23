/****************************************************************************
 * 单向链表
 * **************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "link_list.h"


#define  list_malloc        malloc
#define  list_free          free


LinkList InitList()
{
    LinkList L;

    L = (LinkList) list_malloc(sizeof(LNode));  // 创建头结点
    if (NULL == L)
    {
        return NULL;
    }

    L->next = NULL;
    return L;
}

// 给定节点序号i,获得该节点的值,1<= i <=listLength(L)
bool GetElem(LinkList L, int i, ElemType *data)
{
    LNode *p;
    int j;

    if (NULL == L || NULL == data)
        return false;
    
    p = L->next;
    j = 1;
    while(p && j < i)
    {
        p = p->next;
        j++;
    }
    if (!p || j > i)  // 第 i 个元素不存在
        return false;

    *data = p->data;
    return true;
}

// 按值查找位置
LNode *LocationElem(LinkList L, ElemType data)
{
    LNode *p;

    if (NULL == L)
        return NULL;

    p = L->next;
    while(p && p->data != data)
    {
        p = p->next;
    }
    return p;
}

// 把数据插入到第i个节点上（i-1和i之间的位置）
bool ListInsert(LinkList L, int i, ElemType data)
{
    LNode *p, *s;
    int j;

    if (NULL == L)
        return false;
    
    p = L;
    j = 0;
    while(p && j < (i - 1))  // 查找第i-1个节点
    {
        p = p->next;
        j++;
    }
    if (!p || j > i-1)
        return false;

    s = (LNode *) list_malloc(sizeof(LNode)); // 创建新节点
    if (NULL == s)
        return false;

    s->data = data;
    s->next = p->next;
    p->next = s;

    return true; 
}

// 删除第i个节点
bool ListDelete(LinkList L, int i)
{
    LNode *p, *s;
    int j;

    if (NULL == L)
        return false;

    p = L;
    j = 0;
    while(p && (j < i-1))
    {
        p = p->next;
        j++;
    }
    if (!p || (j > i-1))
        return false;

    s = p->next;
    if (s != NULL)
    {
        p->next = s->next;
        list_free(s);
    }

    return true;
}

bool ClearList(LinkList L)
{
    LNode *p, *q;

    if (NULL == L)
        return false;
    
    p = L->next;
    while(p)
    {
        q = p->next;
        list_free(p);
        p = q;
    }

    L->next = NULL;
}

bool DestoryList(LinkList L)
{
    ClearList(L);
    list_free(L);
}

// 头插法创建链表
// 头插法（前插法）：新节点插入到头结点之后；尾插发（后插法）：新节点插入到中断节点之后
LinkList CreateList_H()
{
    LinkList L;
    LNode *p;
    int number = 5;

    L = InitList();
    if (NULL == L)
        return NULL;
    
    for(int i = 0; i < number; i++)
    {
        p = (LNode *) list_malloc(sizeof(LNode));
        if (NULL == p)
            return L;
        p->data = i;
        p->next = L->next;
        L->next = p;
    }
    return L;
}

// 尾插法创建链表
// 头插法（前插法）：新节点插入到头结点之后；尾插法（后插法）：新节点插入到中断节点之后
LinkList CreateList_R(ElemType *data)
{
    LinkList L;
    LNode *p,*r;
    int number = 5;

    L = InitList();
    if (NULL == L)
        return NULL;

    r = L;    // 尾指针
    while(*data)
    {
        p = (LNode *) list_malloc(sizeof(LNode));
        if (NULL == p)
            return L;
        p->data = *data;
        p->next = NULL;
        r->next = p;
        r = p;
        data++;
    }
    return L;
}

bool PrintList(LinkList L)
{
    LNode *p;

    if (NULL == L)
        return false;

    p = L->next;
    printf("data:");
    while(p)
    {
        printf("%d ",p->data);
        p = p->next;
    }
    printf("\n");
    return true;
}



