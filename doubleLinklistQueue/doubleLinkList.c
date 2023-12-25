#include "doubleLinkList.h"
#include <stdlib.h>
#include <stdio.h>
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

/* 宏函数*/
#if 1
/* 检查指针是否为空的宏函数 */
#define CHECK_NULL_POINTER(ptr)                 \
    do                                          \
    {                                           \
        if(ptr == NULL)                         \
        {                                       \
            return NULL_PTR;                    \
        }                                       \
    } while(0)  
/* 判断位置的合法性 */
#define CHECK_POSITION(index, pArray)           \
    do                                          \
    {                                           \
        if(index < 0 || index > pArray->count)  \
        {                                       \
            return ILLEGAL_ACCESS;              \
        }                                       \
    } while(0)
/* 释放结点内存 */
#define FREE_NODE(node)                         \
    do                                          \
    {                                           \
        if(node != NULL)                        \
        {                                       \
            free(node);                         \
            node = NULL;                        \
        }                                       \
    } while(0)
/* 检测分配空间是否成功 */
#define CHECK_MALLOC_ERROR(ptr)                 \
    do                                          \
    {                                           \
        if(ptr == NULL)                         \
        {                                       \
            return MALLOC_ERROR;                \
        }                                       \
    } while(0)
#endif

/* 遍历到指定位置 */
static int DoubleLinkListFind(DoubleLinkList *list, int index, DoubleLinkNode **node)
{
    /* 遍历结点到插入点 */
    DoubleLinkNode *travelNode = NULL;
    if(index < (list->count >> 1))
    {
        /* 从头遍历 */
        travelNode = list->head;
        while(index--)
        {
            travelNode = travelNode->next;
        }
    }
    else
    {
        /* 从尾部开始 */
        travelNode = list->tail;
        while(index++ < list->count)
        {
            travelNode = travelNode->prev;
        }
    }

    /* 返回结点指针 */
    *node = travelNode;
    return SUCCESS;   
}

