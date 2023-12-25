#include "circularLinkList.h"
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


/* 新建双链表结点 */
static CircularLinkNode *CircularLinkListNewNode(ELEMENTTYPE data)
{
    CircularLinkNode *node = (CircularLinkNode *)malloc(sizeof(CircularLinkNode));
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
    memset(node, 0, sizeof(CircularLinkNode));
    /* 初始化结点 */
    node->data = data;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

/* 遍历到指定位置 */
static int CircularLinkListFind(CircularLinkList *list, int index, CircularLinkNode **node)
{
    /* 遍历结点到插入点 */
    CircularLinkNode *travelNode = NULL;
    travelNode = list->head;
    if(index < (list->count >> 1))
    {
        /* 从头遍历 */
        printf("从头部开始了遍历\n");
        while(index--)
        {
            travelNode = travelNode->next;
        }
    }
    else
    {
        /* 从尾部开始 */
        printf("从尾部开始了遍历\n");
        while(index++ <= list->count)
        {
            travelNode = travelNode->prev;
        }
    }

    /* 返回结点指针 */
    *node = travelNode;
    return SUCCESS;   
}

/* 链表初始化 */
int CircularLinkListInit(CircularLinkList **list)
{
    CircularLinkList *pList = (CircularLinkList*)malloc(sizeof(CircularLinkList));
    CHECK_MALLOC_ERROR(pList);
    /* 清楚脏数据 */
    memset(pList, 0, sizeof(CircularLinkList));
    *list = pList;

    /*初始化头指针*/
    pList->head = (CircularLinkNode*)malloc(sizeof(CircularLinkNode));
    CHECK_MALLOC_ERROR(pList->head);
    memset(pList->head, 0, sizeof(CircularLinkNode));
    pList->head->next = pList->head;
    pList->head->prev = pList->head;
    pList->head->data = 0;

    /* 初始化长度*/
    pList->count = 0;

    return SUCCESS;
}

/* 链表头插 */
int CircularLinkListHeadInsert(CircularLinkList *list, ELEMENTTYPE data)
{
    return CircularLinkListInsert(list, 1, data);
}

/* 链表尾插 */
int CircularLinkListTailInsert(CircularLinkList *list, ELEMENTTYPE data)
{
    return CircularLinkListInsert(list, list->count + 1, data);
}

/* 链表指定位置插入 */
int CircularLinkListInsert(CircularLinkList *list, int index, ELEMENTTYPE data)
{
    index--;
    /* 检查指针是否为空 */
    CHECK_NULL_POINTER(list);
    /* 检查位置合法性 */
    CHECK_POSITION(index, list);

    /* 新建结点 */
    CircularLinkNode *newNode = CircularLinkListNewNode(data);

    /* 遍历结点 */
    CircularLinkNode *travelNode = NULL;
    CircularLinkListFind(list, index, &travelNode);
    
    /* 插入结点 */

    newNode->prev = travelNode;
    newNode->next = travelNode->next;
    travelNode->next->prev = newNode;
    travelNode->next = newNode;

    /* 更新结点数 */
    list->count++;

    return SUCCESS;
}

/* 获取链表长度(结点个数) */
int CircularLinkListLength(CircularLinkList *list, int *length)
{
    /* 判空 */
    CHECK_NULL_POINTER(list);
    *length = list->count;
    return SUCCESS;
}

/* 获取指定位置数据 */
int CircularLinkListGet(CircularLinkList *list, int index, ELEMENTTYPE *data)
{
    /* 判空 */
    CHECK_NULL_POINTER(list);
    /* 检查位置合法性 */
    CHECK_POSITION(index, list);

    /* 遍历结点 */
    CircularLinkNode *travelNode = NULL;
    CircularLinkListFind(list, index, &travelNode);
    *data = travelNode->data;
    return SUCCESS;
}

/* 链表头删 */
int CircularLinkListHeadDelete(CircularLinkList *list)
{
    return CircularLinkListDelete(list, 1);
}

/* 链表尾删 */
int CircularLinkListTailDelete(CircularLinkList *list)
{
    return CircularLinkListDelete(list, list->count);
}

/* 链表指定位置删除 */
int CircularLinkListDelete(CircularLinkList *list, int index)
{
    /* 判空 */
    CHECK_NULL_POINTER(list);
    /* 检查位置合法性 */
    CHECK_POSITION(index, list);
    if(index == 0)
    {
        return UNDERFLOW; /* 头结点不能删 */
    }

    /* 遍历结点 */
    CircularLinkNode *travelNode = NULL;
    CircularLinkListFind(list, index, &travelNode);

    /* 删除结点 */
    travelNode->prev->next = travelNode->next;
    travelNode->next->prev = travelNode->prev;
    FREE_NODE(travelNode);
    list->count--;

    return SUCCESS;
}

/* 链表删除指定值*/
int CircularLinkListDeleteValue(CircularLinkList *list, ELEMENTTYPE data, int (*isSame)(ELEMENTTYPE,ELEMENTTYPE))
{
    /* 判空 */
    CHECK_NULL_POINTER(list);

    /* 遍历结点 */
    int count = 1;
    CircularLinkNode *travelNode = list->head->next;
    while(travelNode != list->head)
    {
        if (isSame(travelNode->data, data))
        {
            travelNode = travelNode->next;
            CircularLinkListDelete(list, count);
            /* 这里必须先移动遍历指针，不如指针指的结点删除后指针会无法正确找到下一位 */
        }
        else
        {
            travelNode = travelNode->next;
            count++;
        }
    }
    return SUCCESS;
}

/* 链表销毁 */
int CircularLinkListDestroy(CircularLinkList *list)
{
    /* 判空 */
    CHECK_NULL_POINTER(list);
    /* 遍历结点 */
    while(list->head->next != list->head)
    {
        /* 尾删 */
        CircularLinkListTailDelete(list);
    }
    /* 释放头结点 */
    FREE_NODE(list->head);
    /* 释放链表 */
    FREE_NODE(list);

    return SUCCESS;
    
}

/* 链表遍历 */
int CircularLinkListTraverse(CircularLinkList *list, int (*visit)(ELEMENTTYPE))
{
    /* 判空 */
    CHECK_NULL_POINTER(list);

    /* 遍历 */
    CircularLinkNode *travelNode = list->head;
    while(travelNode->next != list->head)
    {
        travelNode = travelNode->next;
        visit(travelNode->data);
    }

    return SUCCESS;
}

/* 逆序遍历 */
int CircularLinkListReverseTraverse(CircularLinkList *list, int (*visit)(ELEMENTTYPE))
{
    /* 判空 */
    CHECK_NULL_POINTER(list);

    /* 遍历 */
    CircularLinkNode *travelNode = list->head;
    while(travelNode->prev != list->head)
    {
        travelNode = travelNode->prev;
        visit(travelNode->data);
    }

    return SUCCESS;    
}
