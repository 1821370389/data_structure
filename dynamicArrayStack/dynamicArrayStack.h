#ifndef __DYNAMIC_ARRAY_STACK_H__
#define __DYNAMIC_ARRAY_STACK_H__
/* 避免头文件重命名*/

#include "common.h"

/* 栈的初始化 */
int dynamicArrayStackInit(dynamicArrayStack * pStack);

/* 压栈 */
int dynamicArrayStackPush(dynamicArrayStack * pStack,ElemType value);

/* 查看栈顶元素 */
int dynamicArrayStackTop(dynamicArrayStack * pStack,ElemType* pValue);

/* 出栈 */
int dynamicArrayStackPop(dynamicArrayStack * pStack);

/* 获得栈的大小 */
int dynamicArrayStackSize(dynamicArrayStack * pStack, int * pSize);

/* 判断栈是否为空 */
int dynamicArrayStackEmpty(dynamicArrayStack * pStack);

/* 栈的销毁 */
int dynamicArrayStackDestroy(dynamicArrayStack * pStack);

#endif  //__DYNAMIC_ARRAY_H__