/* 新建双链表结点 */
static DoubleLinkNode *DoubleLinkListNewNode(ELEMENTTYPE data)
{
    DoubleLinkNode *node = (DoubleLinkNode *)malloc(sizeof(DoubleLinkNode));
    /* 判断分配空间是否成功 
        默认返回值是 int型 存在返回不兼容问题
        所以不用宏函数
    */
    //CHECK_MALLOC_ERROR(node);
    if(node == NULL)
    {
        return NULL;
    }
    /* 清除脏数据 */
    memset(node, 0, sizeof(DoubleLinkNode));
    /* 初始化结点 */
    node->data = data;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

/* 链表初始化 */
int DoubleLinkListInit(DoubleLinkList **list)
{
    DoubleLinkList *pList = (DoubleLinkList*)malloc(sizeof(DoubleLinkList));
    CHECK_MALLOC_ERROR(pList);

    /* 清除脏数据 */
    memset(pList, 0, sizeof(DoubleLinkList));

    *list = pList;

    /* 初始化首尾指针 */
    pList->head = (DoubleLinkNode *)malloc(sizeof(DoubleLinkNode));
    CHECK_MALLOC_ERROR(pList->head);
    memset(pList->head, 0, sizeof(DoubleLinkNode));
    pList->head->prev = NULL;
    pList->head->data = 0;
    pList->head->next = NULL;
    pList->tail = pList->head;

    /* 初始化长度 */
    pList->count = 0;

    return SUCCESS;
}

/* 链表头插 */
int DoubleLinkListHeadInsert(DoubleLinkList *list, ELEMENTTYPE data)
{
    return DoubleLinkListInsert(list, 1, data);
    
}

/* 链表尾插 */
int DoubleLinkListTailInsert(DoubleLinkList *list, ELEMENTTYPE data)
{
    return DoubleLinkListInsert(list, list->count+1, data);
}

/* 链表指定位置插入 */
int DoubleLinkListInsert(DoubleLinkList *list, int index, ELEMENTTYPE data)
{
    /* 从习惯上讲，插入的位置一个是指定位置原数据的前面 所以输入的数会比实际大1 */
    index -= 1;
    /* 判空 */
    CHECK_NULL_POINTER(list);
    /* 判断位置合法性 */
    CHECK_POSITION(index, list);

    /* 创建新结点 */
    #if 0
    DoubleLinkNode *newNode = (DoubleLinkNode *)malloc(sizeof(DoubleLinkNode));
    CHECK_MALLOC_ERROR(newNode);
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    #else
    DoubleLinkNode *newNode = DoubleLinkListNewNode(data);
    CHECK_MALLOC_ERROR(newNode);
    #endif

    /* 插入结点 */
    if(index == list->count)/* 尾插 */
    {
        newNode->prev = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;
    }
    else/* 中间插 */
    {
        /* 遍历结点到插入点 */
        DoubleLinkNode *travelNode = NULL;
        DoubleLinkListFind(list, index, &travelNode);
        /* 插入结点 */
        /* 错误示例 */
        // newNode->next = travelNode;
        // newNode->prev = travelNode->prev;
        // travelNode->prev->next = newNode;
        // travelNode->prev = newNode;
        /* 接在指定结点后,不然会被头结点往后顶，但头结点没值 */

        travelNode->next->prev = newNode;
        newNode->next = travelNode->next;
        travelNode->next = newNode;
        newNode->prev = travelNode;
    }

    
    /* 结点数+1 */
    list->count++;

    return SUCCESS;
}

/* 获取链表长度(结点个数) */
int DoubleLinkListLength(DoubleLinkList *list, int *length)
{
    /* 判空 */
    CHECK_NULL_POINTER(list);
    CHECK_NULL_POINTER(length);

    /* 获取长度 */
    *length = list->count;

    return list->count;
}

/* 获取指定位置数据 */
int DoubleLinkListGet(DoubleLinkList *list, int index, ELEMENTTYPE *data)
{
    /* 判空 */
    CHECK_NULL_POINTER(list);
    CHECK_NULL_POINTER(data);
    /* 判断位置合法性 */
    CHECK_POSITION(index, list);
    
    /* 遍历到指定位置 */
    DoubleLinkNode *travelNode = NULL;
    DoubleLinkListFind(list, index, &travelNode);
    /* 返回数据 */
    *data = travelNode->data;
    return SUCCESS;
}

/* 链表头删 */
int DoubleLinkListHeadDelete(DoubleLinkList *list)
{
    return DoubleLinkListDelete(list, 1);
}

/* 链表尾删 */
int DoubleLinkListTailDelete(DoubleLinkList *list)
{
    return DoubleLinkListDelete(list, list->count);
}

/* 链表指定位置删除 */
int DoubleLinkListDelete(DoubleLinkList *list, int index)
{
    /* 判空 */
    CHECK_NULL_POINTER(list);
    /* 判断位置合法性 */
    CHECK_POSITION(index, list);
    if(index == 0)
    {
        return UNDERFLOW; /* 头结点不能删 */
    }

    /* 遍历结点 */
    DoubleLinkNode *travelNode = NULL;
    /* 尾删 */
    if(index == list->count)
    {
        travelNode = list->tail;
        list->tail = list->tail->prev;
        list->tail->next = NULL;
    }
    else
    {
        DoubleLinkListFind(list, index, &travelNode);
        travelNode->prev->next = travelNode->next;
        travelNode->next->prev = travelNode->prev;
    }

    FREE_NODE(travelNode);
    list->count--;

    return SUCCESS;
}



/* 链表删除指定值*/
int DoubleLinkListDeleteValue(DoubleLinkList *list, ELEMENTTYPE data,int (*isSame)(ELEMENTTYPE,ELEMENTTYPE))
{
    /* 判空 */
    CHECK_NULL_POINTER(list);

    /* 遍历结点 */
    int count = 1;
    DoubleLinkNode *travelNode = list->head->next;
    while(travelNode != NULL)
    {
        if (isSame(travelNode->data, data))
        {
            travelNode = travelNode->next;
            DoubleLinkListDelete(list, count);
        }
        else
        {
            travelNode = travelNode->next;
            count++;
        }
    }
}

/* 链表销毁 */
int DoubleLinkListDestroy(DoubleLinkList *list)
{
    /* 判空 */
    CHECK_NULL_POINTER(list);
    /* 遍历结点 */
    while(list->tail != list->head)
    {
        /* 尾删 */
        DoubleLinkListTailDelete(list);
    }
    FREE_NODE(list->head);
    FREE_NODE(list);


    return SUCCESS;
}

/* 链表遍历 */
int DoubleLinkListTraverse(DoubleLinkList *list, int (*visit)(ELEMENTTYPE))
{
    /* 判空 */
    CHECK_NULL_POINTER(list);
    /* 遍历结点 */
    #if 0
    /* 从头结点开始，判断下一结点是否为空，非空就跳到下一结点，打印值 */
    DoubleLinkNode *travelNode = list->head;
    while(travelNode->next != NULL)
    {
        travelNode = travelNode->next;
        visit(travelNode->data);
    }
    #else
    /* 从第一结点开始，判断该结点是否为空，非空就打印值，然后跳到下一结点*/
    DoubleLinkNode *travelNode = list->head->next;
    while(travelNode != NULL)
    {
        visit(travelNode->data);
        travelNode = travelNode->next;
    }
    #endif
    return SUCCESS;
}

/* 逆序遍历 */
int DoubleLinkListReverseTraverse(DoubleLinkList *list, int (*visit)(ELEMENTTYPE))
{
    /* 判空 */
    CHECK_NULL_POINTER(list);
    /* 遍历结点 */
    DoubleLinkNode *travelNode = list->tail;
    while(travelNode != list->head)
    {
        visit(travelNode->data);
        travelNode = travelNode->prev;
    }
    return SUCCESS;
}

/* 获取链表头值 */
int DoubleLinkListGetHead(DoubleLinkList *list, ELEMENTTYPE *data)
{
    #if 0
    return DoubleLinkListGetIndex(list, 1, data);
    #else
    /* 判空 */
    CHECK_NULL_POINTER(list);
    /* 返回数据 */
    if(list->count != 0)
    {
        *data = list->head->next->data;
        return SUCCESS;
    }
    else
    {
        return UNDERFLOW;
    }
    #endif
}

/* 获取链表尾值 */
int DoubleLinkListGetTail(DoubleLinkList *list, ELEMENTTYPE *data)
{
    #if 0
    return DoubleLinkListGetIndex(list, list->count, data);
    #else
    /* 判空 */
    CHECK_NULL_POINTER(list);
    /* 返回数据 */
    if(list->count != 0)
    {
        *data = list->tail->data;
        return SUCCESS;
    }
    else
    {
        return UNDERFLOW;
    }
    #endif
}

/* 获取链表指定位置的值 */
int DoubleLinkListGetIndex(DoubleLinkList *list, int index, ELEMENTTYPE *data)
{
    /* 判空 */
    CHECK_NULL_POINTER(list);
    /* 判断位置合法性 */
    CHECK_POSITION(index, list);
    /* 遍历结点 */
    DoubleLinkNode *travelNode = NULL;
    DoubleLinkListFind(list, index, &travelNode);
    /* 返回数据 */
    *data = travelNode->data;
    return SUCCESS;
}