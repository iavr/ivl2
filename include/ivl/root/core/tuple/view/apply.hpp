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

#ifndef IVL_CORE_TUPLE_VIEW_APPLY_HPP
#define IVL_CORE_TUPLE_VIEW_APPLY_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace tuples {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename F>
class apply_type
{
	template <typename... A>
	struct map_t : id_t <F(pack <A...>)> { };

	template <typename... A>
	struct map_t <pack <A...> > : map_t <A...> { };

public:
	template <typename... A>
	using map = type_of <map_t <A...> >;
};

template <typename F, typename... A>
using apply_types =
	map <apply_type <F>::template map, tup_tran <tup_types <A>...> >;

//-----------------------------------------------------------------------------

template <typename F, typename A, typename I = sz_rng_of_p <A> >
class apply_impl;

template <typename F, typename... A, size_t... I>
class apply_impl <F, pack <A...>, sizes <I...> > :
	public tup_base <apply_tup <F, A...>, apply_types <F, A...> >
{
	using P = apply_types <F, A...>;
	using B = tup_base <apply_tup <F, A...>, P>;

	using fun = elem <0, F>;
	template <size_t J> using arg = elem_at <J + 1, F, A...>;

	friend base_type_of <B>;

//-----------------------------------------------------------------------------

	template <size_t J>
	INLINE r_pick_p <J, P>
	call_at() && { return fun::fwd()(_at._<J>(arg <I>::fwd())...); }

	template <size_t J>
	INLINE l_pick_p <J, P>
	call_at() & { return fun::get()(_at._<J>(arg <I>::get())...); }

	template <size_t J>
	INLINE constexpr c_pick_p <J, P>
	call_at() const& { return fun::get()(_at._<J>(arg <I>::get())...); }

//-----------------------------------------------------------------------------

public:
	using B::B;
};

//-----------------------------------------------------------------------------

template <typename F>
class collection <data::apply <>, F>;

template <typename F, typename... A>
class collection <data::apply <>, F, A...> :
	public apply_impl <F, pack <A...> >
{
	using B = apply_impl <F, pack <A...> >;

public:
	using B::B;
	using B::base_type::operator=;
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace tuples

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_TUPLE_VIEW_APPLY_HPP
