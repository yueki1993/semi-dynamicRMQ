#include "SparseTable.h"
#include "misc.h"
#include <cmath>
#include <algorithm>

using namespace std;


SparseTable::SparseTable(int size) : width_size(floor_log2(size)+1)
{
	resize(size);
}

void SparseTable::resize(int size)
{
	width_size = floor_log2(size) + 1;
	ST.resize(size, vector<int>(width_size));
}

void SparseTable::append(int x)
{
	int i = num;
	ST[i][0] = x;
	for (int j = 1; j < width_size; j++) {
		if (i + 1 >= pow2(j)) {
			ST[i - pow2(j) + 1][j] = min(ST[i - pow2(j) + 1][j - 1], ST[i - pow2(j - 1) + 1][j - 1]);
		}
	}
	num++;
}

int SparseTable::rmq(int i, int j)
{
	int l = floor_log2(j - i + 1);
	return min(ST[i][l], ST[j - pow2(l) + 1][l]);
}