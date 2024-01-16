#pragma once

#include <iostream>
#include <stdexcept>

using namespace std;
#define FIFO_ALLOCATION_ERROR 0x01
#define FIFO_QUEUE_EMPTY 0x04
#define OTHER_ERROR 0x10

template<class T>
class FQueue;

template<class T>
class FifoItem
{
	friend class FQueue<T>;

public:
	FifoItem( T itemData );
	virtual ~FifoItem();
private:
	T mData;
	FifoItem<T> *m_pNext;
};

template<class T>
class FifoException : public exception
{
public:
	FifoException( int errCode = OTHER_ERROR ) : errorCode( errCode )
	{}

	const char *getReason() const;
private:
	int errorCode;
};

template<class T>
class FQueue
{
public:
	FQueue();
	virtual ~FQueue();
	bool FQEmpty() const;
	int FQEnqueue( T info );
	T FQDequeue();
	void FQClear();
	void Print() const;
private:
	FifoItem<T> *m_pHead;
	void FQDel();
};

//==IMPLEMENTATIONS=====================================================================================================

template<class T>
FifoItem<T>::FifoItem( T itemData )
{
	mData = itemData;
	m_pNext = nullptr;
}

template<class T>
FifoItem<T>::~FifoItem()
{}

template<class T>
FQueue<T>::FQueue()
{
	m_pHead = nullptr;
}

template<class T>
FQueue<T>::~FQueue()
{
	FQClear();
}

template<class T>
bool FQueue<T>::FQEmpty() const
{
	return m_pHead == nullptr;
}

template<class T>
void FQueue<T>::Print() const
{
	FifoItem<T> *pItem = m_pHead;
	cout << "Queue contents: " << endl;
	while( pItem )
	{
		cout << "Data: " << pItem->mData << endl;
		pItem = pItem->m_pNext;
	}
}

template<class T>
int FQueue<T>::FQEnqueue( T info )
{
	FifoItem<T> *pItem = new( nothrow ) FifoItem<T>( info );
	if( !pItem )
	{
		return FIFO_ALLOCATION_ERROR;
	}

	// Add the new item to the end of the queue
	if( FQEmpty())
	{
		m_pHead = pItem;
	}
	else
	{
		// Traverse to the end of the queue
		FifoItem<T> *pLast = m_pHead;
		while( pLast->m_pNext != nullptr )
		{
			pLast = pLast->m_pNext;
		}

		// Add the new item to the end
		pLast->m_pNext = pItem;
	}
	return 0;
}

template<class T>
T FQueue<T>::FQDequeue()
{
	if( FQEmpty())
	{
		throw FifoException<T>( FIFO_QUEUE_EMPTY );
	}
	FifoItem<T> *pItem = m_pHead;
	m_pHead = m_pHead->m_pNext;
	T data = pItem->mData;
	delete pItem;
	return data;
}

template<class T>
void FQueue<T>::FQClear()
{
	while( !FQEmpty())
	{
		FQDel();
	}
}

template<class T>
void FQueue<T>::FQDel()
{
	if( FQEmpty())
	{
		return;
	}
	FifoItem<T> *pItem = m_pHead;
	m_pHead = m_pHead->m_pNext;
	delete pItem;
}

template<class T>
const char *FifoException<T>::getReason() const
{
	switch( errorCode )
	{
		case FIFO_ALLOCATION_ERROR: return "FIFO allocation error";
		case FIFO_QUEUE_EMPTY: return "FIFO is empty";
		case OTHER_ERROR:
		default: return "Other error";
	}
}
