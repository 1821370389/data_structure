#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkList.h"

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

int main()
{
    LinkList *list = NULL;
    LinkListInit(&list);
    /* ELEMENTTYPE int 是的测试*/
#if 1
    /* 往链表里塞数据 */
    int buffer[BUFFER_SIZE] = {1,2,3,4,5,6,7,8,9,10};
    for(int idx = 0; idx < BUFFER_SIZE; ++idx)
    {
        LinkListHeadInsert(list, (void*)&buffer[idx]);
    }

    /* 获取链表的长度 */
    int len = 0;
    LinkListLen(list, &len);
    printf("len = %d\n", len);

    /* 遍历数组 */
    LinkListTraverse(list,printInt);

#elif 1

    stuInfo stu1,stu2,stu3;
    memset(&stu1,0,sizeof(stu1));
    memset(&stu2,0,sizeof(stu2));
    memset(&stu3,0,sizeof(stu3));

    stu1.age = 10;
    stu1.sex = 'M';

    stu2.age = 20;
    stu2.sex = 'F';

    stu3.age = 30;
    stu3.sex = 'M';
    stuInfo buffer[DEFAULT_NUM] = {stu1,stu2,stu3};

    for (int idx = 0; idx < DEFAULT_NUM; ++idx)
    {
        LinkListTailInsert(list, (void*)&buffer[idx]);
    }

    /* 获取链表的长度 */
    int len = 0;
    LinkListLen(list, &len);
    printf("len = %d\n", len);

    /* 遍历数组 */
    LinkListTraverse(list,printStruct);

#endif
    return 0;
}