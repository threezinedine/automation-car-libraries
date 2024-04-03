#include "Common.h"

#ifdef _DEBUG

static int mallocCount = 0;

void ResetMallocCount()
{
    mallocCount = 0;
}

void IncreaseMallocCount()
{
    mallocCount++;
}

void DecreaseMallocCount()
{
    mallocCount--;
}

void AssertMallocCountIsZero()
{
    if (mallocCount != 0)
    {
        printf("Malloc count is not zero: %d\n", mallocCount);
    }
    assert(mallocCount == 0);
}

#endif