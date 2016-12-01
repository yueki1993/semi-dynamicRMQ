#include "RMQ.h"
using namespace std;

void RMQ::append(int x)
{
	A[num] = x;
	int current_node = E[e_size - 1];
	while (A[current_node] >= x) {
		//if (A[current_node] >= x) {
		E[e_size++] = parents[current_node];
		D.append(--current_depth);
		current_node = parents[current_node];
#ifdef _DEBUG
		D_.push_back(current_depth);
#endif
	}

	E[e_size] = num;
	parents[num] = current_node;
	B[num] = e_size++;
	D.append(++current_depth);
#ifdef _DEBUG
	D_.push_back(current_depth);
#endif

	num++;
}


int RMQ::rmq(int i, int j)
{
	const int lca = D.rmq(B[i + 1], B[j + 1]);
	return lca == B[i + 1] ? A[E[lca]] : A[E[lca] +1];
}