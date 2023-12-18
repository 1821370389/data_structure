/* 动态数组 */
#include <stdio.h>
#include "dynamicArray.h"
#include <string.h>


#define BUFFER_SIZE 7
#define DEFAULT_NUM 3

typedef struct stuInfo
{
    int age;
    char sex;
} stuInfo;


int main()
{
    /* 静态数组 
    1. 不够灵活
    2. 可能会浪费空间
    */
    /*动态数组*/
    dynamicArray array;
    dynamicArrayInit(&array, BUFFER_SIZE);
#if 0
    /* 插入数据*/
    {
        dynamicArrayInsertData(&array, 3);
        for(int idx = 1; idx <= DEFAULT_NUM; idx++)
        {
            dynamicArrayInsertData(&array, 21);
        }
    }

    {
        /* 获取动态数组的大小 */
        int size = 0;
        dynamicArrayGetSize(&array,&size);
        printf("size = %d\n", size);
    }

    /* 打印数组 */
    for(int idx = 0; idx < size; idx++)
    {
        int data = 0;
        dynamicArrayGetAppointPosData(&array, idx, &data);
        printf("data = %d\n", data);
    }

    /* 删除数据*/
    dynamicArrayDeleteData(&array);

    dynamicArrayGetSize(&array,&size);
    /* 获取动态数组的大小 */
    printf("size = %d\n", size);

    /* 打印数组 */
    for(int idx = 0; idx < size; idx++)
    {
        int data = 0;
        dynamicArrayGetAppointPosData(&array, idx, &data);
        printf("data = %d\n", data);
    }
#elif 0
    int buffer[DEFAULT_NUM] = {1,2,3};
    for(int idx = 0; idx < DEFAULT_NUM; idx++)
    {
        dynamicArrayInsertData(&array, (void *)&buffer[idx]);
    }

    int size = 0;
    dynamicArrayGetSize(&array, &size);
    printf("size = %d\n", size);

    int * data = NULL;
    for(int idx = 0; idx < DEFAULT_NUM; idx++)
    {
        dynamicArrayGetAppointPosData(&array, idx, (void *)&data);
        printf("data = %d\n", *data);
    }
#elif 1
    int idx  = 0;
    for(idx; idx < DEFAULT_NUM; idx++)
    {
        dynamicArrayInsertData(&array, (void *)&idx);
    }

    int size = 0;
    dynamicArrayGetSize(&array, &size);
    printf("size = %d\n", size);

    int * data = NULL;
    for(int idx = 0; idx < DEFAULT_NUM; idx++)
    {
        dynamicArrayGetAppointPosData(&array, idx, (void *)&data);
        printf("data = %d\n", *data);
    }
#else
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
    for(int idx = 0; idx < DEFAULT_NUM; idx++)
    {
        dynamicArrayInsertData(&array, (void *)&buffer[idx]);
    }

    int size = 0;
    dynamicArrayGetSize(&array,&size);
    printf("size = %d\n", size);
    

    stuInfo * info = NULL;
    // memset(&info,0,sizeof(info));
    for(int idx = 0; idx < DEFAULT_NUM; idx++)
    {
        dynamicArrayGetAppointPosData(&array, idx, (void *)&info);
        printf("info.age = %d, info.sex = %c\n", info->age, info->sex);
    }
#endif 

    return 0;
}