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

#ifndef IVL_CORE_TUPLE_BASE_STORE_HPP
#define IVL_CORE_TUPLE_BASE_STORE_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace tuples {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename... E>
struct elem_store : E...
{
	template <typename A = int, only_if <_and <is_cons <E>...>{}, A> = 0>
	explicit INLINE constexpr elem_store() : E()... { }

	template <typename... A, only_if <sizeof...(A) == sizeof...(E)> = 0>
	explicit INLINE constexpr elem_store(A&&... a) : E(fwd <A>(a))... { }
};

template <typename E>
struct elem_store <E> : E
{
	template <typename A = int, only_if <is_cons <E>{}, A> = 0>
	explicit INLINE constexpr elem_store() : E() { }

	template <typename A>
	explicit INLINE constexpr elem_store(A&& a) : E(fwd <A>(a)) { }
};

template <>
struct elem_store <> { };

//-----------------------------------------------------------------------------

template <typename D, typename U = tup_data <D>, typename N = sz_rng_of_p <U> >
struct elems;

template <typename D, typename... U, size_t... N>
struct elems <D, pack <U...>, sizes <N...> > :
	elem_store <elem <N, U>...>
{
	using elem_store <elem <N, U>...>::elem_store;
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace tuples

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_TUPLE_BASE_STORE_HPP
