#pragma once
#include "BitTableLookup.h"

class InBlock
{
private:
	BitTableLookup* tl = nullptr;
	int diff;
public:
	InBlock(int A0) : diff(A0) {}; // A0 : A'[0]
	InBlock() {};	
	~InBlock() {};
	void set_diff(int A0)
	{
		diff = A0;
	}
	void set_ptr(BitTableLookup* t)
	{
		tl = t;
	}
	
	int rmq(int i, int j)
	{
		return tl->rmq(i, j);
	}
};

