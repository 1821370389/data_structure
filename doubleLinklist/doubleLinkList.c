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
static int linkListFind(LinkList *list, int index, DoubleLinkNode **node)
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

/* 链表初始化 */
int linkListInit(LinkList **list)
{
    LinkList *pList = (LinkList*)malloc(sizeof(LinkList));
    CHECK_MALLOC_ERROR(pList);

    /* 清除脏数据 */
    memset(pList, 0, sizeof(LinkList));

    *list = pList;

    /* 初始化首尾指针 */
    pList->head = (DoubleLinkNode *)malloc(sizeof(DoubleLinkNode));;
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
int linkListHeadInsert(LinkList *list, ELEMENTTYPE data)
{
    return linkListInsert(list, 1, data);
    
}

/* 链表尾插 */
int linkListTailInsert(LinkList *list, ELEMENTTYPE data)
{
    return linkListInsert(list, list->count+1, data);
}

/* 链表指定位置插入 */
int linkListInsert(LinkList *list, int index, ELEMENTTYPE data)
{
    /* 从习惯上讲，插入的位置一个是指定位置原数据的前面 所以输入的数会比实际大1 */
    index -= 1;
    /* 判空 */
    CHECK_NULL_POINTER(list);
    /* 判断位置合法性 */
    CHECK_POSITION(index, list);

    /* 创建新结点 */
    DoubleLinkNode *node = (DoubleLinkNode *)malloc(sizeof(DoubleLinkNode));
    CHECK_MALLOC_ERROR(node);
    node->data = data;
    node->prev = NULL;
    node->next = NULL;

    /* 插入结点 */
    if(index == list->count)/* 尾插 */
    {
        node->prev = list->tail;
        list->tail->next = node;
        list->tail = node;
    }
    else/* 中间插 */
    {
        /* 遍历结点到插入点 */
        DoubleLinkNode *travelNode = NULL;
        linkListFind(list, index, &travelNode);
        /* 插入结点 */
        /* 错误示例 */
        // node->next = travelNode;
        // node->prev = travelNode->prev;
        // travelNode->prev->next = node;
        // travelNode->prev = node;
        /* 接在指定结点后,不然会被头结点往后顶，但头结点没值 */

        travelNode->next->prev = node;
        node->next = travelNode->next;
        travelNode->next = node;
        node->prev = travelNode;
    }

    
    /* 结点数+1 */
    list->count++;

    return SUCCESS;
}

/* 获取链表长度(结点个数) */
int linkListLength(LinkList *list, int *length)
{
    /* 判空 */
    CHECK_NULL_POINTER(list);
    CHECK_NULL_POINTER(length);

    /* 获取长度 */
    *length = list->count;

    return list->count;
}

/* 获取指定位置数据 */
int linkListGet(LinkList *list, int index, ELEMENTTYPE *data)
{
    /* 判空 */
    CHECK_NULL_POINTER(list);
    CHECK_NULL_POINTER(data);
    /* 判断位置合法性 */
    CHECK_POSITION(index, list);
    
    /* 遍历到指定位置 */
    DoubleLinkNode *travelNode = NULL;
    linkListFind(list, index, &travelNode);
    /* 返回数据 */
    *data = travelNode->data;
    return SUCCESS;
}

/* 链表头删 */
int linkListHeadDelete(LinkList *list)
{
    return linkListDelete(list, 1);
}

/* 链表尾删 */
int linkListTailDelete(LinkList *list)
{
    return linkListDelete(list, list->count);
}

/* 链表指定位置删除 */
int linkListDelete(LinkList *list, int index)
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
        list->count--;
        FREE_NODE(travelNode);
    }
    else
    {
        linkListFind(list, index, &travelNode);
        travelNode->prev->next = travelNode->next;
        travelNode->next->prev = travelNode->prev;
        list->count--;
        FREE_NODE(travelNode);
    }

    return SUCCESS;
}

// /* 获取指定值的位置*/
// static int linkListFindValue(LinkList *list, ELEMENTTYPE data, int *index) 
// {
//     /* 遍历结点 */
//     int count = 1;
//     DoubleLinkNode *travelNode = list->head->next;
//     while(travelNode != NULL)
//     {
//         if (travelNode->data == data)
//         {
//             *index = count;
//             return count;
//         }
//         travelNode = travelNode->next;
//         count++;
//     }
//     /* 未找到指定值 */
//     *index = UNDERFLOW;
//     return UNDERFLOW;
// }
/* 判断两值是否相同 */


/* 链表删除指定值*/
int linkListDeleteValue(LinkList *list, ELEMENTTYPE data,int (*isSame)(ELEMENTTYPE,ELEMENTTYPE))
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
            linkListDelete(list, count);
        }
        else
        {
            travelNode = travelNode->next;
            count++;
        }
    }
}

/* 链表销毁 */
int linkListDestroy(LinkList *list)
{
    /* 判空 */
    CHECK_NULL_POINTER(list);
    /* 遍历结点 */
    while(list->tail != list->head)
    {
        /* 尾删 */
        linkListTailDelete(list);
    }
    FREE_NODE(list->head);
    FREE_NODE(list);


    return SUCCESS;
}

/* 链表遍历 */
int linkListTraverse(LinkList *list, int (*visit)(ELEMENTTYPE))
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
int linkListReverseTraverse(LinkList *list, int (*visit)(ELEMENTTYPE))
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