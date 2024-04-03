#ifndef _LINKLIST_INCLUDE_H
#define _LINKLIST_INCLUDE_H

#include "Common.h"
#include <string.h>

typedef struct LinkList_Node
{
    void *data;
    struct LinkList_Node *next;
} LinkList_Node;

typedef void (*LinkList_FreeDataCallbackType)(void *data);
typedef void (*LinkList_ForEachCallbackType)(void *data, void *context);

typedef struct LinkList_Instance
{
    LinkList_Node *head;
    LinkList_Node *tail;
    uint32_t count;
    LinkList_FreeDataCallbackType freeDataCallback;
} LinkList_Instance;

LinkList_Instance *LinkList_Init();
void LinkList_SetFreeDataCallback(LinkList_Instance *instance,
                                  LinkList_FreeDataCallbackType callback);

void LinkList_AddNode(LinkList_Instance *instance, void *data);
void LinkList_ForEach(LinkList_Instance *instance,
                      LinkList_ForEachCallbackType foreach,
                      void *context);

void LinkList_Clear(LinkList_Instance *instance);

void LinkList_Release(LinkList_Instance *instance);

#endif // _LINKLIST_INCLUDE_H