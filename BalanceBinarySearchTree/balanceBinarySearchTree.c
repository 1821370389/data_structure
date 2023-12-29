#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "balanceBinarySearchTree.h"
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

/* 宏定义 */
#define true 1
#define false 0

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
static AVLNode* createNewAVLNode(ELEMENTTYPE data, AVLNode* parent);
/* 基于指定的值获取平衡二叉搜索树的节点 */
static AVLNode* AVLGetNode(BalanceBinarySearchTree* pTree, ELEMENTTYPE data);

/* 前序遍历 */
static int preOrderTravel(AVLNode* travelNode, BalanceBinarySearchTree* pTree);
/* 中序遍历*/
static int inOrderTravel(AVLNode* travelNode, BalanceBinarySearchTree* pTree);
/* 后序遍历 */
static int postOrderTravel(AVLNode* travelNode, BalanceBinarySearchTree* pTree);
/* 左右子树入队 */
static void AVLLeftRightPush(DoubleLinkList * pQueue, AVLNode* node);


/* 判断平衡二叉树的深度为2 */
static int AVLChildHad2(AVLNode* node);
/* 判断平衡二叉树的搜索树度为1 */
static int AVLChildHad1(AVLNode* node);
/* 判断平衡二叉树的搜索树度为0 */
static int AVLChildHad0(AVLNode* node);

/* 获取当前结点的前驱结点 */
static AVLNode* AVLGetPreNode(AVLNode* node);
/* 获取当前结点的后继结点 */
static AVLNode* AVLGetNextNode(AVLNode* node);

/* 平衡二叉搜索树的节点删除 */
static int AVLDeleteNode(AVLNode* pNode, BalanceBinarySearchTree* pTree);

/* 平衡二叉搜索树添加节点后... */
static int AVLAddNodeAfter(AVLNode* pNode, BalanceBinarySearchTree* pTree);
/* 删除节点后...*/
static int AVLDeleteNodeAfter(AVLNode* pNode, BalanceBinarySearchTree* pTree);
/* 计算节点的平衡因子 */
static int AVLGetBalanceFactor(AVLNode* node);
/* 判断节点是否平衡 */
static int AVLIsBalance(AVLNode* node);
/* 更新节点高度 */
static int AVLNodeUpdateHeight(AVLNode*pNode);

/* 比较两数返回最大值 */
static int Max(int a, int b);

/* 调整平衡 */
static int AVLBalance(AVLNode* pNode, BalanceBinarySearchTree* pTree);
/* 左左平衡 */
static int AVLLeftLeftBalance(AVLNode* pNode, BalanceBinarySearchTree* pTree);
/* 左右平衡 */
static int AVLLeftRightBalance(AVLNode* pNode, BalanceBinarySearchTree* pTree);
/* 右左平衡 */
static int AVLRightLeftBalance(AVLNode* pNode, BalanceBinarySearchTree* pTree);
/* 右右平衡 */
static int AVLRightRightBalance(AVLNode* pNode, BalanceBinarySearchTree* pTree);
/* LLRR旋转的公共部分*/
static int AVLRotate(BalanceBinarySearchTree* pTree,AVLNode* pChildNode, AVLNode* pParentNode, AVLNode* pGrandNode );
/* 返回更高的子节点 */
static AVLNode* AVLGetHighestNode(AVLNode* node);

/* 判断当前节点是否父节点的左节点 */
static int AVLIsParentLeft(AVLNode* pNode);
/* 判断当前节点是否父节点的右节点 */
static int AVLIsParentRight(AVLNode* pNode);

