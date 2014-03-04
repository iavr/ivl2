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

#ifndef IVL_CORE_ARRAY_FUN_FOLD_HPP
#define IVL_CORE_ARRAY_FUN_FOLD_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace afun {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

struct val_and
{
	INLINE constexpr bool operator()() const { return true; }

	template <typename A, typename... An>
	INLINE constexpr bool operator()(A&& a, An&&... an) const
		{ return fwd <A>(a) && operator()(fwd <An>(an)...); }
};

struct val_or
{
	INLINE constexpr bool operator()() const { return false; }

	template <typename A, typename... An>
	INLINE constexpr bool operator()(A&& a, An&&... an) const
		{ return fwd <A>(a) || operator()(fwd <An>(an)...); }
};

//-----------------------------------------------------------------------------

template <size_t Z = 0>
class val_first
{
	template <size_t I>
	INLINE constexpr size_t find(size <I>) const { return I; }

	template <size_t I, typename A, typename... An>
	INLINE constexpr size_t find(size <I>, A&& a, An&&... an) const
		{ return fwd <A>(a) ? I : find(size <I + 1>(), fwd <An>(an)...); }

public:
	template <typename... A>
	INLINE constexpr size_t
	operator()(A&&... a) const { return find(size <Z>(), fwd <A>(a)...); }
};

//-----------------------------------------------------------------------------

template <size_t Z = 0>
class val_last
{
	static constexpr size_t M = Z - 1;

	template <size_t I>
	INLINE constexpr size_t find(size <I>) const { return M; }

	template <size_t I, typename A, typename... An>
	INLINE constexpr size_t find(size <I>, A&& a, An&&... an) const
		{ return test <I>(fwd <A>(a), find(size <I + 1>(), fwd <An>(an)...)); }

	template <size_t I, typename A>
	INLINE constexpr size_t
	test(A&& a, size_t t) const { return t != M ? t : fwd <A>(a) ? I : M; }

public:
	template <typename... A>
	INLINE constexpr size_t
	operator()(A&&... a) const { return find(size <Z>(), fwd <A>(a)...); }
};

//-----------------------------------------------------------------------------

template <typename F>
struct val_fold
{
	template <typename A>
	INLINE constexpr copy <A>
	operator()(A&& a) const { return fwd <A>(a); }

	template <typename A, typename... An>
	INLINE constexpr copy <common <A, An...> >
	operator()(A&& a, An&&... an) const
		{ return F()(fwd <A>(a), operator()(fwd <An>(an)...)); }
};

//-----------------------------------------------------------------------------

struct val_min_fun
{
	template <typename A, typename B>
	INLINE constexpr copy <common <A, B> >
	operator()(A&& a, B&& b) const
		{ return a < b ? fwd <A>(a) : fwd <B>(b); }
};

struct val_max_fun
{
	template <typename A, typename B>
	INLINE constexpr copy <common <A, B> >
	operator()(A&& a, B&& b) const
		{ return a > b ? fwd <A>(a) : fwd <B>(b); }
};

//-----------------------------------------------------------------------------

using val_min  = val_fold <val_min_fun>;
using val_max  = val_fold <val_max_fun>;
using val_sum  = val_fold <afun::op::plus>;
using val_prod = val_fold <afun::op::mul>;

//-----------------------------------------------------------------------------

}  // namespace details

using details::val_and;
using details::val_or;

using details::val_first;
using details::val_last;

using details::val_fold;
using details::val_min;
using details::val_max;
using details::val_sum;
using details::val_prod;

//-----------------------------------------------------------------------------

}  // namespace afun

static __attribute__ ((unused)) afun::val_and  val_and;
static __attribute__ ((unused)) afun::val_or   val_or;

static __attribute__ ((unused)) afun::val_first <> val_first;
static __attribute__ ((unused)) afun::val_last  <> val_last;

static __attribute__ ((unused)) afun::val_min   val_min;
static __attribute__ ((unused)) afun::val_max   val_max;
static __attribute__ ((unused)) afun::val_sum   val_sum;
static __attribute__ ((unused)) afun::val_prod  val_prod;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_FUN_FOLD_HPP
