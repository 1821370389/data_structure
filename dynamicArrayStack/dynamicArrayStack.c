#include "dynamicArrayStack.h"
#include "dynamicArray.h"
#define STACK_INIT_SIZE 10

/* 栈的初始化 */
int dynamicArrayStackInit(dynamicArrayStack * pStack)
{
    return dynamicArrayInit(pStack, STACK_INIT_SIZE);
}

/* 压栈 */
int dynamicArrayStackPush(dynamicArrayStack * pStack,ElemType value)
{
    /* 调用动态数组的尾插 */
    return dynamicArrayInsertData(pStack, value);
}

/* 查看栈顶元素 */
int dynamicArrayStackTop(dynamicArrayStack * pStack, ElemType * pValue)
{
    /* 调用动态数组的查看指定位置的数据 */
    return dynamicArrayGetAppointPosData(pStack, pStack->size-1, pValue);
}

/* 出栈 */
int dynamicArrayStackPop(dynamicArrayStack * pStack)
{
    /* 调用动态数组的删除尾部数据 */
    return dynamicArrayDeleteData(pStack);
}

/* 获得栈的大小 */
int dynamicArrayStackSize(dynamicArrayStack * pStack, int * pSize)
{
    return dynamicArrayGetSize(pStack, pSize);
}

/* 判断栈是否为空 */
int dynamicArrayStackEmpty(dynamicArrayStack * pStack)
{
    int size = 0;
    dynamicArrayStackSize(pStack, &size);
    return size == 0 ? 1 : 0;
}

/* 栈的销毁 */
int dynamicArrayStackDestroy(dynamicArrayStack * pStack)
{
    return dynamicArrayDestroy(pStack);
}