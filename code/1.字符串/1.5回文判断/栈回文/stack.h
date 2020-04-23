#ifndef STACK_H_
#define STACK_H_

typedef  char   SElemType;


typedef struct 
{
    SElemType *base;
    SElemType *top;
    int StackSize;
}SqStack;

typedef struct 
{
    SElemType *base;
    SElemType *top1;
    SElemType *top2;
    int StackSize;
}ShareSqStack;

// 链栈节点
typedef struct StackNode
{
    SElemType data;
    struct StackNode *next;
}StackNode, *LinkStack;



#ifndef USE_LINK_STACK
bool InitStack(SqStack *S,int size);
bool Push(SqStack *S, SElemType e);
bool Pop(SqStack *S, SElemType *e);
bool GetTop(SqStack *S, SElemType *e);
bool DestoryStack(SqStack *S);
#endif

#endif
