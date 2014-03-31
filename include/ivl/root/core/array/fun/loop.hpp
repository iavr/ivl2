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

// no alias: entry point
template <typename M = prim_term>
struct seq_apply_by : uref_map <apply_sequence_by <M> > { };

//-----------------------------------------------------------------------------

struct iter_eval
{
	template <typename V>
	INLINE void operator()(V&& v) const { for (; v; ++v) *v; }
};

template <typename M>
struct iter_loop_by
{
	template <typename F, typename... V>
	INLINE F&& operator()(F&& f, V&&... v) const
	{
		for (; M()(v...); thru{++v...})
			fwd <F>(f)(*v...);
		return fwd <F>(f);
	}
};

//-----------------------------------------------------------------------------

struct cont_eval
{
	template <typename A>
	INLINE void operator()(A&& a) const
		{ return iter_eval()(trav()(fwd <A>(a))); }
};

template <typename L, typename T>
struct cont_loop
{
	template <typename F, typename... A>
	INLINE F&& operator()(F&& f, A&&... a) const
		{ return L()(fwd <F>(f), T()(fwd <A>(a))...); }
};

template <typename L>
struct cont_head_loop
{
	template <typename F, typename G, typename... A>
	INLINE void operator()(F&& f, G&& g, A&&... a) const
		{ L()(fwd <F>(f), fwd <G>(g), trav()(fwd <A>(a))...); }
};

//-----------------------------------------------------------------------------

using seq_eval_sw = t_switch <
	t_case <seq_travers, cont_eval>,
	t_case <trav_travers, iter_eval>
>;

template <template <typename...> class C, typename L, typename... T>
using iter_sw = fun_switch <
	t_case <seq_travers, C <L, T...> >,
	t_case <trav_travers, L>
>;

template <template <typename...> class C, typename L>
using raw_iter_sw = fun_switch <
	t_case <cont_travers, C <L, raw_trav> >,
	t_case <iter_travers, L>
>;

//-----------------------------------------------------------------------------

using seq_eval = switch_fun_of <seq_eval_sw>;

template <typename M = prim_term>
using seq_loop_by = switch_fun_of <
	iter_sw <cont_loop, iter_loop_by <M>, trav>
>;

template <typename M = prim_term>
using seq_raw_loop_by = switch_fun_of <
	raw_iter_sw <cont_loop, iter_loop_by <M> >
>;

//-----------------------------------------------------------------------------

template <typename M>
struct iter_head_loop_by
{
	template <typename F, typename G, typename... V>
	INLINE void operator()(F&& f, G&& g, V&&... v) const
	{
		if (M()(v...))
			fwd <F>(f)(*v...),
			seq_loop_by <M>()(fwd <G>(g), ++v...);
	}
};

template <typename M = prim_term>
using seq_head_loop_by = switch_fun_of <cdr_switch <
	iter_sw <cont_head_loop, iter_head_loop_by <M> >
> >;

//-----------------------------------------------------------------------------

using seq_apply     = seq_apply_by <>;
using seq_loop      = seq_loop_by <>;
using seq_raw_loop  = seq_raw_loop_by <>;
using seq_head_loop = seq_head_loop_by <>;

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

using details::seq_apply;
using details::seq_apply_by;
using details::seq_eval;
using details::seq_loop;
using details::seq_loop_by;
using details::seq_raw_loop;
using details::seq_raw_loop_by;
using details::seq_head_loop;
using details::seq_head_loop_by;

//-----------------------------------------------------------------------------

}  // namespace afun

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_FUN_LOOP_HPP
