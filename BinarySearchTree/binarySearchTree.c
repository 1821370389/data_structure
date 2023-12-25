#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binarySearchTree.h"

/* 状态码 */
enum STATUS_CODE
{
    SUCCESS = 0,
    NULL_PTR = -1,
    MALLOC_ERROR = -2,
    ILLEGAL_ACCESS = -3,
    UNDERFLOW = -4,
};

/* 宏函数 */
/* 检测分配空间是否成功 */
#define CHECK_MALLOC_ERROR(ptr)                 \
    do                                          \
    {                                           \
        if(ptr == NULL)                         \
        {                                       \
            return MALLOC_ERROR;                \
        }                                       \
    } while(0)

/* 二叉树搜索树初始化 */
int BSTInit(BinarySearchTree** pTree)
{
    BinarySearchTree* pNewTree = (BinarySearchTree*)malloc(sizeof(BinarySearchTree));
    CHECK_MALLOC_ERROR(pNewTree);
    /* 清除脏数据 */
    memset(pNewTree, 0, sizeof(BinarySearchTree));

    /* 设置根节点 */
    
    pNewTree->root = NULL;
    pNewTree->size = 0;

    pNewTree->root = (BSTNode*)malloc(sizeof(BSTNode));
    CHECK_MALLOC_ERROR(pNewTree->root);
    memset(pNewTree->root, 0, sizeof(BSTNode));

    /* 初始化根节点 */
    pNewTree->root->data = 0;
    pNewTree->root->left = NULL;
    pNewTree->root->right = NULL;
    pNewTree->root->parent = NULL;

    *pTree = pNewTree;
    return SUCCESS;
}

/* 二叉搜索树的插入 */
int BSTInsert(BinarySearchTree* pTree, ELEMENTTYPE data)
{

}