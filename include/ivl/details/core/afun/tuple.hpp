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

#ifndef IVL_DETAILS_CORE_AFUN_TUPLE_HPP
#define IVL_DETAILS_CORE_AFUN_TUPLE_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace afun_details {

//-----------------------------------------------------------------------------

template <
	template <typename...> class T = tuple,
	template <typename...> class F = id,
	template <typename...> class E = always
>
struct val_of
{
	template <typename... A, enable_if <E <A...>{}> = 0>
	inline T <F <decay <A> >...>
	operator()(A&&... a) const { return T <F <decay <A> >...>(fwd <A>(a)...); }

// 	TODO: gcc ICE: no constexpr, no F <>, no decay <>
// 	template <typename... A, enable_if <E <A...>{}> = 0>
// 	inline T <typename decay_t <A>::type...>
// 	operator()(A&&... a) const { return T <typename decay_t <A>::type...>(fwd <A>(a)...); }
};

//-----------------------------------------------------------------------------

template <
	template <typename...> class T = tuple,
	template <typename...> class F = id,
	template <typename...> class E = always
>
struct rref_of
{
	template <typename... A, enable_if <E <A...>{}> = 0>
	inline constexpr T <F <A&&>...>
	operator()(A&&... a) const { return T <F <A&&>...>(fwd <A>(a)...); }
};

//-----------------------------------------------------------------------------

template <
	template <typename...> class T = tuple,
	template <typename...> class F = id,
	template <typename...> class E = always
>
struct lref_of
{
	template <typename... A, enable_if <all <E, A...>{}> = 0>
	inline constexpr T <F <A&>...>
	operator()(A&... a) const { return T <F <A&>...>(a...); }
};

//-----------------------------------------------------------------------------

template <
	template <typename...> class T = tuple,
	template <typename...> class F = id,
	template <typename...> class E = always
>
struct clref_of
{
	template <typename... A, enable_if <all <E, A...>{}> = 0>
	inline constexpr T <F <const A&>...>
	operator()(const A&... a) const { return T <F <const A&>...>(a...); }
};

//-----------------------------------------------------------------------------

using val_   = val_of <>;
using rref_  = rref_of <>;
using lref_  = lref_of <>;
using clref_ = clref_of <>;

//-----------------------------------------------------------------------------

using tup_join = rref_of <join_tup, id, all_tuple>;
using tup_     = rref_of <join_tup, wrap>;

using tup_zip   = rref_of <zip_tup, id,   all_tuple>;
using tup_inner = rref_of <zip_tup, wrap, any_tuple>;

static __attribute__ ((unused)) tup_join  _join;
static __attribute__ ((unused)) tup_zip   _zip;
static __attribute__ ((unused)) tup_inner _inner;

//-----------------------------------------------------------------------------

struct tup_head
{
	template <typename T, enable_if <as_tup_non_empty <T>{}> = 0>
	inline constexpr auto operator()(T&& t) const
		-> decltype(at._<0>(fwd <T>(t)))
		{ return at._<0>(fwd <T>(t)); }
};

//-----------------------------------------------------------------------------

struct tup_tail
{
	template <typename T, enable_if <as_tup_non_empty <T>{}> = 0>
	inline constexpr auto operator()(T&& t) const
		-> decltype(at._<sz_range <1, tup_len <T>() - 1> >(fwd <T>(t)))
		{ return at._<sz_range <1, tup_len <T>() - 1> >(fwd <T>(t)); }
};

//-----------------------------------------------------------------------------

struct tup_flip
{
	template <typename T, enable_if <tup_empty <T>{} || is_atom <T>{}> = 0>
	inline constexpr T&& operator()(T&& t) const { return fwd <T>(t); }

	template <typename T, enable_if <tup_non_empty <T>{}> = 0>
	inline constexpr auto operator()(T&& t) const
		-> decltype(at._<sz_range <tup_len <T>() - 1, 0, -1> >(fwd <T>(t)))
		{ return at._<sz_range <tup_len <T>() - 1, 0, -1> >(fwd <T>(t)); }
};

//-----------------------------------------------------------------------------

struct tup_call
{
	template <typename F, typename T>
	inline constexpr auto operator()(F&& f, T&& t) const
		-> decltype(fwd <T>(t).call(fwd <F>(f)))
		{ return fwd <T>(t).call(fwd <F>(f)); }
};

//-----------------------------------------------------------------------------

static __attribute__ ((unused)) tup_head _head;
static __attribute__ ((unused)) tup_tail _tail;
static __attribute__ ((unused)) tup_flip _flip;
static __attribute__ ((unused)) tup_call _call;

//-----------------------------------------------------------------------------

}  // namespace afun_details

//-----------------------------------------------------------------------------

namespace afun {

using afun_details::val_of;
using afun_details::rref_of;
using afun_details::lref_of;
using afun_details::clref_of;

using val   = afun_details::val_;
using rref  = afun_details::rref_;
using lref  = afun_details::lref_;
using clref = afun_details::clref_;

using tup = afun_details::tup_;

}  // namespace afun

//-----------------------------------------------------------------------------

static __attribute__ ((unused)) afun::val    val;
static __attribute__ ((unused)) afun::rref   rref;
static __attribute__ ((unused)) afun::lref   lref;
static __attribute__ ((unused)) afun::clref  clref;

static __attribute__ ((unused)) afun::tup    tup;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_AFUN_TUPLE_HPP