/* 平衡二叉树搜索树初始化 */
int AVLInit(BalanceBinarySearchTree** pTree, int (*compareFunc)(ELEMENTTYPE, ELEMENTTYPE), int (*printFunc)(ELEMENTTYPE))
{
    BalanceBinarySearchTree* pNewTree = (BalanceBinarySearchTree*)malloc(sizeof(BalanceBinarySearchTree));
    CHECK_MALLOC_ERROR(pNewTree);
    /* 清除脏数据 */
    memset(pNewTree, 0, sizeof(BalanceBinarySearchTree));
    pNewTree->root = NULL;
    pNewTree->size = 0;
    pNewTree->compareFunc = compareFunc;
    pNewTree->printFunc =  printFunc;

    /* 设置根节点 */
#if 0
    pNewTree->root = NULL;
    pNewTree->size = 0;

    pNewTree->root = (AVLNode*)malloc(sizeof(AVLNode));
    CHECK_MALLOC_ERROR(pNewTree->root);
    memset(pNewTree->root, 0, sizeof(AVLNode));

    /* 初始化根节点 */
    pNewTree->root->data = 0;
    pNewTree->root->left = NULL;
    pNewTree->root->right = NULL;
    pNewTree->root->parent = NULL;
#else
    pNewTree->root = createNewAVLNode(0,NULL);
#endif

    *pTree = pNewTree;
    return SUCCESS;
}

/* 平衡二叉搜索树的插入 */
int AVLInsert(BalanceBinarySearchTree* pTree, ELEMENTTYPE data)
{
    /* 空树 */
    if(pTree->size == 0)
    {
        pTree->root->data = data;
        pTree->size++;
        AVLAddNodeAfter(pTree->root, pTree);
        return SUCCESS;
    }
    /* 非空树 */
    AVLNode* travelNode = pTree->root;  //遍历节点
    AVLNode* prarentNode = pTree->root; //父节点
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
    AVLNode* newAVLNode = createNewAVLNode(data,prarentNode);
    if(flag < 0)
    {
        prarentNode->left = newAVLNode;
    }
    else
    {
        prarentNode->right = newAVLNode;
    }
    /* 调整节点高度 */
    AVLAddNodeAfter(newAVLNode, pTree);

    /* 更新结点数 */
    pTree->size++;

    return SUCCESS;
}

/* 平衡二叉搜索树的是否包含指定元素 */
int AVLIsContains(BalanceBinarySearchTree* pTree, ELEMENTTYPE data)
{
    return (AVLGetNode(pTree, data) != NULL);
}

/* 获取平衡二叉搜索树的结点个数 */
int AVLGetSize(BalanceBinarySearchTree *pTree, int *count)
{
    if(pTree == NULL)
    {
        *count = 0;
        return NULL_PTR;
    }
    *count = pTree->size;
    return SUCCESS;
}

/* 平衡二叉搜索树的前序遍历 */
int AVLPreOrder(BalanceBinarySearchTree* pTree)
{
    /* 判空 */
    CHECK_MALLOC_ERROR(pTree);
    preOrderTravel(pTree->root,pTree);
    return SUCCESS;
}

/* 平衡二叉搜索树的中序遍历 */
int AVLInOrder(BalanceBinarySearchTree* pTree)
{
    inOrderTravel(pTree->root,pTree);
    return SUCCESS;
}

/* 平衡二叉搜索树的后序遍历 */
int AVLPostOrder(BalanceBinarySearchTree* pTree)
{
    postOrderTravel(pTree->root,pTree);
    return SUCCESS;
}

/* 平衡二叉搜索树的层序遍历 */
int AVLLevelOrder(BalanceBinarySearchTree* pTree)
{
    /* 判空 */
    CHECK_MALLOC_ERROR(pTree);

    DoubleLinkList * pQueue = NULL;
    DoubleLinkListQueueInit(&pQueue);
    DoubleLinkListQueuePush(pQueue, pTree->root);

    /* 遍历结点 */
    AVLNode* travelNode = NULL;
    while(!DoubleLinkListQueueIsEmpty(pQueue))
    {
        DoubleLinkListQueueTop(pQueue, (void**)&travelNode);
        DoubleLinkListQueuePop(pQueue);
        pTree->printFunc(travelNode->data);

        /* 左右子树入队 */
        AVLLeftRightPush(pQueue, travelNode);
    }

    /* 销毁队列 */
    DoubleLinkListQueueDestroy(pQueue);
    
    return SUCCESS;
}

