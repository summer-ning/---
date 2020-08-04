/******************************************************************************
 *  说明：两个单链表求差集
******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

typedef  int   ElemType;

typedef struct LNode
{
    ElemType data;
    struct LNode *next;
}LNode, *LinkList;

bool difference_set(LinkList *A,LinkList B)
{
    LNode *pA, *pB, *q;
    if (NULL == *A || NULL == B)
        return false;
    pB = B;
    while (pB != NULL)
    {
        pA = *A;
        q = pA;
        while (pA != NULL)
        {
            if (pB->data == pA->data)
            {
                if (pA == *A)  // 头结点
                {
                    *A = (*A)->next;
                }
                else
                {
                    q->next = pA->next;
                }
                free(pA);
                break;
            }
            else 
            {
                q = pA;
                pA = pA->next;
            }
        }
        if (pA == NULL)
        {
            printf("%d does not exist in set A\n",pB->data);
            return false;
        }
        pB = pB->next;
    }
    return true;
}

bool PrintList(LinkList L)
{
    LNode *p;

    if (NULL == L)
        return false;

    p = L;
    printf("data:");
    while(p)
    {
        printf("%d ",p->data);
        p = p->next;
    }
    printf("\n");
    return true;
}

int main()
{
    int a;
    LinkList setA =NULL, setB = NULL;
    LNode *p, *q;
    char buf[2];

    printf("first list,'q' means end:");
    while (scanf("%d",&a))
    {
        p = (LNode *)malloc(sizeof(LNode));
        if (NULL == p)
        {
            printf("malloc fail\n");
            break;
        }
        p->data = a;
        p->next = NULL;
        if (NULL == setA)
        {
            setA = p;
            q = setA;
        }
        else
        {
            q->next = p;
            q = p;
        }
    }
    gets(buf);

    printf("Second list,'q' means end:");
    while (scanf("%d",&a))
    {
        p = (LNode *)malloc(sizeof(LNode));
        if (NULL == p)
        {
            printf("malloc fail\n");
            break;
        }
        p->data = a;
        p->next = NULL;
        if (NULL == setB)
        {
            setB = p;
            q = setB;
        }
        else
        {
            q->next = p;
            q = p;
        }
    }
    PrintList(setA);
    PrintList(setB);
    if (difference_set(&setA, setB) == true)
    {
        PrintList(setA);
    }
    return 0;
}