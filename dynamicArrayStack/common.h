#ifndef __COMMON_H_
#define __COMMON_H_

typedef void * ElemType;
typedef struct dynamicArray
{
    ElemType *data; /* 数组的空间*/
    int size;       /* 数组的大小 */
    int capacity;   /* 数组的容量 */
}dynamicArray;
typedef dynamicArray dynamicArrayStack;


#endif // __COMMON_H_