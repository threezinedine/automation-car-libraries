#include "LinkList.h"

LinkList_Instance *LinkList_Init()
{
    LinkList_Instance *instance = (LinkList_Instance *)malloc(sizeof(LinkList_Instance));
    DEBUG_INCREASE_MALLOC_COUNT();

    instance->head = NULL;
    instance->tail = NULL;
    instance->freeDataCallback = NULL;
    instance->count = 0;

    return instance;
}

void LinkList_SetFreeDataCallback(LinkList_Instance *instance,
                                  LinkList_FreeDataCallbackType callback)
{
    instance->freeDataCallback = callback;
    return;
}

void LinkList_AddNode(LinkList_Instance *instance, void *data)
{
    LinkList_Node *newNode = (LinkList_Node *)malloc(sizeof(LinkList_Node));
    DEBUG_INCREASE_MALLOC_COUNT();

    newNode->data = data;
    newNode->next = NULL;

    if (instance->count == 0)
    {
        instance->head = newNode;
    }
    else
    {
        instance->tail->next = newNode;
    }

    instance->count++;
    instance->tail = newNode;
    return;
}

void LinkList_ForEach(LinkList_Instance *instance,
                      LinkList_ForEachCallbackType foreach,
                      void *context)
{
    LinkList_Node *current = instance->head;

    while (current != NULL)
    {
        foreach (current->data, context)
            ;
        current = current->next;
    }

    return;
}

void LinkList_Clear(LinkList_Instance *instance)
{
    LinkList_Node *current = instance->head;

    while (current != NULL)
    {
        LinkList_Node *next = current->next;

        if (instance->freeDataCallback != NULL)
        {
            instance->freeDataCallback(current->data);
        }

        free(current);
        DEBUG_DECREASE_MALLOC_COUNT();
        current = next;
    }

    instance->head = NULL;
    instance->tail = NULL;
    instance->count = 0;

    return;
}

void LinkList_Release(LinkList_Instance *instance)
{
    LinkList_Node *current = instance->head;

    while (current != NULL)
    {
        LinkList_Node *next = current->next;

        if (instance->freeDataCallback != NULL)
        {
            instance->freeDataCallback(current->data);
        }

        free(current);
        DEBUG_DECREASE_MALLOC_COUNT();
        current = next;
    }

    free(instance);
    DEBUG_DECREASE_MALLOC_COUNT();

    return;
}