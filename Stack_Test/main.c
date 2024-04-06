#include "Stack.h"

void FreeIntData(void *data)
{
    FREE((int *)data);
}

int main(void)
{
    DEBUG_RESET_MALLOC_COUNT();

    Stack_Instance *ins = Stack_Init();
    Stack_SetFreeDataCallback(ins, FreeIntData);

    assert(Stack_Count(ins) == 0);

    int *data1 = (int *)MALLOC(sizeof(int));
    *data1 = 1;
    Stack_PushBack(ins, data1);

    assert(Stack_Count(ins) == 1);

    int *data2 = (int *)MALLOC(sizeof(int));
    *data2 = 23;
    Stack_PushBack(ins, data2);

    assert(*(int *)Stack_Top(ins) == *data2);

    Stack_Pop(ins);

    assert(*(int *)Stack_Top(ins) == *data1);

    Stack_Clear(ins);

    assert(Stack_Count(ins) == 0);

    int *data3 = (int *)MALLOC(sizeof(int));
    *data3 = 3;

    Stack_PushBack(ins, data3);

    Stack_Release(ins);

    DEBUG_ASSERT_MALLOC_COUNT_ZERO();
    TEST_PASSED();
    return 0;
}