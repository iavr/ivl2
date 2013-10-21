/* This file is part of the ivl C++ library <http://image.ntua.gr/ivl>.
   A C++ template library extending syntax towards mathematical notation.

   Copyright (C) 2012 Yannis Avrithis <iavr@image.ntua.gr>
   Copyright (C) 2012 Kimon Kontosis <kimonas@image.ntua.gr>

   ivl is free software; you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License
   version 3 as published by the Free Software Foundation.

   Alternatively, you can redistribute it and/or modify it under the terms
   of the GNU General Public License version 2 as published by the Free
   Software Foundation.

   ivl is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
   See the GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   and a copy of the GNU Lesser General Public License along
   with ivl. If not, see <http://www.gnu.org/licenses/>. */

//-----------------------------------------------------------------------------

#ifndef IVL_DETAILS_CORE_PLATFORM_MATH_HPP
#define IVL_DETAILS_CORE_PLATFORM_MATH_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace platform {

//-----------------------------------------------------------------------------

namespace math {

// TODO: all constexpr in C++1y

//-----------------------------------------------------------------------------

#ifdef _MSC_VER

//-----------------------------------------------------------------------------
// TODO: check MSVC requirements -- <intrin.h> ?

// bit scan reverse instruction, or count leading zeros (CLZ)
template <typename T>
INLINE auto BSR(T x)
	-> decltype(sizeof(T) >= 8 ?
		_BitScanReverse64(&out, x) : _BitScanReverse(&out, x))
{
	static T out;
	sizeof(T) >= 8 ?
		_BitScanReverse64(&out, x) : _BitScanReverse(&out, x);
	return out;
}

// population count instruction (number of bits set)
template <typename T>
INLINE auto POPCNT(T x)
	-> decltype(sizeof(T) >= 8 ? __popcnt64(x) : __popcnt(x))
	{ return sizeof(T) >= 8 ? __popcnt64(x) : __popcnt(x); }

//-----------------------------------------------------------------------------

#else  // _MSC_VER

//-----------------------------------------------------------------------------

// bit scan reverse instruction, or count leading zeros (CLZ)
template <typename T>
INLINE auto BSR(T x)
	-> decltype(sizeof(T) >= 8 ? __builtin_clzll(x) : __builtin_clz(x))
	{ return sizeof(T) >= 8 ? __builtin_clzll(x) : __builtin_clz(x); }

// population count instruction (number of bits set)
// gcc/clang require -msse4.2 flag
template <typename T>
INLINE auto POPCNT(T x)
	-> decltype(sizeof(T) >= 8 ?
		__builtin_popcountll(x) : __builtin_popcount(x))
{
	return sizeof(T) >= 8 ?
		__builtin_popcountll(x) : __builtin_popcount(x);
}

//-----------------------------------------------------------------------------

#endif  // _MSC_VER

//-----------------------------------------------------------------------------

// number of bits for given integer type
template <typename T>
INLINE auto bits()
	-> decltype(sizeof(T) << 3)
	{ return (sizeof(T) << 3); }

// most significant bit position for given integer type
template <typename T>
INLINE auto msb()
	-> decltype(bits <T>() - 1)
	{ return bits <T>() - 1; }

//-----------------------------------------------------------------------------

// log2 for integer type
template <typename T>
INLINE auto log2(T x)
	-> decltype(msb <T>() - BSR(x))
{
	CHECK(x > 0, e_domain);
	return msb <T>() - BSR(x);
}

// previous power of 2 for integer type
template <typename T>
INLINE auto prev_pow2(T x)
	-> decltype(1 << (msb <T>() - BSR(x)))
{
	CHECK(x > 0, e_domain);
	return 1 << (msb <T>() - BSR(x));
}

// next power of 2 for integer type
template <typename T>
INLINE auto next_pow2(T x)
	-> decltype(1 << (bits <T>() - BSR(x)))
{
	CHECK(x > 0, e_domain);
	return 1 << (bits <T>() - BSR(x));
}

// is power of 2 for integer type
template <typename T>
INLINE bool is_pow_of2(T x)
{
	return POPCNT(x) == 1;
}

//-----------------------------------------------------------------------------

}  // namespace math

//-----------------------------------------------------------------------------

}  // namespace platform

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_PLATFORM_MATH_HPP
