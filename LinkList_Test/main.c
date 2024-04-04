#include <assert.h>
#include <LinkList.h>

typedef struct Pair
{
    const char *key;
    const char *value;
} Pair;

void FreeIntData(void *data)
{
    FREE((int *)data);
}

void ForEachSum(void *data, void *context)
{
    *(int *)(context) += *(int *)data;
}

void FreePairData(void *data)
{
    FREE((Pair *)data);
}

void ForEachPair(void *data, void *context)
{
    Pair *pair = (Pair *)data;
    *((int *)context) += 1;
}

int main(void)
{
    DEBUG_RESET_MALLOC_COUNT();

    LinkList_Instance *ins = LinkList_Init();
    int sum = 0;

    {
        LinkList_SetFreeDataCallback(ins, FreeIntData);
        int *data = (int *)MALLOC(sizeof(int));
        *data = 4;

        LinkList_AddNode(ins, (void *)data);

        int *data2 = (int *)MALLOC(sizeof(int));
        *data2 = 5;
        LinkList_AddNode(ins, (void *)data2);

        int *data3 = (int *)MALLOC(sizeof(int));
        *data3 = 0;
        LinkList_AddNode(ins, (void *)data3);

        assert(*(int *)LinkList_GetNodeDataByIndex(ins, 0) == 4);
        assert(*(int *)LinkList_GetNodeDataByIndex(ins, 1) == 5);
        assert(*(int *)LinkList_GetNodeDataByIndex(ins, 2) == 0);

        assert(LinkList_Count(ins) == 3);

        LinkList_ForEach(ins, ForEachSum, (void *)&sum);
        assert(sum == 9);

        LinkList_RemoveNodeByIndex(ins, 1);
        assert(*(int *)LinkList_GetNodeDataByIndex(ins, 0) == 4);
        assert(*(int *)LinkList_GetNodeDataByIndex(ins, 1) == 0);
        assert(LinkList_Count(ins) == 2);
        assert(LinkList_GetNodeDataByIndex(ins, 2) == NULL);
        LinkList_RemoveNodeByIndex(ins, 4);
        assert(LinkList_Count(ins) == 2);

        LinkList_Clear(ins);

        assert(LinkList_Count(ins) == 0);
        assert(LinkList_GetNodeDataByIndex(ins, 0) == NULL);
        LinkList_RemoveNodeByIndex(ins, 3);
        assert(LinkList_Count(ins) == 0);

        LinkList_RemoveNodeByIndex(ins, 0);
        assert(LinkList_Count(ins) == 0);
    }

    {
        LinkList_SetFreeDataCallback(ins, FreePairData);
        Pair *pair = (Pair *)MALLOC(sizeof(Pair));
        pair->key = "0883922712";
        pair->value = "John Doe";
        LinkList_AddNode(ins, (void *)pair);

        Pair *pair2 = (Pair *)MALLOC(sizeof(Pair));
        pair2->key = "0883922713";
        pair2->value = "Jane Doe";
        LinkList_AddNode(ins, (void *)pair2);

        void *data = LinkList_GetNodeDataByIndex(ins, 0);
        assert(strcmp(((Pair *)data)->key, pair->key) == 0);
        assert(strcmp(((Pair *)data)->value, pair->value) == 0);

        data = LinkList_GetNodeDataByIndex(ins, 1);
        assert(strcmp(((Pair *)data)->key, pair2->key) == 0);
        assert(strcmp(((Pair *)data)->value, pair2->value) == 0);

        int callCount = 0;
        LinkList_ForEach(ins, ForEachPair, (void *)&callCount);

        LinkList_RemoveNodeByIndex(ins, 0);
        assert(LinkList_Count(ins) == 1);

        assert(callCount == 2);
    }

    LinkList_Release(ins);

    DEBUG_ASSERT_MALLOC_COUNT_ZERO();
    TEST_PASSED();
    return 0;
}