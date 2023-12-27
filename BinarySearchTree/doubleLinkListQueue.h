#ifndef __DOUBLELINKLIST_QUEUE_H__
#define __DOUBLELINKLIST_QUEUE_H__

#include "common.h"
typedef DoubleLinkList DoubleLinkListQueue;

/* 队列初始化*/
int DoubleLinkListQueueInit(DoubleLinkListQueue **pQueue);

/* 队列入队 */
int DoubleLinkListQueuePush(DoubleLinkListQueue *pQueue, ELEMENTTYPE data);

/* 查看队头元素 */
int DoubleLinkListQueueTop(DoubleLinkListQueue *pQueue, ELEMENTTYPE data);

/* 查看队尾元素 */
int DoubleLinkListQueueBottom(DoubleLinkListQueue *pQueue, ELEMENTTYPE data);

/* 队列出队 */
int DoubleLinkListQueuePop(DoubleLinkListQueue *pQueue);

/* 获取队列大小 */
int DoubleLinkListQueueSize(DoubleLinkListQueue *pQueue,int *pSize);

/* 判断队列是否为空 */
int DoubleLinkListQueueIsEmpty(DoubleLinkListQueue *pQueue);

/* 队列销毁 */
int DoubleLinkListQueueDestroy(DoubleLinkListQueue *pQueue);


#endif