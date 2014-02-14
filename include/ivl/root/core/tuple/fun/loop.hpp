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
struct tup_apply : uref_of <apply_tuple> { };

//-----------------------------------------------------------------------------

struct off_fix_call
{
	template <size_t I, typename F, typename... A>
	INLINE constexpr auto _(F&& f, A&&... a) const
	-> decltype(fwd <F>(f)(fwd <A>(a)...))
		{ return fwd <F>(f)(fwd <A>(a)...); }
};

template <template <size_t...> class M>
struct off_map_call
{
	template <size_t I, typename F, typename... A>
	INLINE constexpr auto _(F&& f, A&&... a) const
	-> decltype(fwd <F>(f)(M <I>{}, fwd <A>(a)...))
		{ return fwd <F>(f)(M <I>{}, fwd <A>(a)...); }
};

//-----------------------------------------------------------------------------

template <typename C>
class tup_loop_of
{
	template <size_t I, typename F, typename... A>
	INLINE void each(F&& f, A&&... a) const
		{ C().template _<I>(fwd <F>(f), at()._<I>(fwd <A>(a))...); }

	template <size_t... I, typename F, typename... A>
	INLINE void loop(sizes <I...>, F&& f, A&&... a) const
		{ thru{(each <I>(fwd <F>(f), fwd <A>(a)...), 0)...}; }

public:
	template <typename F, typename... A, typename R = tup_tran_rng <A...> >
	INLINE F&& operator()(F&& f, A&&... a) const
	{
		return loop(R(), fwd <F>(f), tup_atom_of <A>(fwd <A>(a))...),
			fwd <F>(f);
	}
};

using tup_loop = tup_loop_of <off_fix_call>;

template <template <size_t...> class M = size>
using tup_scan_of = tup_loop_of <off_map_call <M> >;

using tup_scan      = tup_scan_of <>;
using tup_tail_scan = tup_scan_of <sz_inc>;

//-----------------------------------------------------------------------------

struct tup_head_loop_fun
{
	template <typename F, typename G, typename... T>
	INLINE void operator()(F&& f, G&& g, T&&... t) const
	{
		fwd <F>(f)(tup_head()(fwd <T>(t))...);
		tup_loop()(fwd <G>(g), tup_tail()(fwd <T>(t))...);
	}
};

template <typename F, typename G, typename... T>
using tup_head_loop_sw =
	_if <_or <fix_empty <T>...>{}, nop_fun, tup_head_loop_fun>;

using tup_head_loop = switch_fun <tup_head_loop_sw>;

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

using details::tup_apply;
using details::tup_loop;
using details::tup_head_loop;

//-----------------------------------------------------------------------------

}  // namespace afun

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_TUPLE_FUN_LOOP_HPP
