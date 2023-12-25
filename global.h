#pragma once

#include <iostream>
#include <stdexcept>

using namespace std;

class FQInfo
{
public:
	FQInfo( int key );
	virtual ~FQInfo();
	friend ostream &operator<<( ostream &os, const FQInfo &info );
private:
	int nKey;
	int *pData;
};

inline FQInfo::FQInfo( int key ) : nKey( key ), pData( new int[2] ){}

inline FQInfo::~FQInfo()
{
	delete[] pData;
}

inline ostream &operator<<( ostream &out, const FQInfo &info )
{
	out << "Key: " << info.nKey << ", Data: [" << info.pData[0] << ", " << info.pData[1] << "]";
	return out;
}

