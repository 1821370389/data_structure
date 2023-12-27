#ifndef __BALANCE_BINARY_SEARCH_TREE_H__
#define __BALANCE_BINARY_SEARCH_TREE_H__

// #define ELEMENTTYPE void*
#include "common.h"

/* 平衡二叉树节点 */
typedef struct AVLNode
{
    ELEMENTTYPE data;
    struct AVLNode* left;   // 左子树
    struct AVLNode* right;  // 右子树
    struct AVLNode* parent; // 父节点
}AVLNode;

/* 平衡二叉搜索树 */
typedef struct BalanceBinarySearchTree
{
    /* 根节点 */
    AVLNode* root;
    /* 节点数 */
    int size;
    /* 比较函数 */
    int (*compareFunc)(ELEMENTTYPE, ELEMENTTYPE);

    /* 打印函数 */
    int (*printFunc)(ELEMENTTYPE);
    
}BalanceBinarySearchTree;


/* 平衡二叉搜索树初始化 */
int AVLInit(BalanceBinarySearchTree** pTree, int (*compareFunc)(ELEMENTTYPE, ELEMENTTYPE), int (*printFunc)(ELEMENTTYPE));

/* 平衡二叉搜索树的插入 */
int AVLInsert(BalanceBinarySearchTree* pTree, ELEMENTTYPE data);

/* 平衡二叉搜索树的是否包含指定元素 */
int AVLIsContains(BalanceBinarySearchTree* pTree, ELEMENTTYPE data);

/* 获取平衡二叉搜索树的结点个数 */
int AVLGetSize(BalanceBinarySearchTree* pTree, int* count);

/* 前序遍历 */
int AVLPreOrder(BalanceBinarySearchTree* pTree);

/* 中序遍历 */
int AVLInOrder(BalanceBinarySearchTree* pTree);

/* 后序遍历 */
int AVLPostOrder(BalanceBinarySearchTree* pTree);

/* 层序遍历 */
int AVLLevelOrder(BalanceBinarySearchTree* pTree);

/* 获取平衡二叉搜素树的高度 */
int AVLGetHeight(BalanceBinarySearchTree* pTree, int *pHeight);

/* 平衡二叉搜索树的销毁 */
int AVLDestroy(BalanceBinarySearchTree* pTree);

/* 平衡二叉搜索树的节点删除 */
int AVLDelete(BalanceBinarySearchTree* pTree, ELEMENTTYPE data);

#endif // !__BINARY_SEARCH_TREE_H__
