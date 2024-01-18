#include "hashTable.h"
#include "doubleLinkList.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define DEFAULT_SLOT_NUMS   10

/* 状态码 */
enum STATUS_CODE
{
    SUCCESS = 0,
    NULL_PTR = -1,
    MALLOC_ERROR = -2,
    ILLEGAL_ACCESS = -3,
    UNDERFLOW = -4,

};

int hashTableInit(HashTable **hashTable)
{
    HashTable * hash = (HashTable *)malloc(sizeof(HashTable));
    if(hash == NULL)
    {
        perror("malloc hashTable failed");
        return MALLOC_ERROR;
    }

    memset(hash, 0, sizeof(HashTable));
    hash->slotNums = DEFAULT_SLOT_NUMS;

    hash->slotKeyId = (hashNode*)malloc(sizeof(hashNode) * hash->slotNums);
    if(hash->slotKeyId == NULL)
    {
        perror("malloc hash->slotKeyId failed");
        return MALLOC_ERROR;
    }
    memset(hash->slotKeyId, 0, sizeof(hashNode) * hash->slotNums);

    /*  为哈希表的value初始化 
        哈希表的value是链表的虚拟头节点
        */
    DoubleLinkListInit(&hash->slotValueList);

    /* 指针解引用 */
    *hashTable = hash;

    return SUCCESS;

    return 0;
}
