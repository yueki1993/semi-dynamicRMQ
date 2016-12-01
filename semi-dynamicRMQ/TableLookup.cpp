//unused class
#include "TableLookup.h"
#include <vector>
#include <algorithm>

using namespace std;

TableLookup::TableLookup(const vector<int>& A)
{
	set(A);
}

TableLookup::TableLookup(int n)
{
	resize(n);
}

void TableLookup::resize(int n)
{
	TL.resize(n, vector<int>(n));
}

void TableLookup::set(const vector<int>& A)
{
	resize(A.size());
	compute_table(A);
}

void TableLookup::compute_table(const vector<int>& A)
{
	const int n = A.size();
	for (int i = 0; i < n; i++) {
		TL[i][i] = A[i];
		for (int j = i + 1; j < n; j++) {
			TL[i][j] = min(TL[i][j - 1], A[j]);
		}
	}
}

int TableLookup::rmq(int i, int j)
{
	return TL[i][j];
}

TableLookup::~TableLookup()
{
}
