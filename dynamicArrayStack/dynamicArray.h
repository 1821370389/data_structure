#ifndef __DYNAMIC_ARRAY_H__
#define __DYNAMIC_ARRAY_H__
/* 避免头文件重命名*/

// #define ElemType void*
#include "common.h"
/* API ：application pragram interface */

/* 动态数组初始化 */
int dynamicArrayInit(dynamicArray *pArray, int capacity);

/* 动态数组插入数据(默认插入到数组的末尾) */
int dynamicArrayInsertData(dynamicArray *pArray, ElemType value);

/* 动态数组插入数据(在指定位置) */
int dynamicArrayAppointPosInsertData(dynamicArray *pArray, ElemType value, int pos);

/* 动态数组修改指定位置的数据 */
int dynamicArrayModifyAppointPosData(dynamicArray *pArray, ElemType value, int pos);

/* 动态数组删除数据(默认删除末尾的数据) */
int dynamicArrayDeleteData(dynamicArray *pArray);

/* 动态数组删除数据(指定位置的数据) */
int dynamicArrayDeleteAppointPosData(dynamicArray *pArray, int pos);

/* 动态数组删除数据(指定数据)*/
int dynamicArrayDeleteAppointData(dynamicArray *pArray, ElemType value);

/* 动态数组的销毁 */
int dynamicArrayDestroy(dynamicArray *pArray);

/* 获取动态数组的大小 */
int dynamicArrayGetSize(dynamicArray *pArray, int *pSize);

/* 获取动态数组的容量 */
int dynamicArrayGetCapacity(dynamicArray *pArray, int *pCapacity);

/* 获取指定位置的元素数据 */
int dynamicArrayGetAppointPosData(dynamicArray *pArray, int pos, ElemType *pValue);

#endif  //__DYNAMIC_ARRAY_H__