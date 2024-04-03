#include <assert.h>
#include <LinkList.h>

typedef struct Pair
{
    const char *key;
    const char *value;
} Pair;

void FreeIntData(void *data)
{
    DEBUG_DECREASE_MALLOC_COUNT();
    free((int *)data);
}

void ForEachSum(void *data, void *context)
{
    *(int *)(context) += *(int *)data;
}

void FreePairData(void *data)
{
    DEBUG_DECREASE_MALLOC_COUNT();
    free((Pair *)data);
}

void ForEachPair(void *data, void *context)
{
    Pair *pair = (Pair *)data;
    DEBUG_PRINT("Key: %s, Value: %s\n", pair->key, pair->value);
    *((int *)context) += 1;
}

int main(void)
{
    DEBUG_RESET_MALLOC_COUNT();

    LinkList_Instance *ins = LinkList_Init();
    int sum = 0;

    {
        LinkList_SetFreeDataCallback(ins, FreeIntData);
        int *data = (int *)malloc(sizeof(int));
        DEBUG_INCREASE_MALLOC_COUNT();
        *data = 4;

        LinkList_AddNode(ins, (void *)data);

        int *data2 = (int *)malloc(sizeof(int));
        DEBUG_INCREASE_MALLOC_COUNT();
        *data2 = 5;
        LinkList_AddNode(ins, (void *)data2);

        LinkList_ForEach(ins, ForEachSum, (void *)&sum);
        assert(sum == 9);

        LinkList_Clear(ins);
    }

    {
        LinkList_SetFreeDataCallback(ins, FreePairData);
        Pair *pair = (Pair *)malloc(sizeof(Pair));
        DEBUG_INCREASE_MALLOC_COUNT();
        pair->key = "0883922712";
        pair->value = "John Doe";

        LinkList_AddNode(ins, (void *)pair);

        Pair *pair2 = (Pair *)malloc(sizeof(Pair));
        DEBUG_INCREASE_MALLOC_COUNT();
        pair2->key = "0883922713";
        pair2->value = "Jane Doe";

        LinkList_AddNode(ins, (void *)pair2);

        int callCount = 0;
        LinkList_ForEach(ins, ForEachPair, (void *)&callCount);

        assert(callCount == 2);
    }

    LinkList_Release(ins);

    DEBUG_ASSERT_MALLOC_COUNT_ZERO();
    return 0;
}