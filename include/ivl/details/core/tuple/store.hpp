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

#ifndef IVL_DETAILS_CORE_TUPLE_STORE_HPP
#define IVL_DETAILS_CORE_TUPLE_STORE_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace tuples {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename P> struct elem_store;

template <typename... E>
struct elem_store <pack <E...> > : E...
{
	explicit INLINE constexpr elem_store(_true) : E()... { }

	template <typename... A>
	explicit INLINE constexpr elem_store(A&&... a) : E(fwd <A>(a))... { }
};

//-----------------------------------------------------------------------------

template <typename U, typename N = sz_rng_of_p <U> > struct elem_types_t;
template <typename U, typename N = sz_rng_of_p <U> >
using elem_types = type_of <elem_types_t <U, N> >;

template <typename... U, size_t... N>
struct elem_types_t <pack <U...>, sizes <N...> > : pack <elem <N, U>...> { };

//-----------------------------------------------------------------------------

template <typename D>
struct elems : elem_store <elem_types <under <D> > >
{
	using elem_store <elem_types <under <D> > >::elem_store;
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace tuples

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_TUPLE_STORE_HPP
