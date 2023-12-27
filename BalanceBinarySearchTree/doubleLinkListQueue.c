#include "doubleLinkListQueue.h"
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
/* 队列初始化*/
int DoubleLinkListQueueInit(DoubleLinkListQueue **pQueue)
{
    return DoubleLinkListInit(pQueue);
}

/* 队列入队 */
int DoubleLinkListQueuePush(DoubleLinkListQueue *pQueue, ELEMENTTYPE data)
{
    return DoubleLinkListTailInsert(pQueue, data);
}


/* 查看队头元素 */
int DoubleLinkListQueueTop(DoubleLinkListQueue *pQueue, ELEMENTTYPE data)
{
    return DoubleLinkListGetHead(pQueue, data);
}


/* 查看队尾元素 */
int DoubleLinkListQueueBottom(DoubleLinkListQueue *pQueue, ELEMENTTYPE data)
{
    return DoubleLinkListGetTail(pQueue, data);
}


/* 队列出队 */
int DoubleLinkListQueuePop(DoubleLinkListQueue *pQueue)
{
    return DoubleLinkListHeadDelete(pQueue);
}


/* 获取队列大小 */
int DoubleLinkListQueueSize(DoubleLinkListQueue *pQueue,int *pSize)
{
    return DoubleLinkListLength(pQueue,pSize);
}


/* 判断队列是否为空 */
int DoubleLinkListQueueIsEmpty(DoubleLinkListQueue *pQueue)
{
    int size =0;
    size = DoubleLinkListLength(pQueue,&size);
    return size == 0 ? 1 : 0;
}


/* 队列销毁 */
int DoubleLinkListQueueDestroy(DoubleLinkListQueue *pQueue)
{
    return DoubleLinkListDestroy(pQueue);
}


