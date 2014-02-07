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

#ifndef IVL_CORE_TUPLE_FUN_MANIP_HPP
#define IVL_CORE_TUPLE_FUN_MANIP_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace afun {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

using tup_join = uref_of <join_tup, all_tuple>;
using tup      = uref_of <join_tuple>;

using tup_zip   = uref_of <zip_tup,   all_tuple>;
using tup_inner = uref_of <zip_tuple, any_tuple>;

//-----------------------------------------------------------------------------

struct tup_head
{
	template <typename T, only_if <!is_tuple <T>{}> = 0>
	INLINE constexpr T&& operator()(T&& t) const { return fwd <T>(t); }

	template <typename T, only_if <tup_non_empty <T>{}> = 0>
	INLINE constexpr auto operator()(T&& t) const
	-> decltype(at()._<0>(fwd <T>(t)))
		{ return at()._<0>(fwd <T>(t)); }
};

//-----------------------------------------------------------------------------

template <template <typename...> class O = base_opt>
struct tup_tail_of
{
	template <typename T, only_if <!is_tuple <T>{}> = 0>
	INLINE constexpr T&& operator()(T&& t) const { return fwd <T>(t); }

	template <typename T, only_if <tup_non_empty <T>{}> = 0>
	INLINE constexpr tail_tup <subs <O, T> >
	operator()(T&& t) const { return tail_tup <subs <O, T> >(fwd <T>(t)); }
};

using tup_tail = tup_tail_of <>;

//-----------------------------------------------------------------------------

struct tup_flip
{
	template <typename T, only_if <tup_empty <T>{}> = 0>
	INLINE constexpr T&& operator()(T&& t) const { return fwd <T>(t); }

	template <typename T, only_if <tup_non_empty <T>{}> = 0>
	INLINE constexpr auto operator()(T&& t) const
	-> decltype(at()._<sz_range <tup_len <T>() - 1, 0, -1> >(fwd <T>(t)))
		{ return at()._<sz_range <tup_len <T>() - 1, 0, -1> >(fwd <T>(t)); }
};

//-----------------------------------------------------------------------------

struct arg_call
{
	template <typename F, typename... A>
	INLINE constexpr auto operator()(F&& f, A&&... a) const
	-> decltype(fwd <F>(f)(uref()(fwd <A>(a)...)))
		{ return fwd <F>(f)(uref()(fwd <A>(a)...)); }
};

//-----------------------------------------------------------------------------

struct tup_call
{
	template <
		typename F, typename T, typename... A,
		only_if <is_tuple <T>{}>
	= 0>
	INLINE constexpr auto operator()(F&& f, T&& t, A&&... a) const
	-> decltype(fwd <T>(t).call(fwd <F>(f), fwd <A>(a)...))
		{ return fwd <T>(t).call(fwd <F>(f), fwd <A>(a)...); }
};

//-----------------------------------------------------------------------------

class head_call
{
	using H = tup_head;
	using L = tup_tail;

public:
	template <
		typename F, typename T, typename... A,
		only_if <is_tuple <T>{}>
	= 0>
	INLINE constexpr auto operator()(F&& f, T&& t, A&&... a) const
	-> decltype(fwd <F>(f)(H()(fwd <T>(t)), L()(fwd <T>(t)), fwd <A>(a)...))
		{ return fwd <F>(f)(H()(fwd <T>(t)), L()(fwd <T>(t)), fwd <A>(a)...); }
};

//-----------------------------------------------------------------------------

struct pre_call
{
	template <
		typename F, typename T, typename... A,
		only_if <is_tuple <T>{}>
	= 0>
	INLINE constexpr ret <F(A...)>
	operator()(F&& f, T&& t, A&&... a) const
		{ return fwd <T>(t).call(fwd <F>(f)), fwd <F>(f)(fwd <A>(a)...); }
};

//-----------------------------------------------------------------------------

template <typename F> using arg_fun_of = bind_fun <arg_call, F>;
template <typename F> using tup_fun_of = bind_fun <tup_call, F>;
template <typename F> using head_fun_of = bind_fun <head_call, F>;

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

using details::tup;

using details::arg_call;
using details::tup_call;
using details::head_call;

using details::arg_fun_of;
using details::tup_fun_of;
using details::head_fun_of;

//-----------------------------------------------------------------------------

}  // namespace afun

//-----------------------------------------------------------------------------

static __attribute__ ((unused)) afun::tup  tup;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_TUPLE_FUN_MANIP_HPP
