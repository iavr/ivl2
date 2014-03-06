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

template <int R = 0, int E = 0, int F = 0>
struct path_ : id_t <path_<R, E, F> >
{
	static constexpr int flipped = R;
	static constexpr int edge    = E;
	static constexpr int finite  = F;
};

using path = path_<>;

//-----------------------------------------------------------------------------

template <typename P> using path_flip = expr <P::flipped>;
template <typename P> using path_edge = expr <P::edge>;
template <typename P> using path_fin  = expr <P::finite>;

//-----------------------------------------------------------------------------

template <int S, typename P> struct set_flip_t { };
template <int S, typename P> struct set_edge_t { };
template <int S, typename P> struct set_fin_t  { };

template <int S, typename P> using set_flip = type_of <set_flip_t <S, P> >;
template <int S, typename P> using set_edge = type_of <set_edge_t <S, P> >;
template <int S, typename P> using set_fin  = type_of <set_fin_t <S, P> >;

template <int SET, int R, int E, int F>
struct set_flip_t <SET, path_<R, E, F> > : path_<SET, E, F> { };

template <int SET, int R, int E, int F>
struct set_edge_t <SET, path_<R, E, F> > : path_<R, SET, F> { };

template <int SET, int R, int E, int F>
struct set_fin_t <SET, path_<R, E, F> > : path_<R, E, SET> { };

//-----------------------------------------------------------------------------

template <typename P> using flip_on = set_flip <1, P>;
template <typename P> using edge_on = set_edge <1, P>;
template <typename P> using fin_on  = set_fin <1, P>;

template <typename P> using flip_off = set_flip <0, P>;
template <typename P> using edge_off = set_edge <0, P>;
template <typename P> using fin_off  = set_fin <0, P>;

//-----------------------------------------------------------------------------

template <typename P> struct not_flip_t { };
template <typename P> struct not_edge_t { };
template <typename P> struct not_fin_t  { };

template <typename P> using not_flip = type_of <not_flip_t <P> >;
template <typename P> using not_edge = type_of <not_edge_t <P> >;
template <typename P> using not_fin  = type_of <not_fin_t <P> >;

template <int R, int E, int F>
struct not_flip_t <path_<R, E, F> > : path_<!R, E, F> { };

template <int R, int E, int F>
struct not_edge_t <path_<R, E, F> > : path_<R, !E, F> { };

template <int R, int E, int F>
struct not_fin_t <path_<R, E, F> > : path_<R, E, !F> { };

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

using details::path;

using details::path_flip;
using details::path_edge;
using details::path_fin;

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_TYPE_PATH_HPP
