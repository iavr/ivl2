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

template <bool E = false, bool I = false>
struct path_ : id_t <path_<E, I> >
{
	static constexpr bool edge    = E;
	static constexpr bool finite  = I;
};

using path = path_<>;

//-----------------------------------------------------------------------------

template <typename P> using path_edge = expr <P::edge>;
template <typename P> using path_fin  = expr <P::finite>;

//-----------------------------------------------------------------------------

template <typename P = path> struct edge_path_t { };
template <typename P = path> struct fin_path_t  { };

template <typename P = path> using edge_path = type_of <edge_path_t <P> >;
template <typename P = path> using fin_path  = type_of <fin_path_t <P> >;

template <bool E, bool I>
struct edge_path_t <path_<E, I> > : path_<true, I> { };

template <bool E, bool I>
struct fin_path_t <path_<E, I> > : path_<E, true> { };

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

using details::path;

using details::path_edge;
using details::path_fin;

using details::edge_path;
using details::fin_path;

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_TYPE_PATH_HPP
