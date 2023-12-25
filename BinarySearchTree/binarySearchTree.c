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


/* 比较大小 */
static int compareFunc(ELEMENTTYPE data1, ELEMENTTYPE data2)
{
    return data1 - data2;
}
/* 新建节点 */
static int newTreeNode(BSTNode** pNewNode, ELEMENTTYPE data)
{
    BSTNode* pNew = (BSTNode*)malloc(sizeof(BSTNode));
    CHECK_MALLOC_ERROR(pNew);
    memset(pNew, 0, sizeof(BSTNode));
    pNew->data = data;
    pNew->left = NULL;
    pNew->right = NULL;
    pNew->parent = NULL;
    *pNewNode = pNew;
    return SUCCESS;
}

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
    /* 空树 */
    if(pTree->size == 0)
    {
        pTree->root->data = data;
        pTree->size++;
        return SUCCESS;
    }
    /* 非空树 */
    BSTNode* travelNode = pTree->root;  //遍历节点
    BSTNode* prarentNode = pTree->root; //父节点
    /* 记录符号 */
    int flag = 0;
    while(travelNode != NULL)
    {
        /* 标记父节点 */
        prarentNode = travelNode;
        flag =compareFunc(travelNode->data, data);
        if(flag < 0)
        {
            /* 左子树 */
            travelNode = travelNode->left;
        }
        else if(flag > 0)
        {
            /* 右子树 */
            travelNode = travelNode->right;
        }
        else
        {
            /* 重复元素 */
            /* 视情况修改，此处默认不管，直接跳过 */
            return SUCCESS;
        }
    }
    /* 插入新节点 */
    BSTNode* newBSTNode = NULL;
    newTreeNode(&newBSTNode, data);
    newBSTNode->parent = prarentNode;
    if(flag < 0)
    {
        prarentNode->left = newBSTNode;
    }
    else
    {
        prarentNode->right = newBSTNode;
    }

    /* 更新结点数 */
    pTree->size++;

    return SUCCESS;
}