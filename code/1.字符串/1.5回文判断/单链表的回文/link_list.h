#ifndef LINK_LIST_H_
#define LINK_LIST_H_

typedef  char   ElemType;

typedef struct LNode
{
    ElemType data;
    struct LNode *next;
}LNode, *LinkList;

typedef struct DulNode
{
    ElemType data;
    struct DulNode *next;
    struct DulNode *prior;
}DulNode, *DuLinkList;



#endif