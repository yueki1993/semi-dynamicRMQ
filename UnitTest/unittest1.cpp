#include "stdafx.h"
#include "CppUnitTest.h"
#include "SparseTable.h"
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
	TEST_CLASS(ST_TEST)
	{
	public:
		TEST_METHOD(TEST1)
		{
			SparseTable st(10);
			for (int i = 0; i < 10; i++) {
				st.append(i);
			}
			Assert::AreEqual(0, st.rmq(0, 9));
			Assert::AreEqual(1, st.rmq(1, 1));
		}
		TEST_METHOD(TEST2)
		{
			SparseTable st;
			st.resize(10);
			for (int i = 0; i < 10; i++) {
				st.append(i);
			}
			Assert::AreEqual(0, st.rmq(0, 9));
			Assert::AreEqual(1, st.rmq(1, 1));
		}
		TEST_METHOD(TEST3)
		{
			SparseTable st;
			st.resize(10);
			for (int i = 0; i < 10; i++) {
				st.append(1);
			}
			Assert::AreEqual(9, st.rmq(0, 9));
		}

		TEST_METHOD(RANDOM)
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
				uniform_int_distribution<> A(0, n - 1);
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
	};

	TEST_CLASS(BIT_TL_TEST)
	{
	public:
		TEST_METHOD(TEST1)
		{
			BitTableLookup tl(0u, 3); // 0b000 == {0, -1, -2, -3}				
			Assert::AreEqual(3, tl.rmq(0, 3));
			Assert::AreEqual(2, tl.rmq(0, 2));
			Assert::AreEqual(1, tl.rmq(0, 1));
			Assert::AreEqual(0, tl.rmq(0, 0));

		}
		TEST_METHOD(TEST2)
		{
			BitTableLookup tl(18u, 5); //0b10010 == {0, -1, 0, -1, -2, -1}
			Assert::AreEqual(4, tl.rmq(0, 5));
			Assert::AreEqual(3, tl.rmq(0, 3));
			Assert::AreEqual(1, tl.rmq(0, 2));
			Assert::AreEqual(4, tl.rmq(3, 5));
			Assert::AreEqual(4, tl.rmq(4, 5));
			Assert::AreEqual(4, tl.rmq(1, 4));
		}
	};

	TEST_CLASS(pm1RMQ_TEST)
	{
	public:
		TEST_METHOD(TEST1)
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
		TEST_METHOD(TEST2)
		{
			pm1RMQ p(4);
			vector<int> v = { 0, 1, 0, 1 };
			for (int i = 0; i < 4; i++) {
				p.append(v[i]);
			}
			Assert::AreEqual(2, p.rmq(0, 3));
			Assert::AreEqual(1, p.rmq(1, 1));

		}

		TEST_METHOD(RANDOM)
		{
			mt19937 mt(0);
			uniform_int_distribution<> rand(1, 1000);
			uniform_int_distribution<> rand_bin(0, 1);

			for (int num = 0; num < 1000; num++) {
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

	TEST_CLASS(RMQ_TEST)
	{
	public:
		TEST_METHOD(EULER_TOUR)
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

		TEST_METHOD(TEST1)
		{
			RMQ r(8);
			vector<int> X = { 4, 6, 5, 7, 3, 4, 5, 3 };
			for (auto x : X)r.append(x);

			Assert::AreEqual(2, r.rmq(1, 3));
			Assert::AreEqual(0, r.rmq(0, 0));
			Assert::AreEqual(3, r.rmq(3, 3));
			Assert::AreEqual(7, r.rmq(7, 7));
			Assert::AreEqual(4, r.rmq(4, 6));
		}

		TEST_METHOD(RIGHTMOST)
		{
			RMQ r(8);
			for (int i = 0; i < 8; i++)r.append(1);

			Assert::AreEqual(3, r.rmq(1, 3));
			Assert::AreEqual(6, r.rmq(4, 6));
			Assert::AreEqual(7, r.rmq(7, 7));
		}

		TEST_METHOD(TEST2)
		{
			vector<int> v{ 0, 3, 4, 2, 1 };
			SparseTable st(v.size());
			RMQ r(v.size());
			for (auto x : v)st.append(x), r.append(x);
			Assert::AreEqual(st.rmq(0, st.rmq(0, v.size() - 1)),
				r.rmq(0, v.size() - 1));
		}

		TEST_METHOD(RANDOM)
		{
			mt19937 mt(0);
			uniform_int_distribution<> rand(1, 1000);

			for (int i = 0; i < 1000; i++) {
				int n = rand(mt);
				SparseTable st(n);
				RMQ r(n);
				for (int j = 0; j < n; j++) {
					int a = rand(mt);
					st.append(a);
					r.append(a);
				}

				uniform_int_distribution<> A(0, n - 1);
				int a = A(mt);
				int b = A(mt);
				if (a > b)swap(a, b);
				Assert::AreEqual(st.rmq(a, b), r.rmq(a, b));
			}
		}
	};
}