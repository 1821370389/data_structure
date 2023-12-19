/* 动态数组 */
#include <stdio.h>
#include "dynamicArray.h"
#include <string.h>
#include <stdlib.h>


#define BUFFER_SIZE 7
#define DEFAULT_NUM 5

typedef struct stuInfo
{
    int age;
    char sex;
} stuInfo;

/* 打印数组 */
void printArray(dynamicArray * array)
{
    for(int idx = 0; idx < array->size; idx++)
    {
        printf("data = %d\n", *(int *)(array->data[idx]));
    }
}

int main()
{
    /* 静态数组 
    1. 不够灵活
    2. 可能会浪费空间
    */
    /*动态数组*/
    dynamicArray array;
    dynamicArrayInit(&array, BUFFER_SIZE);
    // free(array.data);
    // dynamicArrayInit(&array, BUFFER_SIZE);
#if 1
    /* 插入数据*/
    
    int buffer[DEFAULT_NUM] = {1, 2, 3, 2, 5};
    for(int idx = 0; idx < DEFAULT_NUM; idx++)
    {
        dynamicArrayInsertData(&array, (void *)&buffer[idx]);
    }

    /* 获取动态数组的大小 */
    int size = 0;
    int capacity = 0;
    int temp = 5;
    dynamicArrayGetSize(&array,&size);
    dynamicArrayGetCapacity(&array, &capacity);
    printf("size = %d\n", size);
    printf("capacity = %d\n", capacity);

    /* 打印数组 */
    printArray(&array);
    printf("\n");
    #if 0
    /* 删除数据*/
    dynamicArrayDeleteData(&array);
    #elif 0
    
    /* 删除特定位置数据*/
    dynamicArrayDeleteAppointPosData(&array,1);
    #elif 1
    /* 删除指定数据 */
    dynamicArrayDeleteAppointData(&array, (void *)&buffer[3]);
    #elif 0
    /* 在指定位置插入数据 */
    dynamicArrayAppointPosInsertData(&array,(void*)&buffer[4],2);
    #elif 0
    /* 修改指定位置的数据 */
    dynamicArrayModifyAppointPosData(&array,(void*)&temp,2);
    /* 获取动态数组的大小 */
    printf("array.size = %d\n", array.size);
    printf("array.capacity = %d\n", array.capacity);
    #elif 0
    /* 获取指定位置的数据 */
    dynamicArrayGetAppointPosData(&array,3,(ElemType)&temp);
    printf("temp = %d\n", temp);
    #elif 0
    /* 销毁数组*/
    temp = dynamicArrayDestroy(&array);
    printf("temp = %d\n", temp);
    // printArray(&array);
    #endif
    /* 打印数组 */
    printArray(&array);

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