#include "binarySearchTree.h"
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
    /* 创建二叉搜索树 */
    BinarySearchTree *tree = NULL;
    BSTInit(&tree, compareFunc, printFunc);

    /* 插入数据 */
    // int arr[BUFFER_SIZE] = {37, 29, 80, 8, 47, 97, 76, 96, 52, 51};
    int arr[BUFFER_SIZE] = {37, 50,55,52,38,47, 97, 76, 96, 45};
    for (int idx = 0; idx < BUFFER_SIZE; idx++)
    {
        BSTInsert(tree, &arr[idx]);
    }
    
    /* 获取二叉搜索树的节点个数 */
    int size = 0;
    BSTGetSize(tree, &size);
    printf("size = %d\n", size);
    
    /* 层序遍历 */
    printf("层序遍历：\n");
    BSTLevelOrder(tree);
    printf("\n");
    
    /* 前序遍历 */
    printf("前序遍历：\n");
    BSTPreOrder(tree);
    printf("\n");

    /* 中序遍历 */
    printf("中序遍历：\n");
    BSTInOrder(tree);
    printf("\n");

    /* 获取前驱节点数据 */
    int data = 38;
    int *preData = NULL;
    BSTGetPreData(tree, (void*)&data, (void**)&preData);
    printf("%d的前驱节点 %d\n", data, *preData);
    /* 删除 */
    BSTDelete(tree, &arr[4]);
    /* 中序遍历 */
    printf("中序遍历：\n");
    BSTInOrder(tree);
    printf("\n");

    /* 后序遍历 */
    printf("后序遍历：\n");
    BSTPostOrder(tree);
    printf("\n");


    /* 获取高度 */
    int height = 0;
    BSTGetHeight(tree,&height);
    printf("height = %d\n", height);


    /* 判断是否包含某数据 */
    data = 8;
    printf("是否包含 %d :%s\n", data, (BSTIsContains(tree, (void*)&data)) ?"是":"否");
    data = 55;
    printf("是否包含 %d :%s\n", data, (BSTIsContains(tree, (void*)&data)) ?"是":"否");

    return 0;
}