#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "circularLinkList.h"

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
    CircularLinkList *list = NULL;
    CircularLinkListInit(&list);
    /* ELEMENTTYPE int 是的测试*/
#if 1
    /* 往链表里塞数据 */
    int buffer[BUFFER_SIZE] = {1,2,3,4,5,6,7,8,9,10};
    for(int idx = 0; idx < BUFFER_SIZE; idx++)
    {
        #if 0/* 尾插*/
        CircularLinkListTailInsert(list, (void*)&buffer[idx]);
        #else/* 头插*/
        CircularLinkListHeadInsert(list, (void*)&buffer[idx]);
        #endif
    }
    /* 从指定位置插入 */
    CircularLinkListInsert(list, 6, (void*)&buffer[3]);
    /* 获取链表的长度 */
    int len = 0;
    CircularLinkListLength(list, &len);
    printf("len = %d\n", len);

    /* 遍历数组 */
    printf("遍历数组\n");
    CircularLinkListTraverse(list,printInt);

    /* 逆序遍历 */
    printf("逆序遍历\n");
    CircularLinkListReverseTraverse(list,printInt);

    /* 获取指定位置的值 */
    int *data = (int *)malloc(sizeof(int));
    CircularLinkListGet(list, 2, (void*)&data);
    printf("data = %d\n", *(int*)data);

    #if 1
    /* 尾删 */
    CircularLinkListTailDelete(list);
    #else
    /* 头删 */
    CircularLinkListHeadDelete(list);
    #endif

    #if 0
    /* 删除特定位置 */
    CircularLinkListDelete(list, 2);
    #else
    /* 删除指定数据 */
    int temp = 4;
    CircularLinkListDeleteValue(list, (void*)&temp,isEqual);
    #endif

    /* 遍历数组 */
    printf("遍历数组\n");
    CircularLinkListTraverse(list,printInt);

    /* 销毁 */
    printf("销毁\n");
    printf("%d\n",CircularLinkListDestroy(list)) ;

    

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
        CircularLinkListTailInsert(list, (void*)&buffer[idx]);
    }

    /* 获取链表的长度 */
    int len = 0;
    CircularLinkListLength(list, &len);
    printf("len = %d\n", len);

    /* 遍历数组 */
    CircularLinkListTraverse(list,printStruct);

#endif
    return 0;
}