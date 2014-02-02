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

#ifndef IVL_DETAILS_CORE_LOOP_ARRAY_HPP
#define IVL_DETAILS_CORE_LOOP_ARRAY_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace afun {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

struct trav
{
	template <typename A, only_if <is_array <A>{}> = 0>
	INLINE auto operator()(A&& a) const
	-> decltype(fwd <A>(a).trav())
		{ return fwd <A>(a).trav(); }

	template <typename A, only_if <is_trav <A>{}> = 0>
	INLINE A&& operator()(A&& a) const { return fwd <A>(a); }

	template <typename A, only_if <!is_array <A>() && !is_trav <A>()> = 0>
	INLINE constexpr atom_trav <A>
	operator()(A&& a) const { return atom_trav <A>(fwd <A>(a)); }
};

//-----------------------------------------------------------------------------

struct seq_more
{
	template <typename... T>
	INLINE constexpr bool operator()(T&&... t) const
		{ return get <seq_prim <T...>{}>(fwd <T>(t)...); }
};

//-----------------------------------------------------------------------------

template <typename S, typename M = seq_more>
class seq_sep_loop : raw_tuple <S>
{
	using B = raw_tuple <S>;

protected:
	using B::val;

public:
	using B::B;

	template <typename F, typename... A, only_if <any_array <A...>{}> = 0>
	INLINE F&& operator()(F&& f, A&&... a) const
		{ return operator()(fwd <F>(f), trav()(fwd <A>(a))...); }

	template <typename F, typename... T, only_if <all_trav <T...>{}> = 0>
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

template <typename M = seq_more>
struct seq_loop
{
	template <typename F, typename... A, only_if <any_array <A...>{}> = 0>
	INLINE F&& operator()(F&& f, A&&... a) const
		{ return operator()(fwd <F>(f), trav()(fwd <A>(a))...); }

	template <typename F, typename... T, only_if <all_trav <T...>{}> = 0>
	INLINE F&& operator()(F&& f, T&&... t) const
	{
		for (; M()(t...); thru{++t...})
			fwd <F>(f)(*t...);
		return fwd <F>(f);
	}
};

//-----------------------------------------------------------------------------

}  // namespace details

using details::trav;

//-----------------------------------------------------------------------------

}  // namespace afun

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_LOOP_ARRAY_HPP
