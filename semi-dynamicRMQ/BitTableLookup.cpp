#include "BitTableLookup.h"
#include "misc.h"
#include <algorithm>

typedef uint32_t uint;
using namespace std;

static inline int f(int i)
{
	//f(1) = 1, f(0) = -1
	return i - (!i);
}

BitTableLookup::BitTableLookup(uint  bit, int bitwidth)
{
	init(bit, bitwidth);
}

void BitTableLookup::init(uint  bit, int bitwidth)
{
	// 0b110 <=> [0, -1, 0, 1] (LSB represents A[1] - A[0])
	const int N = bitwidth + 1;
	TL.resize(N, vector<int>(N));

	int Ai = 0;
	int Aj;
	for (int i = 0; i < N; i++) {
		TL[i][i] = i;
		Aj = Ai;
		int minval = Aj;
		int minpos = i;
		for (int j = i + 1; j < N; j++) {
			// update Aj
			Aj += f(get_ith_bit(bit, j - 1));
			//TL[i][j] = (TL[i][j - 1], Aj);
			if (minval < Aj) {
				TL[i][j] = minpos;
			} else {
				TL[i][j] = j;		
				minval = Aj;
				minpos = j;
			}
			
		}
		Ai += f(get_ith_bit(bit, i));
	}
}

