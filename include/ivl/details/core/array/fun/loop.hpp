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

#ifndef IVL_CORE_ARRAY_FUN_LOOP_HPP
#define IVL_CORE_ARRAY_FUN_LOOP_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace afun {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

// TODO
struct seq_apply : tup_apply { };

//-----------------------------------------------------------------------------

struct trav_more
{
	template <typename... T>
	INLINE constexpr bool operator()(T&&... t) const
		{ return get <trav_prim <T...>{}>()(fwd <T>(t)...); }
};

//-----------------------------------------------------------------------------

template <typename L>
struct cont_loop
{
	template <typename F, typename... A>
	INLINE F&& operator()(F&& f, A&&... a) const
		{ return L()(fwd <F>(f), trav()(fwd <A>(a))...); }
};

template <typename M>
struct iter_loop_on
{
	template <typename F, typename... T>
	INLINE F&& operator()(F&& f, T&&... t) const
	{
		for (; M()(t...); thru{++t...})
			fwd <F>(f)(*t...);
		return fwd <F>(f);
	}
};

//-----------------------------------------------------------------------------

template <typename M, typename L = iter_loop_on <M> >
struct seq_loop_for
{
	template <typename F, typename... A>
	using map = cond <
		any_cont <A...>, cont_loop <L>,
		can_iter <A...>, L
	>;
};

template <typename M = trav_more>
using seq_loop_on = choose_fun <seq_loop_for <M>::template map>;

//-----------------------------------------------------------------------------

template <typename L>
struct cont_head_loop
{
	template <typename F, typename G, typename... A>
	INLINE void operator()(F&& f, G&& g, A&&... a) const
		{ L()(fwd <F>(f), fwd <G>(g), trav()(fwd <A>(a))...); }
};

template <typename M>
struct iter_head_loop_on
{
	template <typename F, typename G, typename... T>
	INLINE void operator()(F&& f, G&& g, T&&... t) const
	{
		if (M()(t...))
			fwd <F>(f)(*t...),
			seq_loop_on <M>()(fwd <G>(g), ++t...);
	}
};

//-----------------------------------------------------------------------------

template <typename M, typename L = iter_head_loop_on <M> >
struct seq_head_loop_for
{
	template <typename F, typename... A>
	using map = cond <
		any_cont <A...>, cont_head_loop <L>,
		can_iter <A...>, L
	>;
};

template <typename M = trav_more>
using seq_head_loop_on = choose_fun <seq_head_loop_for <M>::template map>;

//-----------------------------------------------------------------------------

// template <typename M = trav_more>
// struct seq_head_loop_on
// {
// 	template <typename F, typename G, typename... A, only_if <any_cont <A...>{}> = 0>
// 	INLINE void operator()(F&& f, G&& g, A&&... a) const
// 		{ operator()(fwd <F>(f), fwd <G>(g), trav()(fwd <A>(a))...); }
//
// 	template <typename F, typename G, typename... T, only_if <can_iter <T...>{}> = 0>
// 	INLINE void operator()(F&& f, G&& g, T&&... t) const
// 	{
// 		if (M()(t...))
// 			fwd <F>(f)(*t...),
// 			seq_loop_on <M>()(fwd <G>(g), ++t...);
// 	}
// };

//-----------------------------------------------------------------------------

using seq_loop      = seq_loop_on <>;
using seq_head_loop = seq_head_loop_on <>;

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

using details::seq_apply;
using details::seq_loop;
using details::seq_loop_on;
using details::seq_head_loop;
using details::seq_head_loop_on;

//-----------------------------------------------------------------------------

}  // namespace afun

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_FUN_LOOP_HPP
