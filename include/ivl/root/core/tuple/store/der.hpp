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

#ifndef IVL_CORE_TUPLE_STORE_DER_HPP
#define IVL_CORE_TUPLE_STORE_DER_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace tuples {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename D, typename... E>
struct der_tuple : raw_tuple <E...>
{
	using raw_tuple <E...>::raw_tuple;
};

//-----------------------------------------------------------------------------

template <typename D, typename E>
class der_tuple <D, E> : public raw_tuple <E>
{
	using B = raw_tuple <E>;

protected:
	template <typename A>
	static INLINE constexpr bool is_elem(id_t <A>)  { return true; }
	static INLINE constexpr bool is_elem(id_t <D>)  { return false; }
	static INLINE constexpr bool is_elem(id_t <D&>) { return false; }

public:
	// TODO: the following is slower in GCC, hence the need for elem():
	// template <typename A, only_if <!eq <D, remove_ref <A> >()> = 0>

	template <typename A, only_if <is_elem(id_t <A>())> = 0>
	explicit INLINE constexpr der_tuple(A&& a) : B(fwd <A>(a)) { }
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace tuples

using tuples::details::der_tuple;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_TUPLE_STORE_DER_HPP
