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

/* API ：application pragram interface */

/* 动态数组初始化 */
int dynamicArrayInit(dynamicArray *dynamicArray, int capacity);

/* 动态数组插入数据(默认插入到数组的末尾) */
int dynamicArrayInsertData(dynamicArray *dynamicArray, ElemType value);

/* 动态数组插入数据(在指定位置) */
int dynamicArrayAppointPosInsertData(dynamicArray *dynamicArray, ElemType value, int index);

/* 动态数组修改指定位置的数据 */
int dynamicArrayModifyAppointPosData(dynamicArray *dynamicArray, ElemType value, int index);

/* 动态数组删除数据(默认删除末尾的数据) */
int dynamicArrayDeleteData(dynamicArray *dynamicArray);

/* 动态数组删除数据(指定位置的数据) */
int dynamicArrayDeleteAppointPosData(dynamicArray *dynamicArray, int index);

/* 动态数组的销毁 */
int dynamicArrayDestroy(dynamicArray *dynamicArray);

/* 获取动态数组的大小 */
int dynamicArrayGetSize(dynamicArray *dynamicArray);

/* 获取动态数组的容量 */
int dynamicArrayGetCapacity(dynamicArray *dynamicArray);

#endif  //__DYNAMIC_ARRAY_H__