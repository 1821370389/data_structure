#ifndef __BINARY_SEARCH_TREE_H__
#define __BINARY_SEARCH_TREE_H__

#define ELEMENTTYPE int

/* 二叉树节点 */
typedef struct BSTNode
{
    ELEMENTTYPE data;
    struct BSTNode* left;   // 左子树
    struct BSTNode* right;  // 右子树
    struct BSTNode* parent; // 父节点
}BSTNode;

/* 二叉搜索树 */
typedef struct BinarySearchTree
{
    /* 根节点 */
    BSTNode* root;
    /* 节点数 */
    int size;
    /* 比较函数 */
    int (*compareFunc)(ELEMENTTYPE, ELEMENTTYPE);

    /* 打印函数 */
    int (*printFunc)(ELEMENTTYPE);
    
}BinarySearchTree;


/* 二叉树搜索树初始化 */
int BSTInit(BinarySearchTree** pTree, int (*compareFunc)(ELEMENTTYPE, ELEMENTTYPE), int (*printFunc)(ELEMENTTYPE));

/* 二叉搜索树的插入 */
int BSTInsert(BinarySearchTree* pTree, ELEMENTTYPE data);

/* 二叉搜索树的是否包含指定元素 */
int BSTIsContains(BinarySearchTree* pTree, ELEMENTTYPE data);

/* 前序遍历 */
int BSTPreOrder(BinarySearchTree* pTree);

/* 中序遍历 */
int BSTInOrder(BinarySearchTree* pTree);

/* 后序遍历 */
int BSTPostOrder(BinarySearchTree* pTree);

/* 层序遍历 */
int BSTLevelOrder(BinarySearchTree* pTree);

/* 获取二叉搜素树的高度 */
int BSTGetHeight(BinarySearchTree* pTree);

#endif // !__BINARY_SEARCH_TREE_H__
