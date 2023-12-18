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
    ILLEGAL_ACCESS = -3,
    UNDERFLOW = -4,

};

#define DEFAULT_SIZE 10

/* 静态函数前置声明 */
static int dynamicArrayExpand(dynamicArray *pArray);

/* 动态数组初始化 */
int dynamicArrayInit(dynamicArray *pArray, int capacity)
{
    /* 判断指针是否为空 */
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
    dynamicArrayAppointPosInsertData(pArray,value,pArray->size);
}

/*动态数组扩容*/
static int dynamicArrayExpand(dynamicArray *pArray)
{
    int ret = 0;
    /* 确认新空间大小 */
    int needExpandCapacity = pArray->capacity + (pArray->capacity >> 1);
#if 0
    pArray->data = (ElemType *)realloc(pArray->data, sizeof(ElemType) * needExpandCapacity);
#else
    /* 创建临时指针 */
    int *temPtr = pArray->data;

    /* 开辟新空间 */
    pArray->data = (ElemType *)malloc(sizeof(ElemType) * needExpandCapacity);

    /* 判断开辟空间是否成功 */
    if(pArray->data == NULL)
    {
        return MALLOC_ERROR;
    }

    /* 清楚脏数据 */
    memset(pArray->data, 0, sizeof(ElemType) * needExpandCapacity);

    /* 复制数据 */
    for(int idx = 0; idx < pArray->size; idx++)
    {
        pArray->data[idx] = temPtr[idx];
    }

    /* 释放旧空间 */
    if(temPtr != NULL)
    {
        free(temPtr);
        temPtr = NULL;
    }

    /* 更新新动态数组的容量 */
    pArray->capacity = needExpandCapacity;

#endif
    return ret;
}

/* 动态数组插入数据(在指定位置) */
int dynamicArrayAppointPosInsertData(dynamicArray *pArray, ElemType value, int pos)
{
    /* 判断指针是否为空 */
    if(pArray == NULL)
    {
        return NULL_PTR;
    }

    /* 判断位置的合法性 */
    if(pos < 0 || pos > pArray->size)
    {
        return ILLEGAL_ACCESS;
    }
    
    /* 判断是否需要扩容,(到上线2/3时就扩容) */
    if((pArray->size + (pArray->size >> 1)) >= pArray->capacity)
    {
        dynamicArrayExpand(pArray);
    }

    /* 为新值腾出空间 */
    for(int idx = pArray->size; idx > pos; idx--)
    {
        pArray->data[idx] = pArray->data[idx - 1];
    }
    /* 找到对应位置，填入值 */
    pArray->data[pos] = value;
    /* 数组大小+1 */
    pArray->size++;

    
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
