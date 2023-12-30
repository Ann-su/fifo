// TemplateFQueue.h

#pragma once

#include <iostream>
#include <stdexcept>

using namespace std;
#define FIFO_ALLOCATION_ERROR 0x01
#define FIFO_QUEUE_EMPTY 0x04
#define OTHER_ERROR 0x10

//==Templatki===========================================================================================================

template<class K>
struct FQInfo
{
	K nKey;
	int *pData;
	FQInfo( K key = K());
	~FQInfo();

	friend ostream &operator<<( ostream &out, const FQInfo &info )
	{
		out << "Key: " << info.nKey << ", Data: [" << info.pData[0] << ", " << info.pData[1] << "]";
		return out;
	}
};

template<class K>
class FQueue;

template<class K>
class FifoItem
{
	friend class FQueue<K>;

public:
	FifoItem( FQInfo<K> *pItem = nullptr );
	~FifoItem();
private:
	FQInfo<K> *m_pItem;
	FifoItem<K> *m_pNext;
};

template<class K>
class FifoException : public exception
{
public:
	FifoException( int errCode = OTHER_ERROR ) : errorCode( errCode )
	{};
	const char *getReason() const;
private:
	int errorCode;
};

template<class K>
class FQueue
{
public:
	FQueue();
	virtual ~FQueue();
	bool FQEmpty() const;
	int FQEnqueue( FQInfo<K> *pInfo );
	FQInfo<K> *FQDequeue();
	void FQClear();
private:
	FifoItem<K> *m_pHead;
	FifoItem<K> *m_pTail;
	void FQDel();
};

//==IMPLEMENTATIONS=====================================================================================================

template<class K>
FQueue<K>::FQueue()
{
	m_pHead = nullptr;
	m_pTail = nullptr;
}

template<class K>
FQueue<K>::~FQueue()
{
	FQClear();
}

template<class K>
bool FQueue<K>::FQEmpty() const
{
	return m_pHead == nullptr;
}

template<class K>
int FQueue<K>::FQEnqueue( FQInfo<K> *pInfo )
{
	FifoItem<K> *pItem = new( nothrow ) FifoItem<K>( pInfo );
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

template<class K>
const char *FifoException<K>::getReason() const
{
	switch( errorCode )
	{
		case FIFO_ALLOCATION_ERROR: return "FIFO allocation error";
		case FIFO_QUEUE_EMPTY: return "FIFO is empty";
		case OTHER_ERROR:
		default: return "Other error";
	}
}

template<class K>
FQInfo<K> *FQueue<K>::FQDequeue()
{
	if( FQEmpty())
	{
		throw FifoException<K>( FIFO_QUEUE_EMPTY );
	}
	FifoItem<K> *pItem = m_pHead;
	m_pHead = m_pHead->m_pNext;
	FQInfo<K> *pInfo = pItem->m_pItem;
	delete pItem;
	return pInfo;
}

template<class K>
void FQueue<K>::FQClear()
{
	while( !FQEmpty())
	{
		FQDel();
	}
}

template<class K>
void FQueue<K>::FQDel()
{
	if( FQEmpty())
	{
		return;
	}
	FifoItem<K> *pItem = m_pHead;
	m_pHead = m_pHead->m_pNext;
	delete pItem;
}

template<class K>
FQInfo<K>::FQInfo( K key ) : nKey( key ), pData( new int[2] )
{
	pData[0] = 21;
	pData[1] = 37;
}

template<class K>
FQInfo<K>::~FQInfo()
{
	delete[] pData;
}

template<class K>
ostream &operator<<( ostream &out, const FQInfo<K> &info )
{
	out << "Key: " << info.nKey << ", Data: [" << info.pData[0] << ", " << info.pData[1] << "]";
	return out;
}

template<class K>
FifoItem<K>::FifoItem( FQInfo<K> *pItem )
{
	m_pItem = pItem;
	m_pNext = nullptr;
}

template<class K>
FifoItem<K>::~FifoItem(){}
