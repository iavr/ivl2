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

#ifndef IVL_CORE_FUN_CORE_LOOP_HPP
#define IVL_CORE_FUN_CORE_LOOP_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace afun {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <
	template <typename...> class CS, typename S,
	template <typename...> class CT, typename T
>
using op_sw = fun_switch <t_case <CS, S>, t_case <CT, T> >;

template <typename S, typename T>
using apply_sw = op_sw <any_seq, S, any_tuple, T>;

template <typename S, typename T>
using loop_sw = op_sw <travers, S, any_tuple, T>;

template <typename S, typename T>
using raw_loop_sw = op_sw <raw_travers, S, any_tuple, T>;

//-----------------------------------------------------------------------------

using apply = switch_fun_of <apply_sw <seq_apply, tup_apply> >;

//-----------------------------------------------------------------------------

template <typename M = prim_term>
using head_loop_by = switch_fun_of <cdr_switch <
	loop_sw <seq_head_loop_by <M>, tup_head_loop>
> >;

//-----------------------------------------------------------------------------

struct sep_loop_
{
	template <typename S, typename F, typename A>
	INLINE void operator()(S&& s, F&& f, A&& a) const
	{
		head_loop_by <>()
			(fwd <F>(f), pre_fun()(fwd <F>(f), fwd <S>(s)), fwd <A>(a));
	}
};

using sep_loop = bind_of <sep_loop_>;

//-----------------------------------------------------------------------------

struct sep_loop_opt
{
	// TODO: keys
	template <typename S>
	INLINE auto operator[](S&& s) const
	-> decltype(sep_loop()(fwd <S>(s)))
		{ return sep_loop()(fwd <S>(s)); }
};

//-----------------------------------------------------------------------------

template <typename M = prim_term>
struct loop_by : sep_loop_opt,
	switch_fun_of <loop_sw <seq_loop_by <M>, tup_loop> > { };

template <typename M = prim_term>
struct raw_loop_by : sep_loop_opt,
	switch_fun_of <raw_loop_sw <seq_loop_by <M>, tup_loop> > { };

//-----------------------------------------------------------------------------

using loop      = loop_by <>;
using raw_loop  = raw_loop_by <>;
using head_loop = head_loop_by <>;

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

using details::apply;
using details::loop;
using details::loop_by;
using details::raw_loop;
using details::raw_loop_by;
using details::head_loop;
using details::head_loop_by;
using details::sep_loop;

//-----------------------------------------------------------------------------

}  // namespace afun

//-----------------------------------------------------------------------------

static __attribute__ ((unused)) afun::apply  apply;
static __attribute__ ((unused)) afun::loop   loop;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_FUN_CORE_LOOP_HPP
