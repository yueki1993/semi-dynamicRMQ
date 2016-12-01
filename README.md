semi-dynamic range minimum query
================================
The semi-dynamic range minimum query algorithm that maintains an array A and supports the following two operations:  
- `append(x)`:   
append x to the end of A in amortized constant time.  
- `rmq(i, j)`:  
return the (rightmost) **position** of the minimum value in the subarray A[i], ..., A[j] in constant time.

## Example
    #include "RMQ.h"

    [...]
        {
            RMQ r(8);
            vector<int> X = { 4, 6, 5, 7, 3, 4, 5, 3 };
            for (auto x : X) r.append(x);

            Assert::AreEqual(4, r.rmq(0, 7)); // argmin(X) = 4 because X[4] == 3. 
            Assert::AreEqual(7, r.rmq(4, 7)); // X[4] == X[7] == 3, but return the rightmost one.
        }


## Implementations
- semi-dynamicRMQ/RMQ.*  
The proposed algorithm in [2].
- semi-dynamicRMQ/pm1RMQ  
The ±1RMQ algorithm in [1] based on the sparse table algorithm and table lookup algorithm.
- semi-dynamicRMQ/SparseTable.*  
The sparse table algorithm proposed in [1].
- semi-dynamicRMQ/BitTableLookup.*
The table lookup algorithm proposed in [1] using some bitwise operations.
- UnitTest/unittest1.cpp  
Unittest. To run this code, Microsoft Visual Studio is required.

## Remark
Although I did not confirm that these implementations can be compiled with gcc or clang,
but I suppose that these can be compiled with C++11 option `-std=c++11`.  


## References
[1] M. A. Bender & M. Farach-Colton: The LCA problem revisited. In _LATIN 2000_, pp.88-94, 2000.  
[2] Y. Ueki, Diptarama, M. Kurihara, Y. Matsuoka, K. Narisawa, R. Yoshinaka, H. Bannai, S. Inenaga, A. Shinohara: Longest common subsequence in at least k length order-isomorphic substrings. In _SOFSEM 2017_
 https://arxiv.org/abs/1609.03668
 