/* 获取平衡二叉搜素树的高度 */
int AVLGetHeight(BalanceBinarySearchTree* pTree, int *pHeight)
{


    int height = 0;
    /* 判空 */
    CHECK_MALLOC_ERROR(pTree);

    /* 空树 */
    if(pTree->size == 0)
    {
        *pHeight = 0;
        return height;
    }
#if 0
    DoubleLinkList * pQueue = NULL;
    DoubleLinkListQueueInit(&pQueue);
    DoubleLinkListQueuePush(pQueue, pTree->root);

    /* 树每层的结点数 */
    int levelSize = 1;
    /* 遍历结点 */
    AVLNode* travelNode = NULL;
    while(!DoubleLinkListQueueIsEmpty(pQueue))
    {
        DoubleLinkListQueueTop(pQueue, (void**)&travelNode);
        DoubleLinkListQueuePop(pQueue);
        levelSize--;

        /* 左右子树入队 */
        AVLLeftRightPush(pQueue, travelNode);

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
#else
    *pHeight = pTree->root->height;
    return pTree->root->height;
#endif
}

/* 平衡二叉搜索树的销毁 */
int AVLDestroy(BalanceBinarySearchTree* pTree)
{
    /* 判空 */
    CHECK_MALLOC_ERROR(pTree);

    /* 层序遍历 */
    AVLNode* travelNode = NULL;
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

/* 平衡二叉搜索树的节点删除 */
int AVLDelete(BalanceBinarySearchTree* pTree, ELEMENTTYPE data)
{
    /* 判空 */
    CHECK_MALLOC_ERROR(pTree);
    return AVLDeleteNode(AVLGetNode(pTree, data), pTree);
}



/* 创建节点 */
static AVLNode* createNewAVLNode(ELEMENTTYPE data, AVLNode* parent)
{
    AVLNode* pNew = (AVLNode*)malloc(sizeof(AVLNode));
    if(pNew == NULL)
    {
        return NULL;
    }
    memset(pNew, 0, sizeof(AVLNode));
    pNew->data = data;
    pNew->height = 1;
    pNew->left = NULL;
    pNew->right = NULL;
    pNew->parent = parent;
    // *pNewNode = pNew;
    return pNew;
}

/* 基于指定的值获取平衡二叉搜索树的节点 */
static AVLNode* AVLGetNode(BalanceBinarySearchTree* pTree, ELEMENTTYPE data)
{
    AVLNode* travelNode = pTree->root;
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


/* 前序遍历 */
static int preOrderTravel(AVLNode* travelNode, BalanceBinarySearchTree* pTree)
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
static int inOrderTravel(AVLNode* travelNode, BalanceBinarySearchTree* pTree)
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
static int postOrderTravel(AVLNode* travelNode, BalanceBinarySearchTree* pTree)
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

/* 左右子树入队 */
static void AVLLeftRightPush(DoubleLinkList * pQueue, AVLNode* node)
{
    /* 左子树入队 */
    if(node->left != NULL)
    {
        DoubleLinkListQueuePush(pQueue, node->left);
    }
    /* 右子树入队 */
    if(node->right != NULL)
    {
        DoubleLinkListQueuePush(pQueue, node->right);
    }
}


/* 判断平衡二叉树的搜索树度为2 */
static int AVLChildHad2(AVLNode* node)
{
    return (node->left != NULL) && (node->right != NULL);
}
/* 判断平衡二叉树的搜索树度为1 */
static int AVLChildHad1(AVLNode* node)
{
    return ((node->left == NULL) && (node->right != NULL)) || ((node->left != NULL) && (node->right == NULL));
}
/* 判断平衡二叉树的搜索树度为0 */
static int AVLChildHad0(AVLNode* node)
{
    return (node->left == NULL) && (node->right == NULL);
}


/* 获取当前结点的前驱结点 */
static AVLNode* AVLGetPreNode(AVLNode* node)
{
    AVLNode* pNode = NULL;

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


}
/* 获取当前结点的后继结点 */
static AVLNode* AVLGetNextNode(AVLNode* node)
{
    AVLNode* pNode = NULL;
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


/* 平衡二叉搜索树的节点删除 */
static int AVLDeleteNode(AVLNode* pNode, BalanceBinarySearchTree* pTree)
{

    if(AVLChildHad2(pNode))
    {
        /* 度为2 */
        AVLNode* pPreNode = AVLGetPreNode(pNode);
        pNode->data = pPreNode->data;
        pNode = pPreNode;
    }
    /* 度为0/1 */
    /* 子节点 */
    AVLNode* pChildNode = pNode->left != NULL ? pNode->left : pNode->right ;
    if(pChildNode != NULL)
    {
        /* 度为1 */
        pChildNode->parent = pNode->parent;
        AVLDeleteNodeAfter(pNode, pTree);
        if(pNode->parent == NULL)
        {
            /* 删除根节点 */
            pTree->root = pChildNode;
        }

    }
    else
    {
        if(pNode->parent->left == pNode)
        {
            pNode->parent->left = pChildNode;
        }
        else
        {
            pNode->parent->right = pChildNode;
        }
    }
    FREE_NODE(pNode);
    pTree->size--;
    return SUCCESS;
}

/* 平衡二叉搜索树添加节点后... */
/* 新添加的节点一定是叶子节点 */
static int AVLAddNodeAfter(AVLNode* pNode, BalanceBinarySearchTree* pTree)
{
    while(pNode->parent != NULL)
    {
        pNode = pNode->parent;
        /* 函数到这里树一定不止油管节点 */
        if(AVLIsBalance(pNode))
        {
            /* 更新节点高度 */
            AVLNodeUpdateHeight(pNode);
        }
        else
        {
            /* 此处是最低的不平衡节点 */
            /* 调整平衡 */
            AVLBalance(pNode, pTree);
            /* 调整完最低不平衡节点，树就恢复平衡了 */
            break;
        }
    }
    
}

/* 删除节点后...*/
/* 删除节点后可能会影响树的平衡 */
static int AVLDeleteNodeAfter(AVLNode* pNode, BalanceBinarySearchTree* pTree)
{

}

/* 计算节点的平衡因子 */
static int AVLGetBalanceFactor(AVLNode* node)
{
    /* 左子树的高度 */
    int leftHeight = node->left == NULL ? 0 : node->left->height;
    /* 右子树的高度 */
    int rightHeight = node->right == NULL ? 0 : node->right->height;
    return leftHeight - rightHeight;
}

/* 判断节点是否平衡 */
static int AVLIsBalance(AVLNode* pNode)
{
    #if 0 
    return (AVLGetBalanceFactor(pNode)) <= 1;
    #else
    if(abs(AVLGetBalanceFactor(pNode)) <= 1)
    {
        return true;
    }
    else
    {
        return false;
    }
    #endif
}

/* 更新节点高度 */
static int AVLNodeUpdateHeight(AVLNode*pNode)
{
    #if 0
    if(AVLGetBalanceFactor(pNode)>0)
    {
        pNode->height = (pNode->left == NULL ? 0 : pNode->left->height) + 1;
    }
    else
    {
        pNode->height = pNode->right == NULL ? 0 : pNode->right->height + 1;
    }
    #else
    pNode->height = Max((pNode->left == NULL ? 0 : pNode->left->height),
    (pNode->right == NULL ? 0 : pNode->right->height)) + 1;
    #endif
    return SUCCESS;
}

/* 比较两数返回最大值 */
static int Max(int a, int b)
{
    if(a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

/* 调整平衡 */
static int AVLBalance(AVLNode* pNode, BalanceBinarySearchTree* pTree)
{
    /* LL LR RL RR */
#if 0
    int balanceFactor = AVLGetBalanceFactor(pNode);
    if(balanceFactor > 1)
    {
        /* 左子树高度大于右子树高度 */
        if(AVLGetBalanceFactor(pNode->left) > 0)
        {
            /* 左左平衡 */
            AVLLeftLeftBalance(pNode, pTree);
            /* 更新节点高度 */
            AVLNodeUpdateHeight(pNode);
            return SUCCESS;
        }
        else
        {
            /* 左右平衡 */
            AVLLeftRightBalance(pNode, pTree);
            /* 更新节点高度 */
            AVLNodeUpdateHeight(pNode);
            return SUCCESS;
        }
    }
    else if(balanceFactor < -1)
    {
        /* 右子树高度大于左子树高度 */
        if(AVLGetBalanceFactor(pNode->right) < 0)
        {
            /* 右右平衡 */
            AVLRightRightBalance(pNode, pTree);
            /* 更新节点高度 */
            AVLNodeUpdateHeight(pNode);
            return SUCCESS;
        }
        else
        {
            /* 右左平衡 */
            AVLRightLeftBalance(pNode, pTree);
            /* 更新节点高度 */
            AVLNodeUpdateHeight(pNode);
            return SUCCESS;
        }
    }
    else
    {
        /* 平衡 */
        AVLNodeUpdateHeight(pNode);
        return SUCCESS;
    }
#else

    AVLNode* pParentNode = AVLGetHighestNode(pNode);
    AVLNode* pChildNode = AVLGetHighestNode(pParentNode);
    if(AVLIsParentLeft(pParentNode))
    {
        /* 左平衡 */
        if(AVLIsParentLeft(pChildNode))
        {
            /* 左左 */
            AVLLeftLeftBalance(pParentNode,pTree);
            AVLNodeUpdateHeight(pParentNode);
        }
        else 
        {
            /* 左右 */
            AVLLeftRightBalance(pParentNode,pTree);
        }
    }
    else
    {
        /* 右平衡 */
        if(AVLIsParentRight(pChildNode))
        {
            /* 右右 */
        }
        else
        {
            /* 右左 */
        }
    }
#endif
    return SUCCESS;


}

/* 左左平衡 */
static int AVLLeftLeftBalance(AVLNode* pGrandNode, BalanceBinarySearchTree* pTree)
{
    AVLNode* pParentNode = pGrandNode->left;
    AVLNode* pChildNode = pParentNode->right;

    pGrandNode->left = pChildNode;
    pParentNode->right = pGrandNode;
#if 0
    pParentNode->parent = pGrandNode->parent;
    if(AVLIsParentLeft(pGrandNode))
    {
        pGrandNode->parent->left = pParentNode;
    }
    else if(AVLIsParentRight(pGrandNode))
    {
        pGrandNode->parent->right = pParentNode;
    }
    else
    {
        /* 根节点 */
        pTree->root = pParentNode;
    }

    if(pChildNode != NULL)
    {
        pChildNode->parent = pGrandNode;
    }

    /* 更新高度*/
    AVLNodeUpdateHeight(pGrandNode);
    AVLNodeUpdateHeight(pParentNode);
#else
    AVLRotate(pTree, pChildNode, pParentNode, pGrandNode);
#endif
}
/* 左右平衡 */
static int AVLLeftRightBalance(AVLNode* pGrandNode, BalanceBinarySearchTree* pTree)
{
    /* 先左旋再右旋*/
    AVLNode* pParentNode = pGrandNode->left;
    AVLNode* pChildNode = pParentNode->right;
    AVLNode* pChildLeftNode = pChildNode->left;
    AVLNode* pChildRightNode = pChildNode->right;
    pChildNode->left = pParentNode;
    pChildNode->right = pGrandNode;
    pParentNode->right = pChildLeftNode;
    pGrandNode->left = pChildRightNode;
    pParentNode->parent = pChildNode;
    pGrandNode->parent = pChildNode;
    if(pChildLeftNode != NULL)
    {
        pChildLeftNode->parent = pParentNode;
        AVLNodeUpdateHeight(pChildLeftNode);
        AVLNodeUpdateHeight(pParentNode);
        AVLNodeUpdateHeight(pGrandNode);
        AVLNodeUpdateHeight(pChildNode);
        return SUCCESS;
    }
    else
    {
        pTree->root = pChildNode;
        AVLNodeUpdateHeight(pChildNode);
        return SUCCESS;
    }
}
/* 右右平衡 */
static int AVLRightRightBalance(AVLNode* pGrandNode, BalanceBinarySearchTree* pTree)
{
    AVLNode* pParentNode = pGrandNode->right;
    AVLNode* pChildNode = pParentNode->left;

    pGrandNode->right = pChildNode;
    pParentNode->left = pGrandNode;

#if 0
    pParentNode->parent = pGrandNode->parent;
    if(AVLIsParentLeft(pGrandNode))
    {
        pGrandNode->parent->left = pParentNode;
    }
    else if(AVLIsParentRight(pGrandNode))
    {
        pGrandNode->parent->right = pParentNode;
    }
    else
    {
        /* 根节点 */
        pTree->root = pParentNode;
    }

    if(pChildNode != NULL)
    {
        pChildNode->parent = pGrandNode;
    }

    /* 更新高度*/
    AVLNodeUpdateHeight(pGrandNode);
    AVLNodeUpdateHeight(pParentNode);
#else
    AVLRotate(pTree, pChildNode, pParentNode, pGrandNode);
#endif
    
}
/* 右左平衡 */
static int AVLRightLeftBalance(AVLNode* pGrandNode, BalanceBinarySearchTree* pTree)
{
    AVLNode* pParentNode = pGrandNode->right;
    AVLNode* pChildNode = pParentNode->left;
    AVLNode* pChildLeftNode = pChildNode->left;
    AVLNode* pChildRightNode = pChildNode->right;
    pChildNode->left = pGrandNode;
    pChildNode->right = pParentNode;
    pGrandNode->right = pChildLeftNode;
    pParentNode->left = pChildRightNode;
    pParentNode->parent = pChildNode;
    pGrandNode->parent = pChildNode;
    if(pChildRightNode != NULL)
    {
        pChildRightNode->parent = pParentNode;
        AVLNodeUpdateHeight(pChildRightNode);
        AVLNodeUpdateHeight(pParentNode);
        AVLNodeUpdateHeight(pGrandNode);
        AVLNodeUpdateHeight(pChildNode);
        return SUCCESS;
    }
    else
    {
        pTree->root = pChildNode;
        AVLNodeUpdateHeight(pChildNode);
        return SUCCESS;
    }
}

/* LLRR旋转的公共部分*/
static int AVLRotate(BalanceBinarySearchTree* pTree,AVLNode* pChildNode, AVLNode* pParentNode, AVLNode* pGrandNode )
{
    pParentNode->parent = pGrandNode->parent;
    if(AVLIsParentLeft(pGrandNode))
    {
        pGrandNode->parent->left = pParentNode;
    }
    else if(AVLIsParentRight(pGrandNode))
    {
        pGrandNode->parent->right = pParentNode;
    }
    else
    {
        /* 根节点 */
        pTree->root = pParentNode;
    }

    if(pChildNode != NULL)
    {
        pChildNode->parent = pGrandNode;
    }

    /* 更新高度*/
    AVLNodeUpdateHeight(pGrandNode);
    AVLNodeUpdateHeight(pParentNode);

    return SUCCESS;
}

/* 返回更高的子节点 */
static AVLNode* AVLGetHighestNode(AVLNode* pNode)
{
    /* 左子树的高度 */
    int leftHeight = pNode->left == NULL ? 0 : pNode->left->height;
    /* 右子树的高度 */
    int rightHeight = pNode->right == NULL ? 0 : pNode->right->height;
    if(leftHeight > rightHeight)
    {
        return pNode->left;
    }
    else if(leftHeight < rightHeight)
    {
        return pNode->right;
    }
    else
    {
        if(pNode->parent != NULL && pNode->parent->left == pNode)
        {
            return pNode->left;
        }
        else
        {
            return pNode->right;
        }
    }
}

/* 判断当前节点是否父节点的左节点 */
static int AVLIsParentLeft(AVLNode* pNode)
{
    return pNode->parent != NULL && pNode->parent->left == pNode;
}
/* 判断当前节点是否父节点的右节点 */
static int AVLIsParentRight(AVLNode* pNode)
{
    return pNode->parent != NULL && pNode->parent->right == pNode;
}

