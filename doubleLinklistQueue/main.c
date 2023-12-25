#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "doubleLinkListQueue.h"

#define BUFFER_SIZE 10
#define DEFAULT_NUM 3

typedef struct stuInfo
{
    int age;
    char sex;
} stuInfo;

/* 打印结构体 */
int printStruct(void *data)
{
    #if 0
    printf("age = %d, sex = %c\n", ((stuInfo*)data)->age, ((stuInfo*)data)->sex);
    #else    
    stuInfo* info = (stuInfo*)data;
    printf("age = %d, sex = %c\n", info->age, info->sex);
    #endif
}

/* 打印整形 */
int printInt(void *data)
{
    printf("%d\n", *(int*)data);
}

/* 判断是否相同 */
int isEqual(void *data1, void *data2)
{
    if(*(int*)data1 == *(int*)data2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int main()
{
    DoubleLinkListQueue *queue = NULL;
    DoubleLinkListQueueInit(&queue);

    int buffer[BUFFER_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for(int idx = 0; idx < DEFAULT_NUM; idx++)
    {
        DoubleLinkListQueuePush(queue, (ELEMENTTYPE)&buffer[idx]);
    }

    int size = 0;
    DoubleLinkListQueueSize(queue, &size);
    printf("size = %d\n", size);

    int * data = NULL;
    DoubleLinkListQueueTop(queue, (ELEMENTTYPE)&data);
    DoubleLinkListQueuePop(queue);
    printf("data = %d\n", *(int*)data);
    DoubleLinkListQueueTop(queue, (ELEMENTTYPE)&data);
    DoubleLinkListQueuePop(queue);
    printf("data = %d\n", *(int*)data);

    DoubleLinkListQueueDestroy(queue);
    return 0;
}