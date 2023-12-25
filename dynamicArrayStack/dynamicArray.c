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
static int dynamicArrayShrink(dynamicArray *pArray);

/* 检查指针是否为空的宏函数 */
#define CHECK_NULL_POINTER(ptr) \
    do \
    { \
        if(ptr == NULL) \
        { \
            return NULL_PTR; \
        }\
    } while(0)  
/* 避免传入非法值 */
#define CHECK_ILLEGAL_ACCESS(index) \
    do \
    { \
        if(index <= 0 ) \
        { \
            return ILLEGAL_ACCESS; \
        } \
    } while(0)
/* 判断位置的合法性 */
#define CHECK_POSITION(index, pArray) \
    do \
    { \
        if(index < 0 || index > pArray->size) \
        { \
            return ILLEGAL_ACCESS; \
        } \
    } while(0)


/* 动态数组初始化 */
int dynamicArrayInit(dynamicArray *pArray, int capacity)
{
    /* 判断指针是否为空 */
    CHECK_NULL_POINTER(pArray);

    /* 避免传入非法值 */
    CHECK_ILLEGAL_ACCESS(capacity);

    /* 为动态数组分配内存 */
    pArray->data = (ElemType *)malloc(sizeof(ElemType) * capacity);
    if(pArray->data == NULL)
    {
        return MALLOC_ERROR;
    }
    /* 初始化(清除脏数据) */
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
    return SUCCESS;
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
    ElemType *temPtr = pArray->data;

    /* 开辟新空间 */
    pArray->data = (ElemType *)malloc(sizeof(ElemType) * needExpandCapacity);

    /* 判断开辟空间是否成功 */
    if(pArray->data == NULL)
    {
        return MALLOC_ERROR;
    }

    /* 清除脏数据 */
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
    CHECK_NULL_POINTER(pArray);

    /* 判断位置的合法性 */
    CHECK_POSITION(pos, pArray);
    
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

    return SUCCESS;
}

/* 动态数组修改指定位置的数据 */
int dynamicArrayModifyAppointPosData(dynamicArray *pArray, ElemType value, int pos)
{
    /* 判断指针是否为空 */
    CHECK_NULL_POINTER(pArray);

    /* 判断位置的合法性 */
    if(pos < 0 || pos >= pArray->size)
    {
        return ILLEGAL_ACCESS;
    }

    /* 修改数据 */
    pArray->data[pos] = value;

    return SUCCESS;

}

/* 动态数组删除数据(默认删除末尾的数据) */
int dynamicArrayDeleteData(dynamicArray *pArray)
{
    dynamicArrayDeleteAppointPosData(pArray,pArray->size - 1);
    return SUCCESS;
}

/* 动态数组缩容 */
static int dynamicArrayShrink(dynamicArray *pArray)
{
    /* 确认新空间大小 */
    int needShrinkCapacity = pArray->capacity >> 1;

    /* 创建临时指针备份旧数组头地址 */
    ElemType *temPtr = pArray->data;

    /* 开辟新空间 */
    pArray->data = (ElemType *)malloc(sizeof(ElemType) * needShrinkCapacity);
    
    /* 判断开辟空间是否成功 */
    if(pArray->data == NULL)
    {
        return MALLOC_ERROR;
    }

    /* 清除脏数据 */
    memset(pArray->data, 0, sizeof(ElemType) * needShrinkCapacity);
    
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
    pArray->capacity = needShrinkCapacity;

    return SUCCESS;
}

/* 动态数组删除数据(指定位置的数据) */
int dynamicArrayDeleteAppointPosData(dynamicArray *pArray, int pos)
{
    /* 判断指针是否为空 */
    CHECK_NULL_POINTER(pArray);

    /* 判断位置的合法性 */
    CHECK_POSITION(pos, pArray);

    /* 判断是否需要缩容 */
    if((pArray->capacity >> 1) > pArray->size)
    {
        dynamicArrayShrink(pArray);
    }

    /* 删除数据 */
    for(int idx = pos; idx < pArray->size - 1; idx++)
    {
        pArray->data[idx] = pArray->data[idx + 1];
    }

    /* 数组大小-1 */
    (pArray->size)--;
    
    return SUCCESS;
}

/* 动态数组删除数据(指定数据)*/
int dynamicArrayDeleteAppointData(dynamicArray *pArray, ElemType value)
{
    /* 判断指针是否为空 */
    CHECK_NULL_POINTER(pArray);

    for(int idx = pArray->size - 1; idx >= 0; idx--)
    {
        if(*(char*)pArray->data[idx] == *(char*)value)
        {
            dynamicArrayDeleteAppointPosData(pArray, idx);
        }
    }

    return SUCCESS;
}

/* 动态数组的销毁 */
int dynamicArrayDestroy(dynamicArray *pArray)
{
    /* 判断指针是否为空 */
    CHECK_NULL_POINTER(pArray);

    /* 释放动态数组的内存 */
    if(pArray->data != NULL)
    {
        free(pArray->data);
        pArray->data = NULL;
    }

    return SUCCESS;
}

/* 获取动态数组的大小 */
int dynamicArrayGetSize(dynamicArray *pArray, int *pSize)
{
    /* 判断指针是否为空 */
    CHECK_NULL_POINTER(pArray);

    /* 解引用 */
    if(pSize != NULL)
    {
        *pSize = pArray->size;
    }

    return SUCCESS;
}




/* 获取动态数组的容量 */
int dynamicArrayGetCapacity(dynamicArray *pArray, int *pCapacity)
{
    /* 判断指针是否为空 */
    CHECK_NULL_POINTER(pArray);

    /* 解引用 */
    if(pCapacity != NULL)
    {
        *pCapacity = pArray->capacity;
    }

    return SUCCESS;
}

/* 获取指定位置的元素数据 */
int dynamicArrayGetAppointPosData(dynamicArray *pArray, int pos, ElemType *pValue)
{
    int ret = 0;
    /* 判断指针是否为空 */
    CHECK_NULL_POINTER(pArray);

    /* 判断位置的合法性 */
    CHECK_POSITION(pos, pArray);

    if(pValue != NULL)
    {
        // memcpy(pValue, *(pArray->data + pos), sizeof(ElemType));
        *pValue = pArray->data[pos];
    }
    
    return SUCCESS;

}