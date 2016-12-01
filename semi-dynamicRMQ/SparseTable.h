#pragma once

#include <vector>
#include <cmath>

class SparseTable
{
public:
	SparseTable(int size);
	SparseTable() {};
	void append(int x);
	void resize(int size);
	int rmq(int i, int j); // argmin [A[i:j+1] (including i and j), rightmost
	~SparseTable() {};
private:
	std::vector<std::vector<int>> ST; // ST[size][width_size]
	int width_size; // floor(lg_2(size))
	int num = 0;
	std::vector<int> A;
};

