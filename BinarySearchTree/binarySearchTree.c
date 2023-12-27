#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binarySearchTree.h"
#include "doubleLinkListQueue.h"


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
/* 释放结点内存 */
#define FREE_NODE(node)                         \
    do                                          \
    {                                           \
        if(node != NULL)                        \
        {                                       \
            free(node);                         \
            node = NULL;                        \
        }                                       \
    } while(0)

/* 静态函数前置声明 */
/* 创建节点 */
static BSTNode* createNewBSTNode(ELEMENTTYPE data, BSTNode* parent);
/* 基于指定的值获取二叉搜索树的节点 */
static BSTNode* BSTGetNode(BinarySearchTree* pTree, ELEMENTTYPE data);

/* 判断二叉树的深度为2 */
static int BSTisSearchTree2(BSTNode* node);
/* 判断二叉树的搜索树度为1 */
static int BSTisSearchTree(BSTNode* node);
/* 判断二叉树的搜索树度为0 */
static int BSTisSearchTree0(BSTNode* node);

/* 获取当前结点的前驱结点 */
static BSTNode* BSTGetPreNode(BSTNode* node);
/* 获取当前结点的后继结点 */
static BSTNode* BSTGetNextNode(BSTNode* node);


/* 二叉树搜索树初始化 */
int BSTInit(BinarySearchTree** pTree, int (*compareFunc)(ELEMENTTYPE, ELEMENTTYPE), int (*printFunc)(ELEMENTTYPE))
{
    BinarySearchTree* pNewTree = (BinarySearchTree*)malloc(sizeof(BinarySearchTree));
    CHECK_MALLOC_ERROR(pNewTree);
    /* 清除脏数据 */
    memset(pNewTree, 0, sizeof(BinarySearchTree));
    pNewTree->root = NULL;
    pNewTree->size = 0;
    pNewTree->compareFunc = compareFunc;
    pNewTree->printFunc =  printFunc;

    /* 设置根节点 */
#if 0
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
#else
    pNewTree->root = createNewBSTNode(0,NULL);
#endif

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
        flag =pTree->compareFunc(data, travelNode->data);
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
    BSTNode* newBSTNode = createNewBSTNode(data,prarentNode);
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

/* 创建节点 */
static BSTNode* createNewBSTNode(ELEMENTTYPE data, BSTNode* parent)
{
    BSTNode* pNew = (BSTNode*)malloc(sizeof(BSTNode));
    if(pNew == NULL)
    {
        return NULL;
    }
    memset(pNew, 0, sizeof(BSTNode));
    pNew->data = data;
    pNew->left = NULL;
    pNew->right = NULL;
    pNew->parent = parent;
    // *pNewNode = pNew;
    return pNew;
}

/* 基于指定的值获取二叉搜索树的节点 */
static BSTNode* BSTGetNode(BinarySearchTree* pTree, ELEMENTTYPE data)
{
    BSTNode* travelNode = pTree->root;
    int flag = 0;
    while(travelNode != NULL)
    {
        flag = pTree->compareFunc(data, travelNode->data);
        if(flag < 0)
        {
            travelNode = travelNode->left;
        }
        else if(flag > 0)
        {
            travelNode = travelNode->right;
        }
        else
        {
            return travelNode;
        }
    }
    return NULL;
}

/* 二叉搜索树的是否包含指定元素 */
int BSTIsContains(BinarySearchTree* pTree, ELEMENTTYPE data)
{
    return (BSTGetNode(pTree, data) != NULL);
}

/* 前序遍历 */
static int preOrderTravel(BSTNode* travelNode, BinarySearchTree* pTree)
{
    if(travelNode == NULL)
    {
        return SUCCESS;
    }
    pTree->printFunc(travelNode->data);
    /* 左子树 */
    preOrderTravel(travelNode->left, pTree);
    /* 右子树 */
    preOrderTravel(travelNode->right, pTree);
    return SUCCESS;

}

/* 中序遍历*/
static int inOrderTravel(BSTNode* travelNode, BinarySearchTree* pTree)
{
    if( travelNode == NULL)
    {
        return SUCCESS;
    }
    /* 左子树 */
    inOrderTravel(travelNode->left, pTree);
    pTree->printFunc(travelNode->data);
    /* 右子树 */
    inOrderTravel(travelNode->right, pTree);
    return SUCCESS;
}

/* 后序遍历 */
static int postOrderTravel(BSTNode* travelNode, BinarySearchTree* pTree)
{
    if(travelNode == NULL)
    {
        return SUCCESS;
    }
    /* 左子树 */
    postOrderTravel(travelNode->left, pTree);
    /* 右子树 */
    postOrderTravel(travelNode->right, pTree);
    pTree->printFunc(travelNode->data);
    return SUCCESS;
}

/* 二叉搜索树的前序遍历 */
int BSTPreOrder(BinarySearchTree* pTree)
{
    /* 判空 */
    CHECK_MALLOC_ERROR(pTree);
    preOrderTravel(pTree->root,pTree);
    return SUCCESS;
}

/* 二叉搜索树的中序遍历 */
int BSTInOrder(BinarySearchTree* pTree)
{
    inOrderTravel(pTree->root,pTree);
    return SUCCESS;
}

/* 二叉搜索树的后序遍历 */
int BSTPostOrder(BinarySearchTree* pTree)
{
    postOrderTravel(pTree->root,pTree);
    return SUCCESS;
}

/* 二叉搜索树的层序遍历 */
int BSTLevelOrder(BinarySearchTree* pTree)
{
    /* 判空 */
    CHECK_MALLOC_ERROR(pTree);

    DoubleLinkList * pQueue = NULL;
    DoubleLinkListQueueInit(&pQueue);
    DoubleLinkListQueuePush(pQueue, pTree->root);

    /* 遍历结点 */
    BSTNode* travelNode = NULL;
    while(!DoubleLinkListQueueIsEmpty(pQueue))
    {
        DoubleLinkListQueueTop(pQueue, (void**)&travelNode);
        DoubleLinkListQueuePop(pQueue);
        pTree->printFunc(travelNode->data);

        /* 左子树入队 */
        if(travelNode->left != NULL)
        {
            DoubleLinkListQueuePush(pQueue, travelNode->left);
        }
        /* 右子树入队 */
        if(travelNode->right != NULL)
        {
            DoubleLinkListQueuePush(pQueue, travelNode->right);
        }
    }

    /* 销毁队列 */
    DoubleLinkListQueueDestroy(pQueue);
    
    return SUCCESS;
}

/* 获取二叉搜素树的高度 */
int BSTGetHeight(BinarySearchTree* pTree, int *pHeight)
{

    #if 1
    int height = 0;
    /* 判空 */
    CHECK_MALLOC_ERROR(pTree);

    /* 空树 */
    if(pTree->size == 0)
    {
        return height;
    }

    DoubleLinkList * pQueue = NULL;
    DoubleLinkListQueueInit(&pQueue);
    DoubleLinkListQueuePush(pQueue, pTree->root);

    /* 树每层的结点数 */
    int levelSize = 1;
    /* 遍历结点 */
    BSTNode* travelNode = NULL;
    while(!DoubleLinkListQueueIsEmpty(pQueue))
    {
        DoubleLinkListQueueTop(pQueue, (void**)&travelNode);
        DoubleLinkListQueuePop(pQueue);
        levelSize--;
        /* 左子树入队 */
        if(travelNode->left != NULL)
        {
            DoubleLinkListQueuePush(pQueue, travelNode->left);
        }
        /* 右子树入队 */
        if(travelNode->right != NULL)
        {
            DoubleLinkListQueuePush(pQueue, travelNode->right);
        }

        /* 如果levelSize = 0 说明该层结束了*/
        if(levelSize == 0)
        {
            height++;
            DoubleLinkListQueueSize(pQueue, &levelSize);
        }
    }

    *pHeight = height;

    /* 销毁队列 */
    DoubleLinkListQueueDestroy(pQueue);
    
    return SUCCESS;
    #endif
}

/* 判断二叉树的搜索树度为2 */
static int BSTisSearchTree2(BSTNode* node)
{
    return (node->left != NULL) && (node->right != NULL);
}
/* 判断二叉树的搜索树度为1 */
static int BSTisSearchTree(BSTNode* node)
{
    return ((node->left == NULL) && (node->right != NULL)) || ((node->left != NULL) && (node->right == NULL));
}
/* 判断二叉树的搜索树度为0 */
static int BSTisSearchTree0(BSTNode* node)
{
    return (node->left == NULL) && (node->right == NULL);
}

/* 获取当前结点的前驱结点 */
static BSTNode* BSTGetPreNode(BSTNode* node)
{
    BSTNode* pNode = NULL;
    #if 0
    /* 度为2 */
    if(BSTisSearchTree2(node))
    {
        /* 前驱结点是左子树的(右子树的)*n子树*/
        pNode = node->left;
        while(pNode->right != NULL)
        {
            pNode = pNode->right;
        }
        return pNode;
    }
    /* 程序到这里一定是度为1/0*/
    /* 度为1 */
    if(BSTisSearchTree(node))
    {
        pNode = node->parent;
        if(pNode->left == node)
        {
            pNode = pNode->parent;
        }

    }
    #else
    if (node->left != NULL)
    {
        pNode = node->left;
        while(pNode->right != NULL)
        {
            pNode = pNode->right;
        }
        return pNode;
    }
    #if 0
    else
    {
        pNode = node;

        while(pNode->parent != NULL)
        {
            if(pNode->parent->left == pNode)
            {
                return pNode->parent;
            }
            pNode = pNode->parent;
        }
        return NULL;
        
    }
    #else
    while(node->parent != NULL && node->parent->left != node)
    {
        node = node->parent;
    }
    return node->parent;
    #endif

    #endif

}
/* 获取当前结点的后继结点 */
static BSTNode* BSTGetNextNode(BSTNode* node)
{
    BSTNode* pNode = NULL;
    if(node->right != NULL)
    {
        pNode = node->right;
        while(pNode->left != NULL)
        {
            pNode = pNode->left;
        }
        return pNode;
    }
    #if 0
    else
    {
        pNode = node;
        while(pNode != NULL)
        {
            if(pNode->parent->right == pNode)
            {
                return pNode->parent;
            }
            pNode = pNode->parent;
        }
        return NULL;
    }
    #else
    while(node->parent != NULL && node->parent->right != node)
    {
        node = node->parent;
    }
    return node->parent;
    #endif
}

/* 二叉搜索树的销毁 */
int BSTDestroy(BinarySearchTree* pTree)
{
    /* 判空 */
    CHECK_MALLOC_ERROR(pTree);

    /* 层序遍历 */
    BSTNode* travelNode = NULL;
    DoubleLinkList * pQueue = NULL;
    DoubleLinkListQueueInit(&pQueue);
    DoubleLinkListQueuePush(pQueue, pTree->root);
    while(!DoubleLinkListQueueIsEmpty(pQueue))
    {
        DoubleLinkListQueueTop(pQueue, (void**)&travelNode);
        DoubleLinkListQueuePop(pQueue);
        if(travelNode->left != NULL)
        {
            DoubleLinkListQueuePush(pQueue, travelNode->left);
        }
        if(travelNode->right != NULL)
        {
            DoubleLinkListQueuePush(pQueue, travelNode->right);
        }
        FREE_NODE(travelNode);
    }
    DoubleLinkListQueueDestroy(pQueue);
    FREE_NODE(pTree);
    
    return SUCCESS;
}
