#include "stdafx.h"
#include "CppUnitTest.h"
#include "SparseTable.h"
#include "TableLookup.h"
#include "InBlock.h"
#include "BitTableLookup.h"
#include "pm1RMQ.h"
#include "RMQ.h"

#include <random>
#include <algorithm>
#include <iostream>

using namespace std;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(ST)
		{
			SparseTable st(10);
			for (int i = 0; i < 10; i++) {
				st.append(i);
			}
			Assert::AreEqual(0, st.rmq(0, 9));
			Assert::AreEqual(1, st.rmq(1, 1));
		}
		TEST_METHOD(ST2)
		{
			SparseTable st;
			st.resize(10);
			for (int i = 0; i < 10; i++) {
				st.append(i);
			}
			Assert::AreEqual(0, st.rmq(0, 9));
			Assert::AreEqual(1, st.rmq(1, 1));
		}
		TEST_METHOD(ST3)
		{
			SparseTable st;
			st.resize(10);
			for (int i = 0; i < 10; i++) {
				st.append(1);
			}
			Assert::AreEqual(0, st.rmq(0, 9));
		}

		TEST_METHOD(ST_random)
		{
			mt19937 mt(0);
			uniform_int_distribution<> rand(1, 1000);
			vector<int> v(1000);

			for (int i = 0; i < 1000; i++) {
				int n = rand(mt);
				SparseTable st(n);
				vector<int> v(n);				
				for (int j = 0; j < n; j++) {					
					v[j] = j;					
				}
				random_shuffle(v.begin(), v.end());
				for (int j = 0; j<n; j++)st.append(v[j]);
				uniform_int_distribution<> A(0, n-1);
				int a = A(mt);
				int b = A(mt);
				if (a > b) swap(a, b);
				int ans = 1 << 20;
				int pos = 0;
				for (int ii = a; ii <= b; ii++) {
					ans = min(ans, v[ii]);
					pos = ans == v[ii] ? ii : pos;
				}
				Assert::AreEqual(pos, st.rmq(a, b));
				
			}
		}

		TEST_METHOD(TL)
		{			
			vector<int> v;
			for (int i = 0; i < 10; i++) {
				v.push_back(i);
			}
			TableLookup tl(v);
			Assert::AreEqual(0, tl.rmq(0, 9));
			Assert::AreEqual(1, tl.rmq(1, 1));
		}

		TEST_METHOD(TL_random)
		{
			mt19937 mt(0);
			uniform_int_distribution<> rand(1, 1000);
			for (int i = 0; i < 100; i++) {
				int n = rand(mt);
				vector<int> v(n);
				for (int j = 0; j < n; j++) {
					int a = rand(mt);
					v[j] = a;
				}
				uniform_int_distribution<> A(0, n - 1);
				int a = A(mt);
				int b = A(mt);
				if (a > b) swap(a, b);
				int ans = 1 << 20;
				int pos = 0;
				for (int ii = a; ii <= b; ii++) {
					ans = min(ans, v[ii]); pos = ans == v[ii] ? ii : pos;
				}
			
				TableLookup tl(v);
				Assert::AreEqual(v[ans], tl.rmq(a, b));
			}
		}
		
		TEST_METHOD(BIT_TL)
		{
			do{
				BitTableLookup tl(0u, 3); // == {0, -1, -2, -3}				
				Assert::AreEqual(3, tl.rmq(0, 3));
				Assert::AreEqual(2, tl.rmq(0, 2));
				Assert::AreEqual(1, tl.rmq(0, 1));
				Assert::AreEqual(0, tl.rmq(0, 0));
			} while (0);
			
			
			do{ 
				BitTableLookup tl(1u, 3); // == {0, 1, 0, -1}
				Assert::AreEqual(3, tl.rmq(0, 3));
				Assert::AreEqual(0, tl.rmq(0, 2));
				Assert::AreEqual(2, tl.rmq(2, 2));
				Assert::AreEqual(0, tl.rmq(0, 1));
				Assert::AreEqual(0, tl.rmq(0, 0));
			} while (0);
			
			
			do {
				BitTableLookup tl(18u, 5); //0b10010 == {0, -1, 0, -1, -2, -1}
				Assert::AreEqual(4, tl.rmq(0, 5));
				Assert::AreEqual(1, tl.rmq(0, 3));
				Assert::AreEqual(1, tl.rmq(0, 2));
				Assert::AreEqual(4, tl.rmq(3, 5));
				Assert::AreEqual(4, tl.rmq(4, 5));
				Assert::AreEqual(4, tl.rmq(1, 4));
			} while (0);
		}
		TEST_METHOD(BIT_TL2)
		{

			
		}

		TEST_METHOD(pm1)
		{
			pm1RMQ p(10);			
			for (int i = 0; i < 10; i++) {
				p.append(i);
			}
			for (int i = 0; i < 10; i++) {
				for (int j = i; j < 10; j++) {
					Assert::AreEqual(i, p.rmq(i, j));
				}
			}
		}
		TEST_METHOD(pm1_2)
		{
			pm1RMQ p(4);
			vector<int> v = { 0, 1, 0, 1 };
			for (int i = 0; i < 4; i++) {
				p.append(v[i]);
			}
			Assert::AreEqual(0, p.rmq(0, 3));
			Assert::AreEqual(1, p.rmq(1, 1));

		}

		TEST_METHOD(pm1_rand)
		{
			mt19937 mt(0);
			uniform_int_distribution<> rand(1, 1000);
			uniform_int_distribution<> rand_bin(0, 1);

			for (int num = 0; num < 1; num++) {
				int N = rand(mt);
				pm1RMQ p(N);
				SparseTable st(N);
				int val = rand(mt);
				p.append(val);
				st.append(val);
				Assert::AreEqual(st.rmq(0, 0), p.rmq(0, 0));
				
				for (int i = 1; i < N; i++) {
					val += rand_bin(mt) == 0 ? -1 : 1;
					p.append(val);
					st.append(val);

					uniform_int_distribution<> A(0, i - 1);
					int a = A(mt);
					int b = A(mt);
					if (a > b) swap(a, b);
					Assert::AreEqual(st.rmq(a, b), p.rmq(a, b));
				}
			}
		}

		TEST_METHOD(RMQ_Euler_tour)
		{
			RMQ rmq(8);
			vector<int> X = { 4, 6, 5, 7, 3, 4, 5, 3 };
			for (auto x : X)rmq.append(x);
			
			vector<int> E = { 0, 1, 2, 1, 3, 4, 3, 1, 0, 5, 6, 7, 6, 5, 0, 8 };
			vector<int> D = { 0, 1, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 0, 1 };

			auto E_ = rmq.getE();
			Assert::AreEqual(E.size(), E_.size());
			for (int i = 0; i < E.size(); i++) {
				Assert::AreEqual(E[i], E_[i]);
			}

			auto D_ = rmq.getD();
			Assert::AreEqual(D.size(), D_.size());
			for (int i = 0; i < D.size(); i++) {
				Assert::AreEqual(D[i], D_[i]);
			}
		}

		TEST_METHOD(RMQ_static)
		{
			RMQ r(8);
			vector<int> X = { 4, 6, 5, 7, 3, 4, 5, 3 };
			for (auto x : X)r.append(x);

			Assert::AreEqual(5, r.rmq(1, 3));

		}



	};
}