#include "Queue.h"

Queue_Instance *Queue_Init()
{
    Queue_Instance *ins = (Queue_Instance *)malloc(sizeof(Queue_Instance));
    DEBUG_INCREASE_MALLOC_COUNT();
    ins->list = LinkList_Init();
    return ins;
}

void Queue_SetFreeDataCallback(Queue_Instance *ins, void (*freeData)(void *data))
{
    LinkList_SetFreeDataCallback(ins->list, freeData);
}

void *Queue_Front(Queue_Instance *ins)
{
    return LinkList_GetNodeDataByIndex(ins->list, 0);
}

void Queue_Pop(Queue_Instance *ins)
{
    LinkList_RemoveNodeByIndex(ins->list, 0);
}

void Queue_Push(Queue_Instance *ins, void *data)
{
    LinkList_AddNode(ins->list, data);
}

uint32_t Queue_Size(Queue_Instance *ins)
{
    return LinkList_Count(ins->list);
}

void Queue_Clear(Queue_Instance *ins)
{
    LinkList_Clear(ins->list);
}

void Queue_Release(Queue_Instance *ins)
{
    LinkList_Release(ins->list);
    free(ins);
    DEBUG_DECREASE_MALLOC_COUNT();
}