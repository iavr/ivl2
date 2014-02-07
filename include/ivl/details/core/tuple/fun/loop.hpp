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

#ifndef IVL_CORE_TUPLE_FUN_LOOP_HPP
#define IVL_CORE_TUPLE_FUN_LOOP_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace afun {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

// no alias: often used
struct tup_apply : uref_of <apply_tuple, any_tuple> { };
struct tup_loop_ : rref_of <loop_tuple,  any_tuple> { };
struct tup_scan_ : rref_of <scan_tuple,  any_tuple> { };

template <typename L>
struct tup_loop_of
{
	template <typename F, typename... A, only_if <any_tuple <A...>{}> = 0>
	INLINE void operator()(F&& f, A&&... a) const
		{ L()(fwd <F>(f), fwd <A>(a)...).loop(); }
};

using tup_loop = tup_loop_of <tup_loop_>;
using tup_scan = tup_loop_of <tup_scan_>;

//-----------------------------------------------------------------------------

template <typename S>
class tup_sep_loop : raw_tuple <S>
{
	using B = raw_tuple <S>;

protected:
	using B::val;

public:
	using B::B;

	template <typename F, typename T, only_if <tup_empty <T>{}> = 0>
	INLINE void operator()(F&& f, T&& t) const { };

	template <typename F, typename T, only_if <tup_non_empty<T>{}> = 0>
	INLINE void operator()(F&& f, T&& t) const
	{
		fwd <F>(f)(tup_head()(fwd <T>(t)));
		S&& s = fwd <S>(val());
		tup_loop()(pre_fun()(fwd <F>(f), fwd <S>(s)), tup_tail()(fwd <T>(t)));
	}
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

using details::tup_apply;
using details::tup_loop;

//-----------------------------------------------------------------------------

}  // namespace afun

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_TUPLE_FUN_LOOP_HPP
