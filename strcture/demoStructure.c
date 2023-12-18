#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 结构体 */
/* 1.什么叫结构体  将不同类型的属性封装成一个类型*/
#define BUFFER_SIZE 20
#define DEFAULT_SIZE 5
/* 2.怎么定义结构体 */
typedef struct strInfo
{
    int age;
    int height;
    int weight;
    char sex;
    char name[BUFFER_SIZE];
    char *address;
} strInfo;
/* 取别名 typedef */

/* 结构体会默认进行字节对齐：读取速度快，但是浪费空间 */
/* 结构体的位域到网络编程的时候再深究，todo... */
/* 什么叫变长结构体  其实真正意义上并不是结构体的大小可变，而是使用结构体中的变量代表一个地址，从而访问超出结构体大小范围的数据 */

/* 结构体函数 */
/* 值传递 */
#if 0
void printfStruct(strInfo stu)
{
    /* 栈空间很小，不允许超过8MB */
    stu.age = 28;
    printf("age = %d,height:%d,weight:%d,sex:%c,name:%s\n",
    stu.age, stu.height, stu.weight, stu.sex, stu.name);
    
    return;
}
#else
void printfStruct( const strInfo *stu)
{
    /* 所以用指针传地址 */
    /* 结构体必须用指针 */
    int ret = 0;
    int len = sizeof(stu);
    printf("len = %d\n", len);
    // stu->age = 28;
    printf("age = %d,height:%d,weight:%d,sex:%c,name:%s\n", 
    stu->age, stu->height, stu->weight, stu->sex, stu->name);
    return;

}
#endif

#if 1
/* 结构体数组作函数参数 */
void printfStructArray(strInfo *stu, int stuSize)
{
    for(int idx = 0; idx < stuSize; idx++)
    {
        printf("age = %d,height:%d,weight:%d,sex:%c,name:%s\n",stu[idx].age, 
        stu[idx].height, stu[idx].weight, stu[idx].sex, stu[idx].name);
    }
    return;
}
#endif

#if 1
int main()
{
    /* 3.怎么使用结构体 */
    strInfo stu;
    memset(&stu, 0, sizeof(stu));// 初始化结构体
    #if 1
    stu.age = 18;
    stu.height = 170;
    stu.weight = 60;
    stu.sex = 'M';
    strncpy(stu.name, "zhangsan",sizeof(stu.name)-1);
    // stu.name = "zhangsan";

    /* 结构体内有指针必须分配空间*/
    stu.address = (char *)malloc(BUFFER_SIZE*sizeof(char));
    strcpy(stu.address, "china");
    printf("stu.addresss = %s\n",stu.address);

    // printf("age = %d,height:%d,weight:%d,sex:%c,name:%s\n", stu.age, stu.height, stu.weight, stu.sex, stu.name);
    printfStruct(&stu);
    printf("age = %d\n", stu.age);
    #endif

#if 0 
    /* 结构体指针 */
    strInfo *info = &stu;
    info->age = 38;
    printf("inf->age:%d\n",info->age);
    printf("stu.age:%d\n",stu.age);

    /* 4.结构体的大小 */
    int len = sizeof(stu);
    printf("len = %d\n", len);
#endif
    /* 5.结构体数组 */
    #if 0
    /* 数组：一块连续的内存地址，存放的是同一种数据类型*/
    strInfo buffer[DEFAULT_SIZE];
    buffer[0].age = 18;
    buffer[0].height = 170;
    buffer[0].weight = 60;
    buffer[0].sex = 'M';
    strncpy(buffer[0].name, "zhangsan",sizeof(buffer[0].name)-1);
    buffer[1].age = 19;
    buffer[1].height = 171;
    buffer[1].weight = 61;
    buffer[1].sex = 'F';
    strncpy(buffer[1].name, "lisi",sizeof(buffer[1].name)-1);
    printf("age = %d,height:%d,weight:%d,sex:%c,name:%s\n", buffer[0].age, buffer[0].height, buffer[0].weight, buffer[0].sex, buffer[0].name);
    printf("age = %d,height:%d,weight:%d,sex:%c,name:%s\n", buffer[1].age, buffer[1].height, buffer[1].weight, buffer[1].sex, buffer[1].name);
    #endif
    
    return 0;
    
}
#endif