#pragma once

#include <vector>
#include <cmath>

#include "misc.h"

class SparseTable
{
public:
	SparseTable(int size) : width_size(floor_log2(size) + 1)
	{
		resize(size);
	}
	SparseTable() {};
	void append(int x);
	void resize(int size)
	{
		width_size = floor_log2(size) + 1;
		ST.resize(size, std::vector<int>(width_size));
		A.resize(size);
	}
	int rmq(int i, int j)// argmin [A[i:j+1] (including i and j), rightmost
	{
		const int l = floor_log2(j - i + 1);
		return A[ST[i][l]] < A[ST[j - pow2(l) + 1][l]] ? ST[i][l] : ST[j - pow2(l) + 1][l];
	}
	~SparseTable() {};
private:
	std::vector<std::vector<int>> ST; // ST[size][width_size]
	int width_size; // floor(lg_2(size))
	int num = 0;
	std::vector<int> A;
};

