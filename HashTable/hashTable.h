#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#include "common.h"

#define SLOT_CAPACITY 10    // 插槽容量

/* 重定义双链表节点 */
typedef DoubleLinkNode hashNode;

typedef struct hashTable
{
    int slotNums;
    hashNode *slotKeyId;
    DoubleLinkList *slotValueList;
} HashTable;

/* 哈希表的初始化 */
int hashTableInit(HashTable** hashTable);


#endif
