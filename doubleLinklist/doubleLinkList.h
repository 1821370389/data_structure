#ifndef __LINK_LIST_H__
#define __LINK_LIST_H__

#define ELEMENTTYPE void*

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

/* 链表初始化 */
int DoubleLinkListInit(DoubleLinkList **list);

/* 链表头插 */
int DoubleLinkListHeadInsert(DoubleLinkList *list, ELEMENTTYPE data);

/* 链表尾插 */
int DoubleLinkListTailInsert(DoubleLinkList *list, ELEMENTTYPE data);

/* 链表指定位置插入 */
int DoubleLinkListInsert(DoubleLinkList *list, int index, ELEMENTTYPE data);

/* 获取链表长度(结点个数) */
int DoubleLinkListLength(DoubleLinkList *list, int *length);

/* 获取指定位置数据 */
int DoubleLinkListGet(DoubleLinkList *list, int index, ELEMENTTYPE *data);

/* 链表头删 */
int DoubleLinkListHeadDelete(DoubleLinkList *list);

/* 链表尾删 */
int DoubleLinkListTailDelete(DoubleLinkList *list);

/* 链表指定位置删除 */
int DoubleLinkListDelete(DoubleLinkList *list, int index);

/* 链表删除指定值*/
int DoubleLinkListDeleteValue(DoubleLinkList *list, ELEMENTTYPE data,int (*isSame)(ELEMENTTYPE,ELEMENTTYPE));

/* 链表销毁 */
int DoubleLinkListDestroy(DoubleLinkList *list);

/* 链表遍历 */
int DoubleLinkListTraverse(DoubleLinkList *list, int (*visit)(ELEMENTTYPE));

/* 逆序遍历 */
int DoubleLinkListReverseTraverse(DoubleLinkList *list, int (*visit)(ELEMENTTYPE));

#endif