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

template <bool I = false, bool E = false, bool F = false>
struct path_ : id_t <path_<I, E, F> >
{
	static constexpr bool iter    = I;
	static constexpr bool edge    = E;
	static constexpr bool finite  = F;
};

using path = path_<>;

//-----------------------------------------------------------------------------

template <typename P> using path_iter   = expr <P::iter>;
template <typename P> using path_edge   = expr <P::edge>;
template <typename P> using path_finite = expr <P::finite>;

//-----------------------------------------------------------------------------

template <typename P = path> struct iter_path_t { };
template <typename P = path> struct edge_path_t { };
template <typename P = path> struct finite_path_t { };

template <typename P = path> using iter_path   = type_of <iter_path_t <P> >;
template <typename P = path> using edge_path   = type_of <edge_path_t <P> >;
template <typename P = path> using finite_path = type_of <finite_path_t <P> >;

template <bool I, bool E, bool F>
struct iter_path_t <path_<I, E, F> > : path_<true, E, F> { };

template <bool I, bool E, bool F>
struct edge_path_t <path_<I, E, F> > : path_<I, true, F> { };

template <bool I, bool E, bool F>
struct finite_path_t <path_<I, E, F> > : path_<I, E, true> { };

using iter = iter_path <>;

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

using details::path;
using details::iter;

using details::path_iter;
using details::path_edge;
using details::path_finite;

using details::iter_path;
using details::edge_path;
using details::finite_path;

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_TYPE_PATH_HPP
