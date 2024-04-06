#include "Stack.h"

Stack_Instance *Stack_Init()
{
    Stack_Instance *ins = (Stack_Instance *)MALLOC(sizeof(Stack_Instance));
    ins->list = LinkList_Init();
    return ins;
}

void Stack_SetFreeDataCallback(Stack_Instance *ins, LinkList_FreeDataCallbackType callback)
{
    LinkList_SetFreeDataCallback(ins->list, callback);
}

void Stack_PushBack(Stack_Instance *ins, void *data)
{
    LinkList_AddNode(ins->list, data);
}

void *Stack_Top(Stack_Instance *ins)
{
    return LinkList_GetNodeDataByIndex(ins->list, LinkList_Count(ins->list) - 1);
}

void Stack_Pop(Stack_Instance *ins)
{
    LinkList_RemoveNodeByIndex(ins->list, LinkList_Count(ins->list) - 1);
}

uint32_t Stack_Count(Stack_Instance *ins)
{
    return LinkList_Count(ins->list);
}

void Stack_Clear(Stack_Instance *ins)
{
    LinkList_Clear(ins->list);
}

void Stack_Release(Stack_Instance *ins)
{
    LinkList_Release(ins->list);
    FREE(ins);
}