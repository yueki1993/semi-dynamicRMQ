#pragma once

#include <vector>
#include <climits>
#include "pm1RMQ.h"

class RMQ
{
public:
	RMQ(int size) :A(size + 1), B(size + 1), E(2 * size), D(2 * size), parents(size + 1) {
		A[0] = INT_MIN;
		parents[0] = -1;
		E[0] = 0;
		D.append(0);

#ifdef _DEBUG		
		D_.push_back(0);
#endif
	};
	void append(int x);
	int rmq(int i, int j); // argmin, rightmost
	~RMQ() {};

	//for tests
#ifdef _DEBUG
	std::vector<int> getB() { return B; } 
	std::vector<int> getE() { return E; } 
	std:: vector<int> getD() { return D_; }
#endif


private:
	std::vector<int> A; // raw values, A[0] = -\infty
	std::vector<int> B; //B[i] = min{0 <= j < |E| : E[j] = i}
	std::vector<int> E;// labels computed by traversing the euler tour of the 2d-min-heap in preorder
	std::vector<int> parents; //parents of each nodes in the 2d-min-heap
#ifdef _DEBUG
	std::vector<int> D_; // for test only
#endif
	pm1RMQ D; // depths are maintained by the pm1 RMQ

	int num = 1; // Since A[0] is initially set to -\infty, it begins size-1.
	int e_size = 1; // current size of E
	int current_depth = 0;
};

