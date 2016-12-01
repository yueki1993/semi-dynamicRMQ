#pragma once

#include <cmath>
#include <cinttypes>

#ifdef _MSC_VER
#include <intrin.h>
#ifdef _WIN32
inline unsigned int __builtin_ctz(unsigned int x) { unsigned long r; _BitScanForward(&r, x); return r; }
inline unsigned int __builtin_clz(unsigned int x) { unsigned long r; _BitScanReverse(&r, x); return 31 - r; }
inline unsigned int __builtin_ffs(unsigned int x) { unsigned long r; return _BitScanForward(&r, x) ? r + 1 : 0; }
inline unsigned int __builtin_popcount(unsigned int x) { return __popcnt(x); }
#ifdef _WIN64
inline unsigned long long __builtin_ctzll(unsigned long long x) { unsigned long r; _BitScanForward64(&r, x); return r; }
inline unsigned long long __builtin_clzll(unsigned long long x) { unsigned long r; _BitScanReverse64(&r, x); return 63 - r; }
inline unsigned long long __builtin_ffsll(unsigned long long x) { unsigned long r; return _BitScanForward64(&r, x) ? r + 1 : 0; }
inline unsigned long long __builtin_popcountll(unsigned long long x) { return __popcnt64(x); }
#else
inline unsigned int hidword(unsigned long long x) { return static_cast<unsigned int>(x >> 32); }
inline unsigned int lodword(unsigned long long x) { return static_cast<unsigned int>(x & 0xFFFFFFFF); }
inline unsigned long long __builtin_ctzll(unsigned long long x) { return lodword(x) ? __builtin_ctz(lodword(x)) : __builtin_ctz(hidword(x)) + 32; }
inline unsigned long long __builtin_clzll(unsigned long long x) { return hidword(x) ? __builtin_clz(hidword(x)) : __builtin_clz(lodword(x)) + 32; }
inline unsigned long long __builtin_ffsll(unsigned long long x) { return lodword(x) ? __builtin_ffs(lodword(x)) : hidword(x) ? __builtin_ffs(hidword(x)) + 32 : 0; }
inline unsigned long long __builtin_popcountll(unsigned long long x) { return __builtin_popcount(lodword(x)) + __builtin_popcount(hidword(x)); }
#endif // _WIN64
#endif // _WIN32
#endif // _MSC_VER

inline int floor_log2(int x)
{
	//return: floor(log_2(x))
	//int v = (int)log2(x);
	//assert(v == 31 - __builtin_clz(x));
	return (31 - __builtin_clz(x));
}

inline int ceildiv(int a, int b)
{
	//return  ceil(a/b), a!=0
	return 1 + ((a - 1) / b);
}

inline int pow2(int x)
{
	// return 2^x
	return 1 << x;
}

inline int get_ith_bit(uint32_t b, int i)
{
	// return ith bit from LSB
	return (b >> i) & 1;
}
