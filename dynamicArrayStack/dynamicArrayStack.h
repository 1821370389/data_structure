#ifndef __DYNAMIC_ARRAY_STACK_H__
#define __DYNAMIC_ARRAY_STACK_H__
/* 避免头文件重命名*/

/* 栈的初始化 */
int dynamicArrayStackInit(int capacity);

/* 压栈 */
int dynamicArrayStackPush(int value);

/* 查看栈顶元素 */
int dynamicArrayStackTop();

/* 出栈 */
int dynamicArrayStackPop();

/* 获得栈的大小 */
int dynamicArrayStackSize();

/* 判断栈是否为空 */
int dynamicArrayStackEmpty();

/* 栈的销毁 */
int dynamicArrayStackDestroy();

#endif  //__DYNAMIC_ARRAY_H__