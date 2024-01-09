#include "FQueue.h"

// Constructor
FQueue::FQueue()
{
	m_pHead = nullptr;
	m_pTail = nullptr;
}

// Destructor
FQueue::~FQueue()
{
	FQClear();
}

// Constructor for FifoItem
FifoItem::FifoItem(FQInfo *pItem)
{
	m_pItem = pItem;
	m_pNext = nullptr;
}

// Destructor for FifoItem
FifoItem::~FifoItem(){}

// Check if the queue is empty
bool FQueue::FQEmpty() const
{
	return m_pHead == nullptr;
}

int FQueue::FQEnqueue( FQInfo *pInfo )
{
	FifoItem *pItem = new( nothrow ) FifoItem( pInfo );
	if( !pItem )
	{
		return FIFO_ALLOCATION_ERROR;
	}
	if( FQEmpty())
	{
		// If the queue is empty, set both head and tail to the new item
		m_pHead = m_pTail = pItem;
	}
	else
	{
		// Add the new item to the end of the queue and update the tail
		m_pTail->m_pNext = pItem;
		m_pTail = pItem;
	}
	return 0;
}

// Dequeue an item from the front of the queue
FQInfo *FQueue::FQDequeue()
{
	if( FQEmpty())
	{
		throw FifoException( FIFO_QUEUE_EMPTY );
	}
	FifoItem *pItem = m_pHead;
	m_pHead = m_pHead->m_pNext;
	FQInfo *pInfo = new FQInfo(*pItem->m_pItem);
	delete pItem;
	return pInfo; // Return the dequeued item
}

// Clear the entire queue
void FQueue::FQClear()
{
	while( !FQEmpty())
	{
		FQDel();
	}
}

// Delete the front item of the queue
void FQueue::FQDel()
{
	if( FQEmpty())
	{
		return;
	}
	FifoItem *pItem = m_pHead;
	m_pHead = m_pHead->m_pNext;
	delete pItem;
}
