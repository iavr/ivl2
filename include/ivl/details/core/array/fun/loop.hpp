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

struct seq_more
{
	template <typename... T>
	INLINE constexpr bool operator()(T&&... t) const
		{ return get <seq_prim <T...>{}>()(fwd <T>(t)...); }
};

//-----------------------------------------------------------------------------

template <typename M = seq_more>
struct seq_loop : tup_loop
{
	template <typename F, typename... A, only_if <any_cont <A...>{}> = 0>
	INLINE F&& operator()(F&& f, A&&... a) const
		{ return operator()(fwd <F>(f), trav()(fwd <A>(a))...); }

	template <typename F, typename... T, only_if <can_loop <T...>{}> = 0>
	INLINE F&& operator()(F&& f, T&&... t) const
	{
		for (; M()(t...); thru{++t...})
			fwd <F>(f)(*t...);
		return fwd <F>(f);
	}
};

//-----------------------------------------------------------------------------

template <typename S, typename M = seq_more>
class seq_sep_loop : public tup_sep_loop <S>
{
	using B = tup_sep_loop <S>;

protected:
	using B::val;

public:
	using B::B;

	template <typename F, typename... A, only_if <any_cont <A...>{}> = 0>
	INLINE F&& operator()(F&& f, A&&... a) const
		{ return operator()(fwd <F>(f), trav()(fwd <A>(a))...); }

	template <typename F, typename... T, only_if <can_loop <T...>{}> = 0>
	INLINE F&& operator()(F&& f, T&&... t) const
	{
		if (!M()(t...)) return fwd <F>(f);
		fwd <F>(f)(*t...);
		for (thru{++t...}; M()(t...); thru{++t...})
			fwd <F>(f)(fwd <S>(val())), fwd <F>(f)(*t...);
		return fwd <F>(f);
	}
};

//-----------------------------------------------------------------------------

// TODO
using apply = seq_apply;

//-----------------------------------------------------------------------------

template <typename S>
struct sep_loop : seq_sep_loop <S>
{
	using tup_sep_loop <S>::operator();
	using seq_sep_loop <S>::operator();
	using seq_sep_loop <S>::seq_sep_loop;
};

//-----------------------------------------------------------------------------

struct loop : seq_loop <>
{
	using tup_loop::operator();
	using seq_loop <>::operator();

	// TODO: keys
	template <typename S>
	INLINE sep_loop <uref_opt <S> >
	operator[](S&& s) const { return sep_loop <uref_opt <S> >(fwd <S>(s)); }
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

using details::seq_apply;
using details::seq_loop;

using details::apply;
using details::loop;

//-----------------------------------------------------------------------------

}  // namespace afun

//-----------------------------------------------------------------------------

static __attribute__ ((unused)) afun::apply  apply;
static __attribute__ ((unused)) afun::loop   loop;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_FUN_LOOP_HPP
