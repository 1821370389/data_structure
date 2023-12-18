#ifndef __DYNAMIC_ARRAY_H__
#define __DYNAMIC_ARRAY_H__
/* 避免头文件重命名*/
typedef int ElemType;
typedef struct dynamicArray
{
    ElemType *data; /* 数组的空间*/
    int size;       /* 数组的大小 */
    int capacity;   /* 数组的容量 */
}dynamicArray;


#endif  //__DYNAMIC_ARRAY_H__