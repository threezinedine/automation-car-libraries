#include "Queue.h"

void FreeIntData(void *data)
{
    FREE((int *)data);
}

void TestInitQueue(Queue_Instance *queue)
{
    int *data = (int *)MALLOC(sizeof(int));
    *data = 12;
    Queue_Push(queue, (void *)data);

    int *data2 = (int *)MALLOC(sizeof(int));
    *data2 = 13;
    Queue_Push(queue, (void *)data2);

    int *data3 = (int *)MALLOC(sizeof(int));
    *data3 = 144;
    Queue_Push(queue, (void *)data3);
}

int main(void)
{
    Queue_Instance *queue = Queue_Init();

    Queue_SetFreeDataCallback(queue, FreeIntData);
    TestInitQueue(queue);

    assert(Queue_Size(queue) == 3);

    int *testData = (int *)Queue_Front(queue);
    assert(*testData == 12);
    Queue_Pop(queue);

    assert(Queue_Size(queue) == 2);

    testData = (int *)Queue_Front(queue);
    assert(*testData == 13);
    Queue_Pop(queue);
    testData = (int *)Queue_Front(queue);
    assert(*testData == 144);
    Queue_Pop(queue);
    Queue_Pop(queue);

    assert(Queue_Size(queue) == 0);

    TestInitQueue(queue);
    assert(Queue_Size(queue) == 3);
    Queue_Clear(queue);
    assert(Queue_Size(queue) == 0);

    Queue_Release(queue);

    DEBUG_ASSERT_MALLOC_COUNT_ZERO();
    TEST_PASSED();
    return 0;
}