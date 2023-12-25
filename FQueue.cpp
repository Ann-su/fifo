#include "FQueue.h"


FQueue::FQueue()
{
	m_pHead = nullptr;
	m_pTail = nullptr;
}

FQueue::~FQueue()
{
	FQClear();
}
FifoItem::FifoItem(FQInfo *pItem) : m_pItem(pItem), m_pNext(nullptr) {}

FifoItem::~FifoItem() {}
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
		m_pHead = m_pTail = pItem;
	}
	else
	{
		m_pTail->m_pNext = pItem;
		m_pTail = pItem;
	}
	return 0;
}

FQInfo *FQueue::FQDequeue()
{
	if( FQEmpty())
	{
		throw FifoException( FIFO_QUEUE_EMPTY );
	}
	FifoItem *pItem = m_pHead;
	m_pHead = m_pHead->m_pNext;
	FQInfo *pInfo = pItem->m_pItem;
	delete pItem;
	return pInfo;
}

void FQueue::FQClear()
{
	while( !FQEmpty())
	{
		FQDel();
	}
}

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
