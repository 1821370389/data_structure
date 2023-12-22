#ifndef __LINK_LIST_H__
#define __LINK_LIST_H__

#define ELEMENTTYPE void*

/* 双链表结点 */
typedef struct LinkNode 
{
    /* 前指针 */
    struct LinkNode *prev;
    /* 后指针 */
    struct LinkNode *next;
    /* 数据 */
    ELEMENTTYPE data;
} LinkNode;

/* 双链表 */
typedef struct LinkList
{
    /* 头结点 */
    LinkNode *head;
    /* 尾结点 */
    LinkNode *tail;
    /* 结点数 */
    int count;
} LinkList;

/* 链表初始化 */
int linkListInit(LinkList **list);

/* 链表头插 */
int linkListHeadInsert(LinkList *list, ELEMENTTYPE data);

/* 链表尾插 */
int linkListTailInsert(LinkList *list, ELEMENTTYPE data);

/* 链表指定位置插入 */
int linkListInsert(LinkList *list, int index, ELEMENTTYPE data);

/* 获取链表长度(结点个数) */
int linkListLength(LinkList *list, int *length);

/* 获取指定位置数据 */
int linkListGet(LinkList *list, int index, ELEMENTTYPE *data);

/* 链表头删 */
int linkListHeadDelete(LinkList *list);

/* 链表尾删 */
int linkListTailDelete(LinkList *list);

/* 链表指定位置删除 */
int linkListDelete(LinkList *list, int index);

/* 链表删除指定值*/
int linkListDeleteValue(LinkList *list, ELEMENTTYPE data,int (*isSame)(ELEMENTTYPE,ELEMENTTYPE));

/* 链表销毁 */
int linkListDestroy(LinkList *list);

/* 链表遍历 */
int linkListTraverse(LinkList *list, int (*visit)(ELEMENTTYPE));

/* 逆序遍历 */
int linkListReverseTraverse(LinkList *list, int (*visit)(ELEMENTTYPE));

#endif