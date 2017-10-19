/**
 * Copyright (C) 2017 - Shukant Pal
 */

#define NAMESPACE_IPC_MANAGEMENT
#define NAMESPACE_MESSAGE_PASSING_INTERNAL
#define NAMESPACE_KVECTOR
#define NAMESPACE_MEMORY_MANAGER

#include <Exec/Process.h>
#include <Exec/Thread.h>
#include <HAL/Processor.h>
#include <InterProcess/MessagePassing.h>
#include <Memory/Paging.h>
#include <Memory/Slab.h>
#include <Memory/Page.h>
#include <Memory/Heap.h>
#include <Util/KVector.h>
#include <TYPE.h>

DECLARE_TYPE(MessageQueueTp, sizeof(MESSAGE_QUEUE));
DECLARE_TYPE(MessageTp, sizeof(MESSAGE));
DECLARE_TYPE(AVLNodeTp, sizeof(AVL_NODE));
DECLARE_TYPE(AVLTreeTp, sizeof(AVL_TREE));
DECLARE_TYPE(LinkedListTp, sizeof(LINKED_LIST));
KVECTOR_CONTAINER msgQueueVector = NEW_KVECTOR_CONTAINER;

MESSAGE_QUEUE mq;

ID CreateMsgQueue(SIZE queueMaxBytes, SIZE queueMaxMessages)
{
	MESSAGE_QUEUE *msgQueue = (MESSAGE_QUEUE *) KNewObject(&MessageQueueTp);
	memsetf(msgQueue, 0, sizeof(MESSAGE_QUEUE));
	msgQueue->UsageLimit = (queueMaxMessages > 128) ? 128 : queueMaxMessages;
	msgQueue->SizeLimit = (queueMaxBytes > KB(16)) ? KB(16) : queueMaxBytes;
	msgQueue->PriorityMsgTree.FreeNode = (VOID (*) (AVL_NODE*)) &KDeleteObject;
	return (SetKVector((KVECTOR *) msgQueue, &msgQueueVector));
}

LONG ReadMsg(ID queueID, VOID *bufferPointer, USHORT bufferSize, USHORT msgTag, USHORT minPriority, ULONG msgFlags, USHORT timeOut)
{
	CONTEXT *pContext = GetContext();

	if(!CheckUsability((VIRTUAL_T) bufferPointer, pContext))
		return (-1);

	MESSAGE_QUEUE *msgQueue = ReadKVector(MESSAGE_QUEUE, queueID, &msgQueueVector);
	BOOL queueUsable = CheckUsability((VIRTUAL_T) msgQueue, pContext);

	if(queueUsable) {
		
	}

	return (-1);
}

LONG SendMsg(ID queueID, VOID *bufferPointer, USHORT bufferSize, USHORT msgTag, USHORT msgPriority, ULONG msgFlags, USHORT timeOut)
{
	PROCESSOR *pInfo = GetProcessorById(PROCESSOR_ID);
	KTHREAD *pThread = pInfo->PoExT;
	CONTEXT *pContext = GetContext();

	if(!CheckUsability((ADDRESS) bufferPointer, pContext))
		return (-1);
	else {
		MESSAGE_QUEUE *msgQueue = ReadKVector(MESSAGE_QUEUE, queueID, &msgQueueVector);
		BOOL queueUsable = CheckUsability((ADDRESS) msgQueue, pContext);

		MESSAGE *msgPtr = KNewObject(&MessageTp);
	}

	return (-1);
}
