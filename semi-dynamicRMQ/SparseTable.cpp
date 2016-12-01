#include "SparseTable.h"
#include "misc.h"
#include <cmath>
#include <algorithm>

using namespace std;



void SparseTable::append(int x)
{
	int i = num;
	A[i] = x;
	ST[i][0] = i;
	for (int j = 1; j < width_size; j++) {
		if (i + 1 >= pow2(j)) {
			ST[i - pow2(j) + 1][j] = A[ST[i - pow2(j) + 1][j - 1]] < A[ST[i - pow2(j - 1) + 1][j - 1]] ?
				ST[i - pow2(j) + 1][j - 1] : ST[i - pow2(j - 1) + 1][j - 1];

		}
	}
	num++;
}