#include "LinkList.h"

LinkList_Instance *LinkList_Init()
{
    LinkList_Instance *instance = (LinkList_Instance *)MALLOC(sizeof(LinkList_Instance));

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
    LinkList_Node *newNode = (LinkList_Node *)MALLOC(sizeof(LinkList_Node));

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

        FREE(current);
        current = next;
    }

    instance->head = NULL;
    instance->tail = NULL;
    instance->count = 0;

    return;
}

void *LinkList_GetNodeDataByIndex(LinkList_Instance *ins, uint32_t index)
{
    uint32_t temp = 0;
    LinkList_Node *current = ins->head;

    while (current != NULL)
    {
        if (temp == index)
        {
            return current->data;
        }

        current = current->next;

        temp++;
    }
    return NULL;
}

void LinkList_RemoveNodeByIndex(LinkList_Instance *ins, uint32_t index)
{
    uint32_t temp = 0;
    LinkList_Node *current = ins->head;
    LinkList_Node *previous = ins->head;

    if (index == 0)
    {
        if (ins->head == NULL)
        {
            return;
        }
        LinkList_Node *temp = ins->head;
        ins->head = ins->head->next;
        ins->count--;
        ins->freeDataCallback(temp->data);
        FREE(temp);
        return;
    }

    while (current != NULL && temp != index)
    {
        previous = current;
        current = current->next;
        temp++;
    }

    if (current != NULL && previous != NULL && temp == index)
    {
        previous->next = current->next;
        ins->count--;
        ins->freeDataCallback(current->data);
        FREE(current);
    }

    return;
}

uint32_t LinkList_Count(LinkList_Instance *instance)
{
    return instance->count;
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

        FREE(current);
        current = next;
    }

    FREE(instance);

    return;
}