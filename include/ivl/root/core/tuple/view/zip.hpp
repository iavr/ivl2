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

#ifndef IVL_CORE_TUPLE_VIEW_ZIP_HPP
#define IVL_CORE_TUPLE_VIEW_ZIP_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace tuples {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename P, typename I = sz_rng_of_p <P> >
struct zip_impl;

template <typename... U, size_t... I>
class zip_impl <pack <U...>, sizes <I...> > :
	public tup_base <zip_tup <U...>, tup_tran <tup_types <U>...> >
{
	using P = tup_tran <tup_types <U>...>;
	using B = tup_base <zip_tup <U...>, P>;

	template <size_t J> using under = elem_at <J, U...>;

	friend base_type_of <B>;

//-----------------------------------------------------------------------------

	template <size_t J>
	INLINE r_pk <J, P>
	call_at() && { return r_pk <J, P>(_at._<J>(under <I>::fwd())...); }

	template <size_t J>
	INLINE l_pk <J, P>
	call_at() & { return r_pk <J, P>(_at._<J>(under <I>::get())...); }

	template <size_t J>
	INLINE constexpr c_pk <J, P>
	call_at() const& { return r_pk <J, P>(_at._<J>(under <I>::get())...); }

//-----------------------------------------------------------------------------

public:
	using B::B;
};

//-----------------------------------------------------------------------------

template <typename... U>
class collection <data::zip <>, U...> :
	public zip_impl <pack <U...> >
{
	using B = zip_impl <pack <U...> >;

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

#endif  // IVL_CORE_TUPLE_VIEW_ZIP_HPP
