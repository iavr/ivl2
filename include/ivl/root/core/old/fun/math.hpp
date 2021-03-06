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

#ifndef IVL_CORE_ARRAY_FUN_MATH_HPP
#define IVL_CORE_ARRAY_FUN_MATH_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace math {

//-----------------------------------------------------------------------------

namespace afun {

using namespace types::traits;

//-----------------------------------------------------------------------------

#define IVL_FUN1(NAME, FUN)      \
                                 \
struct NAME                      \
{                                \
	template <typename T>         \
	INLINE constexpr auto         \
	operator()(T x) const         \
	-> decltype(FUN(x))           \
		{ return FUN(x); }         \
};

//-----------------------------------------------------------------------------

IVL_FUN1(abs,   std::abs)
IVL_FUN1(floor, std::floor)
IVL_FUN1(ceil,  std::ceil)
IVL_FUN1(round, ::round)

//-----------------------------------------------------------------------------

struct is_int
{
	template <typename T>
	INLINE constexpr bool
	operator()(T x) const { return x == floor()(x); }
};

//-----------------------------------------------------------------------------

struct exp
{
	template <typename T>
	INLINE constexpr auto operator()(T x) const
	-> decltype(std::exp(x))
		{ return std::exp(x); }

	template <typename B, typename T>
	INLINE constexpr auto operator()(B base, T x) const
	-> decltype(std::pow(base, x))
	{
		CHECK((base >= 0 || is_int()(x)) && (base || x > 0), e_domain);
		return std::pow(base, x);
	}
};

//-----------------------------------------------------------------------------

struct log
{
	template <typename T>
	INLINE constexpr auto operator()(T x) const
	->decltype(std::log(x))
	{
		CHECK(x > 0, e_domain);
		return std::log(x);
	}

	template <typename B, typename T>
	INLINE constexpr auto operator()(B base, T x) const
	-> decltype((*this)(x) / (*this)(base))
	{
		CHECK(base != 1, e_domain);
		return (*this)(x) / (*this)(base);
	}
};

//-----------------------------------------------------------------------------

struct exp2
{
	template <typename T>
	INLINE constexpr auto operator()(T x) const
	-> decltype(is_integral <T>() ? 1 << x : exp()(2, x))
		{ return is_integral <T>() ? 1 << x : exp()(2, x); }
};

struct log2
{
	template <typename T>
	INLINE constexpr auto operator()(T x) const
	-> decltype(is_integral <T>() ? platform::math::log2(x) : log()(2, x))
		{ return is_integral <T>() ? platform::math::log2(x) : log()(2, x); }
};

//-----------------------------------------------------------------------------

struct exp10
{
	template <typename T>
	INLINE constexpr auto operator()(T x) const
	-> decltype(exp()(10, x))
		{ return exp()(10, x); }
};

struct log10
{
	template <typename T>
	INLINE constexpr auto operator()(T x) const
	-> decltype(log()(10, x))
		{ return log()(10, x); }
};

//-----------------------------------------------------------------------------

struct prev_pow
{
	template <typename B, typename T>
	INLINE constexpr auto operator()(B base, T x) const
	-> decltype(exp()(base, floor()(log()(base, x))))
		{ return exp()(base, floor()(log()(base, x))); }
};

struct prev_pow2
{
	template <typename T>
	INLINE constexpr auto operator()(T x) const
	-> decltype(is_integral <T>() ?
		platform::math::prev_pow2(x) : prev_pow()(2, x))
	{
		return is_integral <T>() ?
			platform::math::prev_pow2(x) : prev_pow()(2, x);
	}
};

struct prev_pow10
{
	template <typename T>
	INLINE constexpr auto operator()(T x) const
	-> decltype(prev_pow()(10, x))
		{ return prev_pow()(10, x); }
};

//-----------------------------------------------------------------------------

struct next_pow
{
	template <typename B, typename T>
	INLINE constexpr auto operator()(B base, T x) const
	-> decltype(exp()(base, floor()(log()(base, x)) + 1))
		{ return exp()(base, floor()(log()(base, x)) + 1); }
};

struct next_pow2
{
	template <typename T>
	INLINE constexpr auto operator()(T x) const
	-> decltype(is_integral <T>() ?
		platform::math::next_pow2(x) : next_pow()(2, x))
	{
		return is_integral <T>() ?
			platform::math::next_pow2(x) : next_pow()(2, x);
	}
};

struct next_pow10
{
	template <typename T>
	INLINE constexpr auto operator()(T x) const
	-> decltype(next_pow()(10, x))
		{ return next_pow()(10, x); }
};

//-----------------------------------------------------------------------------

struct is_pow_of
{
	template <typename B, typename T>
	INLINE constexpr bool operator()(B base, T x) const
		{ return x == exp()(base, floor()(log()(base, x))); }
};

struct is_pow_of2
{
	template <typename T>
	INLINE constexpr bool operator()(T x) const
	{
		return is_integral <T>() ?
			platform::math::is_pow_of2(x) : is_pow_of()(2, x);
	}
};

//-----------------------------------------------------------------------------

}  // namespace afun

//-----------------------------------------------------------------------------

static __attribute__ ((unused)) afun::floor       floor;
static __attribute__ ((unused)) afun::ceil        ceil;
static __attribute__ ((unused)) afun::round       round;
static __attribute__ ((unused)) afun::is_int      is_int;
static __attribute__ ((unused)) afun::exp         exp,   pow;
static __attribute__ ((unused)) afun::exp2        exp2,  pow2;
static __attribute__ ((unused)) afun::exp10       exp10, pow10;
static __attribute__ ((unused)) afun::log         log;
static __attribute__ ((unused)) afun::log2        log2;
static __attribute__ ((unused)) afun::log10       log10;
static __attribute__ ((unused)) afun::prev_pow    prev_pow;
static __attribute__ ((unused)) afun::prev_pow2   prev_pow2;
static __attribute__ ((unused)) afun::prev_pow10  prev_pow10;
static __attribute__ ((unused)) afun::next_pow    next_pow;
static __attribute__ ((unused)) afun::next_pow2   next_pow2;
static __attribute__ ((unused)) afun::next_pow10  next_pow10;
static __attribute__ ((unused)) afun::is_pow_of   is_pow_of;
static __attribute__ ((unused)) afun::is_pow_of2  is_pow_of2;

//-----------------------------------------------------------------------------

}  // namespace math

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_FUN_MATH_HPP
