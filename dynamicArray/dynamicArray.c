#include <stdio.h>
#include "dynamicArray.h"
#include <stdlib.h>
#include <string.h>

/* 状态码 */
enum STATUS_CODE
{
    SUCCESS = 0,
    NULL_PTR = -1,
    MALLOC_ERROR = -2,
    OVERFLOW = -3,
    UNDERFLOW = -4,

};

#define DEFAULT_SIZE 10

/* 动态数组初始化 */
int dynamicArrayInit(dynamicArray *pArray, int capacity)
{
    if(pArray == NULL)
    {
        return NULL_PTR;
    }

    /* 避免传入非法值 */
    if(capacity <= 0)
    {
        capacity = DEFAULT_SIZE;
    }

    /* 为动态数组分配内存 */
    pArray->data = (ElemType *)malloc(sizeof(ElemType) * capacity);
    if(pArray->data == NULL)
    {
        return MALLOC_ERROR;
    }
    /* 初始化(清楚脏数据) */
    memset(pArray->data, 0, sizeof(ElemType) * capacity);
    /* 初始化动态数组的参数属性 */
    pArray->size = 0;
    pArray->capacity = capacity;
    return SUCCESS;

}

/* 动态数组插入数据(默认插入到数组的末尾) */
int dynamicArrayInsertData(dynamicArray *pArray, ElemType value)
{

}
/* 动态数组插入数据(在指定位置) */
int dynamicArrayAppointPosInsertData(dynamicArray *pArray, ElemType value, int pos)
{

}
/* 动态数组修改指定位置的数据 */
int dynamicArrayModifyAppointPosData(dynamicArray *pArray, ElemType value, int pos)
{

}
/* 动态数组删除数据(默认删除末尾的数据) */
int dynamicArrayDeleteData(dynamicArray *pArray)
{

}
/* 动态数组删除数据(指定位置的数据) */
int dynamicArrayDeleteAppointPosData(dynamicArray *pArray, int pos)
{

}
/* 动态数组删除数据(指定数据)*/
int dynamicArrayDeleteAppointData(dynamicArray *pArray, ElemType value)
{

}
/* 动态数组的销毁 */
int dynamicArrayDestroy(dynamicArray *pArray)
{

}
/* 获取动态数组的大小 */
int dynamicArrayGetSize(dynamicArray *pArray, int *pSize)
{

}
/* 获取动态数组的容量 */
int dynamicArrayGetCapacity(dynamicArray *pArray, int *pCapacity)
{

}
