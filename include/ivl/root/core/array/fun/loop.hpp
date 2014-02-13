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

// no alias: often used
template <typename M = prim_more>
struct seq_apply_on : uref_of <apply_sequence_on <M>::template map> { };

//-----------------------------------------------------------------------------

template <template <typename> class C, typename I>
using raw_iter_sw = fun_switch <
	t_case <cont_travers, C <I> >,
	t_case <iter_travers, I>
>;

template <template <typename> class C, typename I>
using iter_sw = fun_switch <
	t_case <seq_travers, C <I> >,
	t_case <trav_travers, I>
>;

//-----------------------------------------------------------------------------

template <typename L>
struct cont_loop
{
	template <typename F, typename... A>
	INLINE F&& operator()(F&& f, A&&... a) const
		{ return L()(fwd <F>(f), trav()(fwd <A>(a))...); }
};

template <typename L>
struct cont_head_loop
{
	template <typename F, typename G, typename... A>
	INLINE void operator()(F&& f, G&& g, A&&... a) const
		{ L()(fwd <F>(f), fwd <G>(g), trav()(fwd <A>(a))...); }
};

//-----------------------------------------------------------------------------

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

template <typename M = prim_more>
using seq_loop_on = switch_fun_of <iter_sw <cont_loop, iter_loop_on <M> > >;

//-----------------------------------------------------------------------------

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

template <typename M = prim_more>
using seq_head_loop_on = switch_fun_of <cdr_switch <
	iter_sw <cont_head_loop, iter_head_loop_on <M> >
> >;

//-----------------------------------------------------------------------------

using seq_apply     = seq_apply_on <>;
using seq_loop      = seq_loop_on <>;
using seq_head_loop = seq_head_loop_on <>;

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

using details::seq_apply;
using details::seq_apply_on;
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
