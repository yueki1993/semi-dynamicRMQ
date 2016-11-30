#include "stdafx.h"
#include "CppUnitTest.h"
#include "SparseTable.h"
#include "TableLookup.h"
#include "InBlock.h"
#include "BitTableLookup.h"
#include "pm1RMQ.h"

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
		TEST_METHOD(ST_random)
		{
			mt19937 mt(0);
			uniform_int_distribution<> rand(1, 1000);
			for (int i = 0; i < 1000; i++) {
				int n = rand(mt);
				SparseTable st(n);
				vector<int> v(n);
				for (int j = 0; j < n; j++) {
					int a = rand(mt);
					st.append(a);
					v[j] = a;					
				}
				uniform_int_distribution<> A(0, n-1);
				int a = A(mt);
				int b = A(mt);
				if (a > b) swap(a, b);
				int ans = 1 << 20;
				for (int ii = a; ii <= b; ii++) {ans = min(ans, v[ii]);}
				Assert::AreEqual(ans, st.rmq(a, b));
				
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
				for (int ii = a; ii <= b; ii++) { ans = min(ans, v[ii]); }
				TableLookup tl(v);
				Assert::AreEqual(ans, tl.rmq(a, b));
			}
		}
		
		TEST_METHOD(BIT_TL)
		{
			do{
				BitTableLookup tl(0u, 3); // == {0, -1, -2, -3}

				Assert::AreEqual(-3, tl.rmq(0, 3));
				Assert::AreEqual(-2, tl.rmq(0, 2));
				Assert::AreEqual(-1, tl.rmq(0, 1));
				Assert::AreEqual(0, tl.rmq(0, 0));
			} while (0);
			

			do{ 
				BitTableLookup tl(1u, 3); // == {0, 1, 0, -1}
				Assert::AreEqual(-1, tl.rmq(0, 3));
				Assert::AreEqual(0, tl.rmq(0, 2));
				Assert::AreEqual(0, tl.rmq(0, 1));
				Assert::AreEqual(0, tl.rmq(0, 0));
			} while (0);
			

			do {
				BitTableLookup tl(18u, 5); //0b10010 == {0, -1, 0, -1, -2, -1}
				Assert::AreEqual(-2, tl.rmq(0, 5));
				Assert::AreEqual(-1, tl.rmq(0, 3));
				Assert::AreEqual(-1, tl.rmq(0, 2));
				Assert::AreEqual(-2, tl.rmq(3, 5));
				Assert::AreEqual(-2, tl.rmq(4, 5));
				Assert::AreEqual(-2, tl.rmq(1, 4));
			} while (0);
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

		TEST_METHOD(pm1_rand)
		{
			mt19937 mt(0);
			uniform_int_distribution<> rand(1, 1000);
			uniform_int_distribution<> rand_bin(0, 1);

			for (int num = 0; num < 1000; num++) {
				cout << num << endl;
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



	};
}