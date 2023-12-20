#include "LinkList.h"
#include <stdlib.h>
#include <string.h>


/* 状态码 */
enum STATUS_CODE
{
    SUCCESS = 0,
    NULL_PTR = -1,
    MALLOC_ERROR = -2,
    ILLEGAL_ACCESS = -3,
    UNDERFLOW = -4,

};


/* 链表的初始化 */
int LinkListInit(LinkList **pList)
{
    LinkList *list = (LinkList *)malloc(sizeof(LinkList));
    if(list == NULL)
    {
        return MALLOC_ERROR;
    }
    /* 清除脏数据 */
    memset(list, 0, sizeof(LinkList));

    list->head = (LinkNode *)malloc(sizeof(LinkNode));
    if(list->head == NULL)
    {
        return MALLOC_ERROR;
    }
    /* 清除脏数据 */
    memset(list->head, 0, sizeof(LinkNode));
    list->head->data = 0;
    list->head->next = NULL;

    /* 链表的长度为0 */
    list->len = 0;

    /* 二级指针 */
    *pList = &list;
    
    return SUCCESS;
}

/* 链表头插 */
int LinkListHeadInsert(LinkList *pList, ELEMENTTYPE data)
{
    
}

/* 链表尾插 */
int LinkListTailInsert(LinkList *pList, ELEMENTTYPE data)
{
    
}

/* 链表指定位置插入 */
int LinkListInsert(LinkList *pList, int pos, ELEMENTTYPE data)
{
    
}

/* 链表头删 */
int LinkListHeadDelete(LinkList *pList)
{
    
}

/* 链表尾删 */
int LinkListTailDelete(LinkList *pList)
{
    
}

/* 链表指定位置删除 */
int LinkListDelete(LinkList *pList, int pos)
{
    
}

/* 链表指定值删除 */
int LinkListDeleteByValue(LinkList *pList, ELEMENTTYPE data)
{
    
}

/* 获取链表长度 */
int LinkListLen(LinkList *pList, int *pLen)
{
    
}

/* 获取链表指定位置的值 */
int LinkListGet(LinkList *pList, int pos, ELEMENTTYPE *data)
{
    
}

/* 链表销毁 */
int LinkListDestroy(LinkList *pList)
{

}

/* 链表遍历 */
int LinkListTraverse(LinkList *pList)
{

}