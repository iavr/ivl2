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

#ifndef IVL_CORE_ARRAY_TYPE_PATH_HPP
#define IVL_CORE_ARRAY_TYPE_PATH_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace arrays {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <
	typename C = tag::trav,
	bool F = false, bool E = false, bool I = false
>
struct path_ : id_t <path_<C, F, E, I> >
{
	using path = C;
	static constexpr bool flipped = F;
	static constexpr bool edge    = E;
	static constexpr bool finite  = I;
};

using path = path_<>;

template <typename P> using path_of = typename P::path;

//-----------------------------------------------------------------------------

template <typename P> using path_flip = expr <P::flipped>;
template <typename P> using path_edge = expr <P::edge>;
template <typename P> using path_fin  = expr <P::finite>;

//-----------------------------------------------------------------------------

template <typename P = path> struct set_tail_t { };
template <typename P = path> struct set_flip_t { };
template <typename P = path> struct set_edge_t { };
template <typename P = path> struct set_fin_t  { };

template <typename P = path> using set_tail = type_of <set_tail_t <P> >;
template <typename P = path> using set_flip = type_of <set_flip_t <P> >;
template <typename P = path> using set_edge = type_of <set_edge_t <P> >;
template <typename P = path> using set_fin  = type_of <set_fin_t <P> >;

template <typename C, bool F, bool E, bool I>
struct set_tail_t <path_<C, F, E, I> > : path_<tag::tail_<C>, F, E, I> { };

template <typename C, bool F, bool E, bool I>
struct set_flip_t <path_<C, F, E, I> > : path_<tag::flip_<C>, !F, E, I> { };

template <typename C, bool F, bool E, bool I>
struct set_edge_t <path_<C, F, E, I> > : path_<tag::edge_<C>, F, true, I> { };

template <typename C, bool F, bool E, bool I>
struct set_fin_t <path_<C, F, E, I> > : path_<C, F, E, true> { };

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

using details::path;
using details::path_of;

using details::path_flip;
using details::path_edge;
using details::path_fin;

using details::set_tail;
using details::set_flip;
using details::set_edge;
using details::set_fin;

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_TYPE_PATH_HPP
