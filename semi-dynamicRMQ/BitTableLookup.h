#pragma once
#include <vector>
#include <cstdint>

class BitTableLookup
{
private:
	std::vector<std::vector<int>> TL;
public:
	BitTableLookup(uint32_t bit, int bitwidth);
	BitTableLookup() {};
	void init(uint32_t bit, int bitwidth);
	int rmq(int i, int j) { return TL[i][j]; }; // argmin, rightmost

	~BitTableLookup() {};
};

