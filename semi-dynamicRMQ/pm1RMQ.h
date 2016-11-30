#pragma once
#include <cmath>
#include <vector>

#include "SparseTable.h"
#include "InBlock.h"
#include "BitTableLookup.h"
#include <cstdint>

#include "misc.h"


class pm1RMQ
{
	//0 : -1, 1: +1
public:
	pm1RMQ(int size)
	{
		if (size == 1)size++; // to avoid 0div
		blocklen = ceil(std::log2(size) / 2);
		blocknum = ceildiv(size, blocklen);
		ST.resize(blocknum);
		InBlocks.resize(blocknum);
		TLs.resize(pow2(blocklen - 1));
		preprocessing();
	};

	void append(int x);
	int rmq(int i, int j);
	~pm1RMQ();
private:
	void preprocessing(); 
	int lastval;
	uint32_t current_bit;
	int num = 0;
	int blocklen; //block length
	int blocknum; // size/blocklen
	SparseTable ST;
	std::vector<InBlock> InBlocks;
	std::vector<BitTableLookup> TLs;	
};

