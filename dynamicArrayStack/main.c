#include <stdio.h>
#include <stdlib.h>
#include "dynamicArrayStack.h"

#define BUFFER_SIZE 5
int main()
{
    dynamicArrayStack stack;
    /* 怎么解决套壳问题 */
    dynamicArrayStackInit(&stack);
    
    int buffer[BUFFER_SIZE]={ 1, 2, 3, 4, 5 };
    for(int idx = 0; idx < BUFFER_SIZE; idx++)
    {
        dynamicArrayStackPush(&stack, &buffer[idx]);
    }

    int size = 0;
    dynamicArrayStackSize(&stack, &size);
    printf("size = %d\n", size);

    int *val =NULL;
    while(!dynamicArrayStackEmpty(&stack))
    {
        dynamicArrayStackSize(&stack, &size);
        dynamicArrayStackTop(&stack, (void **)&val);
        printf("%dval = %d\n",size, *val);
        dynamicArrayStackPop(&stack);
    }

    dynamicArrayStackDestroy(&stack);
    return 0;
}