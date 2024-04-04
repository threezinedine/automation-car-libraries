#ifndef _QUEUE_INCLUDE_H
#define _QUEUE_INCLUDE_H

#include "Common.h"
#include "LinkList.h"

typedef struct Queue_Instance
{
    LinkList_Instance *list;
} Queue_Instance;

Queue_Instance *Queue_Init();

void Queue_SetFreeDataCallback(Queue_Instance *queue, LinkList_FreeDataCallbackType callback);
void Queue_Push(Queue_Instance *queue, void *data);

void *Queue_Front(Queue_Instance *queue);
void Queue_Pop(Queue_Instance *queue);

uint32_t Queue_Size(Queue_Instance *queue);

void Queue_Clear(Queue_Instance *queue);
void Queue_Release(Queue_Instance *queue);

#endif // _QUEUE_INCLUDE_H