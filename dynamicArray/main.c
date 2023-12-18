/* 动态数组 */
#include <stdio.h>
#include "dynamicArray.h"
#include <string.h>


#define BUFFER_SIZE 7
#define DEFAULT_NUM 5

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
#endif 

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

    // dynamicArrayInsertData(&array, &stu1);
    // dynamicArrayInsertData(&array, &stu2);
    // dynamicArrayInsertData(&array, &stu3);

    return 0;
}