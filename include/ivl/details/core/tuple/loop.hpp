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

#ifndef IVL_DETAILS_CORE_TUPLE_LOOP_HPP
#define IVL_DETAILS_CORE_TUPLE_LOOP_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace tuples {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename F, typename A, typename I = sz_rng_of_p <A> >
class loop_store;

template <typename F, typename... A, size_t... I>
class loop_store <F, pack <A...>, sizes <I...> > : public base_tup <
	loop_tup <F, A...>, rep <tran_len <tup_types <A>...>{}, nat>
>
{
	using P = rep <tran_len <tup_types <A>...>{}, nat>;
	using B = base_tup <loop_tup <F, A...>, P>;

	using fun = elem_at <0, F, A...>;
	template <size_t J> using arg = elem_at <J + 1, F, A...>;

	friend base_type_of <B>;

//-----------------------------------------------------------------------------

	template <size_t J>
	INLINE rtel <J, P>
	_at() && { return fun::fwd()(at._<J>(arg <I>::fwd())...), nat(); }

	template <size_t J>
	INLINE ltel <J, P>
	_at() & { return fun::get()(at._<J>(arg <I>::get())...), nat(); }

	template <size_t J>
	INLINE constexpr cltel <J, P>
	_at() const& { return fun::get()(at._<J>(arg <I>::get())...), nat(); }

//-----------------------------------------------------------------------------

public:
	using B::B;
};

//-----------------------------------------------------------------------------

template <typename F>
class collection <data::loop <>, F>;

template <typename F, typename... A>
class collection <data::loop <>, F, A...> : public loop_store <F, pack <A...> >
{
	using B = loop_store <F, pack <A...> >;

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

#endif  // IVL_DETAILS_CORE_TUPLE_LOOP_HPP
