#ifndef __BINARY_SEARCH_TREE_H__
#define __BINARY_SEARCH_TREE_H__

#define ELEMENTTYPE int

typedef struct BSTNode
{
    ELEMENTTYPE data;
    struct BSTNode* left;   // 左子树
    struct BSTNode* right;  // 右子树
    struct BSTNode* parent; // 父节点
}BSTNode;

typedef struct BinarySearchTree
{
    /* 根节点 */
    BSTNode* root;
    /* 节点数 */
    int size;
    
}BinarySearchTree;


/* 二叉树搜索树初始化 */
int BSTInit(BinarySearchTree** pTree);

/* 二叉搜索树的插入 */
int BSTInsert(BinarySearchTree* pTree, ELEMENTTYPE data,int (*compareFunc)(ELEMENTTYPE, ELEMENTTYPE) );

/* 前序遍历 */
int BSTPreOrder(BSTNode* pTree);

/* 中序遍历 */
int BSTInOrder(BSTNode* pTree);

/* 后序遍历 */
int BSTPostOrder(BSTNode* pTree);

/* 层序遍历 */
int BSTLevelOrder(BSTNode* pTree);

#endif // !__BINARY_SEARCH_TREE_H__
