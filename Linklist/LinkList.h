#ifndef __LINKLIST_H__
#define __LINKLIST_H__

#define ELEMENTTYPE int


/* 链表结点 */
typedef struct LinkNode
{
    ELEMENTTYPE data;
    /* 指向下一个结点的指针 */
    LinkNode *next; 
    /* 为什么指针的类型是结点 */
}   LinkNode;

/* 链表 */
typedef struct LinkList
{
    /* 链表的虚拟头结点
        1.数据与无意义
        2.只使用指针域
    */
    LinkNode *head;

    /* 链表的长度 */
    int len;

} LinkList;

/* 链表的初始化*/
int LinkListInit(LinkList **pList);

/* 链表头插 */
int LinkListHeadInsert(LinkList *pList, ELEMENTTYPE data);

/* 链表尾插 */
int LinkListTailInsert(LinkList *pList, ELEMENTTYPE data);

/* 链表指定位置插入 */
int LinkListInsert(LinkList *pList, int pos, ELEMENTTYPE data);

/* 链表头删 */
int LinkListHeadDelete(LinkList *pList);

/* 链表尾删 */
int LinkListTailDelete(LinkList *pList);

/* 链表指定位置删除 */
int LinkListDelete(LinkList *pList, int pos);

/* 链表指定值删除 */
int LinkListDeleteByValue(LinkList *pList, ELEMENTTYPE data);

/* 获取链表长度 */
int LinkListLen(LinkList *pList, int *pLen);

/* 获取链表指定位置的值 */
int LinkListGet(LinkList *pList, int pos, ELEMENTTYPE *data);

/* 链表销毁 */
int LinkListDestroy(LinkList *pList);

/* 链表遍历 */
int LinkListTraverse(LinkList *pList);

#endif