#include "pm1RMQ.h"
#include "misc.h"

#include <climits>
#include <algorithm>

using namespace std;

typedef uint32_t uint;


void pm1RMQ::preprocessing()
{
	// compute all TableLookups of length blocklen-1, i.e., 2^(blocklen-1) patterns.
	for (uint b = 0; b < pow2(blocklen - 1); b++) {
		TLs[b].init(b, blocklen);
	}
}

void pm1RMQ::append(int x)
{
	int bpos = num % blocklen;
	int bnum = num / blocklen;
	auto& Block = InBlocks[bnum];

	// update inblock
	if (bpos == 0) {
		Block.set_diff(x);
		Block.set_ptr(&TLs[0]); //any TableLookup is ok.
		current_bit = 0u;
	} else {
		current_bit |= (lastval < x) << (bpos - 1);
		Block.set_ptr(&TLs[current_bit]);
	}

	// update sparse table
	if (bpos == blocklen - 1) {
		ST.append(Block.rmq(0, bpos));
	}

	lastval = x;
	num++;
}

int pm1RMQ::rmq(int i, int j)
{
	const int i_block_num = i / blocklen; // the block number where i belongs
	const int j_block_num = j / blocklen;
	
	const int i_block_pos = i % blocklen; // the position in the block where i belongs.
	const int j_block_pos = j % blocklen;
	
	if (i_block_num == j_block_num) {
		return InBlocks[i_block_num].rmq(i_block_pos, j_block_pos);
	}
	// the minimum val between i and the last position of the block where i belongs
	const int i_min = InBlocks[i_block_num].rmq(i_block_pos, blocklen - 1); 
	const int j_min = InBlocks[j_block_num].rmq(0, j_block_pos);
	
	const int i_next_block_num = i_block_num + 1;
	const int j_prev_block_num = j_block_num - 1;

	const int between = (i_next_block_num <= j_prev_block_num) ?
		ST.rmq(i_next_block_num, j_prev_block_num) : INT_MAX;

	return min(i_min, min(j_min, between));
}

pm1RMQ::~pm1RMQ()
{
}
