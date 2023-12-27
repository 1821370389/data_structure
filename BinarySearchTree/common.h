#ifndef __COMMON_H_
#define __COMMON_H_

typedef void * ELEMENTTYPE;
/* 双链表结点 */
typedef struct DoubleLinkNode 
{
    /* 前指针 */
    struct DoubleLinkNode *prev;
    /* 后指针 */
    struct DoubleLinkNode *next;
    /* 数据 */
    ELEMENTTYPE data;
} DoubleLinkNode;

/* 双链表 */
typedef struct DoubleLinkList
{
    /* 头结点 */
    DoubleLinkNode *head;
    /* 尾结点 */
    DoubleLinkNode *tail;
    /* 结点数 */
    int count;
} DoubleLinkList;

#endif // __COMMON_H_