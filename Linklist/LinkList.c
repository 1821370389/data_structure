#include "LinkList.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* 状态码 */
enum STATUS_CODE
{
    SUCCESS = 0,
    NULL_PTR = -1,
    MALLOC_ERROR = -2,
    ILLEGAL_ACCESS = -3,
    UNDERFLOW = -4,

};


/* 检查指针是否为空的宏函数 */
#define CHECK_NULL_POINTER(ptr) \
    do \
    { \
        if(ptr == NULL) \
        { \
            return NULL_PTR; \
        }\
    } while(0)  
/* 判断位置的合法性 */
#define CHECK_POSITION(index, pArray) \
    do \
    { \
        if(index < 0 || index > pArray->len) \
        { \
            return ILLEGAL_ACCESS; \
        } \
    } while(0)
/* 释放结点内存 */
#define FREE_NODE(node) \
    do \
    { \
        if(node != NULL) \
        { \
            free(node); \
            node = NULL; \
        } \
    } while(0)

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

    /* 初始化时尾指针 = 头指针*/
    list->tail = list->head;

    /* 链表的长度为0 */
    list->len = 0;

    /* 二级指针 */
    *pList = list;
    
    return SUCCESS;
}

/* 链表头插 */
int LinkListHeadInsert(LinkList *pList, ELEMENTTYPE data)
{
    return LinkListInsert(pList, 0, data);
}

/* 链表尾插 */
int LinkListTailInsert(LinkList *pList, ELEMENTTYPE data)
{
    return LinkListInsert(pList, pList->len, data);
}

/* 链表指定位置插入 */
int LinkListInsert(LinkList *pList, int pos, ELEMENTTYPE data)
{
    /* 判空 */
    CHECK_NULL_POINTER(pList);
    /* 判断位置合法性 */
    CHECK_POSITION(pos, pList);

    /* 封装结点 */
    LinkNode *newNode = (LinkNode *)malloc(sizeof(LinkNode));
    if(newNode == NULL)
    {
        return MALLOC_ERROR;
    }
    /* 清除脏数据 */
    memset(newNode, 0, sizeof(LinkNode));

    /* 从虚拟头结点开始遍历*/
    LinkNode *travelNode = pList->head;

    int flag = 0;
    /* 这种情况下需要更改尾指针*/
    if(pos == pList->len)
    {
        /* 修改结点指向 */
        travelNode = pList->tail;
        flag = 1;
    }
    else
    {
        while(pos--)
        {
            travelNode = travelNode->next;
        }
    }
    /* 修改结点指向 */
    newNode->next = travelNode->next;
    travelNode->next = newNode;
    newNode->data = data;
    if(flag)
    {
        /* 修改尾指针 */
        pList->tail = newNode;
    }



    /* 更新链表长度 */
    pList->len++;
    return SUCCESS;
}

/* 链表头删 */
int LinkListHeadDelete(LinkList *pList)
{
    return LinkListDelete(pList, 1);
}

/* 链表尾删 */
int LinkListTailDelete(LinkList *pList)
{
    return LinkListDelete(pList, pList->len);
}

/* 链表指定位置删除 */
int LinkListDelete(LinkList *pList, int pos)
{
    int flag = 0;
    /* 判空 */
    CHECK_NULL_POINTER(pList);
    /* 判断位置合法性 */
    CHECK_POSITION(pos, pList);

    /* 需要修改尾指针 */
    if(pos == pList->len)
    {
        flag = 1;
    }
    LinkNode *travelNode = pList->head;
    /* 从虚拟头结点开始遍历*/
    while(--pos)
    {
        travelNode = travelNode->next;
    }
    /* 修改结点指向 */
    LinkNode *delNode = travelNode->next;
    travelNode->next = delNode->next;

    if(flag)
    {
        pList->tail = travelNode;
    }

    /* 释放结点内存 */
    FREE_NODE(delNode);

    /* 更新链表长度 */
    pList->len--;
    return SUCCESS;
}

/* 静态函数只给本源文件的的函数使用，不需要判断参数合法性 */
/* 链表查找指定数据位置 */
static int LinkListFind(LinkList *pList, ELEMENTTYPE data, int *pPos)
{
    LinkNode *travelNode = pList->head->next;
    int pos = 1;
    while(travelNode->data)
    {
        if(travelNode->data == data)
        {
            *pPos = pos;
            return pos;
        }
        pos++;
        travelNode = travelNode->next;
    }

    return UNDERFLOW;
}

/* 链表指定值删除 */
int LinkListDeleteByValue(LinkList *pList, ELEMENTTYPE data)
{

    int pos = 0;
    int len = 0;
    while(LinkListLen(pList, &len) && pos != UNDERFLOW)
    {
        LinkListDelete(pList, LinkListFind(pList, data, &pos));

    }
    return SUCCESS;
}

/* 获取链表长度 */
int LinkListLen(LinkList *pList, int *pLen)
{
    /* 判空 */
    CHECK_NULL_POINTER(pList);

    if(pLen)
    {
        *pLen = pList->len;
    }
    return pList->len;
}

/* 获取链表指定位置的值 */
int LinkListGet(LinkList *pList, int pos, ELEMENTTYPE *data)
{
    
}

/* 链表销毁 */
int LinkListDestroy(LinkList *pList)
{
    /* 我们使用头删释放链表 */
    int size = 0;
    while(LinkListLen(pList,&size))
    {
        LinkListHeadDelete(pList);
    }
    // if(pList->head)
    // {
    //     free(pList->head);
    //     pList->head = NULL;
    // }
    FREE_NODE(pList->head);
}

/* 链表遍历 */
int LinkListTraverse(LinkList *pList,int (*printfFunc)(ELEMENTTYPE))
{
    /* 判空 */
    CHECK_NULL_POINTER(pList);
#if 1
    /* 遍历 */
    LinkNode *travelNode = pList->head->next;
    /* travelNode 指向第一个结点 */
    while(travelNode)
    {
        #if 0 
        printf("%d ", *(int *)travelNode->data);
        #else
        /* 包装器/钩子/回调函数 */
        printfFunc(travelNode->data);
        #endif
        travelNode = travelNode->next;
    }
    printf("\n");
#else
    /* 遍历 */
    LinkNode *travelNode = pList->head;
    /* travelNode 虚拟头结点 */
    while(travelNode->next)
    {
        travelNode = travelNode->next;
        printf("%d ", travelNode->data);
    }
    printf("\n");
#endif
    return SUCCESS;
}