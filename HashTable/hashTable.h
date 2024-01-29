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

/* 哈希表 插入<key,value> */
int hashTableInsert(HashTable* hashTable, int key, int value);

/* 哈希表 删除key */
int hashTableDelete(HashTable* hashTable, int key);

/* 哈希表 根据key获取value */
int hashTableGetValueByKey(HashTable* hashTable, int key);

#endif
