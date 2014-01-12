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

template <typename... E>
struct elem_store : E...
{
	explicit INLINE constexpr elem_store(_true) : E()... { }

	template <typename... A>
	explicit INLINE constexpr elem_store(A&&... a) : E(fwd <A>(a))... { }
};

//-----------------------------------------------------------------------------

template <typename N, typename U> struct elem_map;

template <size_t... N, typename... U>
class elem_map <sizes <N...>, pack <U...> > :
	public elem_store <elem <N, U>...>
{
	using B = elem_store <elem <N, U>...>;

public:
	using B::B;
};

//-----------------------------------------------------------------------------

template <typename D>
class elems : public elem_map <sz_rng_of_p <under <D> >, under <D> >
{
	using U = under <D>;
	using B = elem_map <sz_rng_of_p <U>, U>;

public:
	using B::B;
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace tuples

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_TUPLE_STORE_HPP
