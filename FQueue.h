#pragma once

#include <iostream>
#include <stdexcept>
using namespace std;

#define FIFO_ALLOCATION_ERROR 0x01
#define FIFO_QUEUE_EMPTY 0x04
#define OTHER_ERROR 0x10

// Structure for FQInfo
struct FQInfo
{
	int nKey;
	int *pData;

	FQInfo( int key ) : nKey( key ), pData( new int[2] ){}

	~FQInfo()
	{
		delete[] pData;
	}

	friend ostream &operator<<( ostream &os, const FQInfo &info )
	{
		os << "Key: " << info.nKey << ", Data: [" << info.pData[0] << ", " << info.pData[1] << "]";
		return os;
	}
};

// Item class for the FIFO
class FifoItem
{
public:
	FifoItem( FQInfo *pItem = nullptr );
	~FifoItem();

private:
	FQInfo *m_pItem;
	FifoItem *m_pNext;

	friend class FQueue;
};

// FIFO class
class FQueue
{
public:
	FQueue();
	~FQueue();
	bool FQEmpty() const;
	int FQEnqueue( FQInfo *pInfo );
	FQInfo *FQDequeue();
	void FQClear();
private:
	FifoItem *m_pHead;
	FifoItem *m_pTail;
	void FQDel();
};

// Exception class
class FifoException :public exception
{
public:
	FifoException( int errCode = OTHER_ERROR ) : errorCode( errCode ){};
	const char *getReason() const;

private:
	int errorCode;
};

//==INLINE FUNCTIONS====================================================================================================
inline const char* FifoException::getReason() const
{
	switch(errorCode)
	{
		case FIFO_ALLOCATION_ERROR: return "FIFO allocation error";
		case FIFO_QUEUE_EMPTY: return "FIFO is empty";
		case OTHER_ERROR:
		default: return "Other error";
	}
}
