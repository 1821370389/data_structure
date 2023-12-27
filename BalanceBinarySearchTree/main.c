#include "balanceBinarySearchTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 10

/* 打印函数 */
int printFunc(void *data)
{
    printf("%d,", *(int *)data);
}
/* 比较函数 */
int compareFunc(void *data1, void *data2)
{
    return *(int*)data1 - *(int*)data2;
}


int main()
{
    /* 创建平衡二叉搜索树 */
    BalanceBinarySearchTree *tree = NULL;
    AVLInit(&tree, compareFunc, printFunc);

    /* 插入数据 */
    // int arr[BUFFER_SIZE] = {37, 29, 80, 8, 47, 97, 76, 96, 52, 51};
    int arr[BUFFER_SIZE] = {37, 50,55,52,38,47, 97, 76, 96, 45};
    for (int idx = 0; idx < BUFFER_SIZE; idx++)
    {
        AVLInsert(tree, &arr[idx]);
    }
    
    /* 获取平衡二叉搜索树的节点个数 */
    int size = 0;
    AVLGetSize(tree, &size);
    printf("size = %d\n", size);
    
    /* 前序遍历 */
    printf("前序遍历：\n");
    AVLPreOrder(tree);
    printf("\n");

    /* 中序遍历 */
    printf("中序遍历：\n");
    AVLInOrder(tree);
    printf("\n");

    /* 删除 */
    AVLDelete(tree, &arr[0]);
    /* 中序遍历 */
    printf("中序遍历：\n");
    AVLInOrder(tree);
    printf("\n");

    /* 后序遍历 */
    printf("后序遍历：\n");
    AVLPostOrder(tree);
    printf("\n");

    /* 层序遍历 */
    printf("层序遍历：\n");
    AVLLevelOrder(tree);
    printf("\n");

    /* 获取高度 */
    int height = 0;
    AVLGetHeight(tree,&height);
    printf("height = %d\n", height);


    /* 判断是否包含某数据 */
    int data = 8;
    printf("是否包含 %d :%s\n", data, (AVLIsContains(tree, (void*)&data)) ?"是":"否");
    data = 55;
    printf("是否包含 %d :%s\n", data, (AVLIsContains(tree, (void*)&data)) ?"是":"否");

    return 0;
}