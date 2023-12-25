#ifndef __LINK_LIST_H__
#define __LINK_LIST_H__

#define ELEMENTTYPE void*

/* 循环链表结点 */
typedef struct CircularLinkNode 
{
    /* 前指针 */
    struct CircularLinkNode *prev;
    /* 后指针 */
    struct CircularLinkNode *next;
    /* 数据 */
    ELEMENTTYPE data;
} CircularLinkNode;

/* 循环链表 */
typedef struct CircularLinkList
{
    /* 头结点 */
    CircularLinkNode *head;
    /* 结点数 */
    int count;
} CircularLinkList;

/* 链表初始化 */
int CircularLinkListInit(CircularLinkList **list);

/* 链表头插 */
int CircularLinkListHeadInsert(CircularLinkList *list, ELEMENTTYPE data);

/* 链表尾插 */
int CircularLinkListTailInsert(CircularLinkList *list, ELEMENTTYPE data);

/* 链表指定位置插入 */
int CircularLinkListInsert(CircularLinkList *list, int index, ELEMENTTYPE data);

/* 获取链表长度(结点个数) */
int CircularLinkListLength(CircularLinkList *list, int *length);

/* 获取指定位置数据 */
int CircularLinkListGet(CircularLinkList *list, int index, ELEMENTTYPE *data);

/* 链表头删 */
int CircularLinkListHeadDelete(CircularLinkList *list);

/* 链表尾删 */
int CircularLinkListTailDelete(CircularLinkList *list);

/* 链表指定位置删除 */
int CircularLinkListDelete(CircularLinkList *list, int index);

/* 链表删除指定值*/
int CircularLinkListDeleteValue(CircularLinkList *list, ELEMENTTYPE data, int (*isSame)(ELEMENTTYPE,ELEMENTTYPE));

/* 链表销毁 */
int CircularLinkListDestroy(CircularLinkList *list);

/* 链表遍历 */
int CircularLinkListTraverse(CircularLinkList *list, int (*visit)(ELEMENTTYPE));

/* 逆序遍历 */
int CircularLinkListReverseTraverse(CircularLinkList *list, int (*visit)(ELEMENTTYPE));

#endif