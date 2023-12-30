#pragma once

#include <iostream>
#include <stdexcept>

using namespace std;

struct FQInfo
{
	int nKey;
	int* pData;

	FQInfo(int key = 0);
	~FQInfo();

	friend ostream& operator<<( ostream& out, const FQInfo& info);
};


inline FQInfo::FQInfo( int key ) : nKey( key ), pData( new int[2] )
{
	pData[0] = 21;
	pData[1] = 37;
}

inline FQInfo::~FQInfo()
{
	delete[] pData;
}

inline ostream &operator<<( ostream &out, const FQInfo &info )
{
	out << "Key: " << info.nKey << ", Data: [" << info.pData[0] << ", " << info.pData[1] << "]";
	return out;
}

