/******************************************************************************
 *  题目说明：单链表的回文判断
    解法：快慢指针，当快指针到结尾的时候，慢指针指向链表的中间。把从链表头到链表中间（链表
          的前半部分）部分转置，然后和后半部分比较
******************************************************************************/
#include <stdio.h>
#include <stdbool.h>
#include "link_list.h"



bool IsPalindromeLink(LinkList L)
{
    LinkList second_L;
    LNode *fast, *slow;
    LNode *node;

    if (NULL == L || NULL == L->next)  // 空链表
        return false;
    
    second_L = InitList();
    fast = slow = L->next;
    while(fast != NULL && fast->next != NULL)
    {
        // 把前半部分逆序,使用前插法;为了不改变原来链表的结构，需要额外创建一个链表
        node = (LNode *)malloc(sizeof(LNode));
        node->data = slow->data;
        node->next = second_L->next;
        second_L->next = node;

        slow = slow->next;
        fast = fast->next->next;
    }
    //PrintList(second_L);
    if (fast != NULL && fast->next == NULL)  // 链表的长度是奇数
    {
        // 奇数的节点中间那个元素是不用进行判断的
        slow = slow->next;
    }

    // 比较逆序链表和后半部分是否相同
    node = second_L->next;
    while(slow != NULL && slow->data == node->data)
    {
        slow = slow->next;
        node = node->next;
    }
    DestoryList(second_L);  // 销毁临时链表
    if (slow == NULL)
        return true;
    else 
        return false;
}

int main()
{
    char str[100];
    LinkList L;

    printf("Input a string: ");
    gets(str);
    // 创建链表
    L = CreateList_R(str);
    PrintList(L);
    if (IsPalindromeLink(L))
    {
        printf("string is palindrome link\n");
    }
    else
    {
        printf("string isn't palindrome link\n");
    }
    
    return 0;
}
