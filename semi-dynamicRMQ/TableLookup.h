#pragma once
#include <vector>

class TableLookup
{
public:
	TableLookup(const std::vector<int>& A);
	TableLookup(int size);
	TableLookup() {};
	void set(const std::vector<int>& A);
	int rmq(int i, int j);
	~TableLookup();
private:
	std::vector<std::vector<int>> TL;
	void resize(int n);
	void compute_table(const std::vector<int>& A);
};

