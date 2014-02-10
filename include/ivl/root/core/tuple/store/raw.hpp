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

#ifndef IVL_CORE_TUPLE_STORE_RAW_HPP
#define IVL_CORE_TUPLE_STORE_RAW_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace tuples {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename... E>
class collection <data::raw <>, E...> : public access <raw_tuple <E...>, E...>
{
	using P = pack <E...>;
	using B = access <raw_tuple <E...>, E...>;

	template <size_t J> using under = elem_at <J, E...>;

//-----------------------------------------------------------------------------

public:
	using type = P;
	static constexpr size_t length = P::length;

	using B::B;

//-----------------------------------------------------------------------------

	template <size_t J>
	INLINE r_pk <J, P> at() && { return under <J>::fwd(); }

	template <size_t J>
	INLINE l_pk <J, P> at() & { return under <J>::get(); }

	template <size_t J>
	INLINE constexpr c_pk <J, P> at() const& { return under <J>::get(); }

};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace tuples

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_TUPLE_STORE_RAW_HPP
