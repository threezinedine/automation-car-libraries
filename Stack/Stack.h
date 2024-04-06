#ifndef _STACK_INCLUDE_H
#define _STACK_INCLUDE_H

#include <Common.h>
#include <LinkList.h>

typedef struct Stack_Instance
{
    LinkList_Instance *list;
} Stack_Instance;

Stack_Instance *Stack_Init();
void Stack_SetFreeDataCallback(Stack_Instance *ins, LinkList_FreeDataCallbackType callback);

uint32_t Stack_Count(Stack_Instance *ins);

void Stack_PushBack(Stack_Instance *ins, void *data);

void *Stack_Top(Stack_Instance *ins);
void Stack_Pop(Stack_Instance *ins);

void Stack_Clear(Stack_Instance *ins);

void Stack_Release(Stack_Instance *ins);

#endif