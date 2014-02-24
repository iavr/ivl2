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

template <int R = 0, int B = 0, int F = 0>
struct path_traits
{
	static constexpr int flipped       = R;
	static constexpr int bidirectional = B;
	static constexpr int finite        = F;
};

using path = path_traits <>;

//-----------------------------------------------------------------------------

template <typename P> using is_flip = expr <P::flipped>;
template <typename P> using is_bi   = expr <P::bidirectional>;
template <typename P> using is_fin  = expr <P::finite>;

//-----------------------------------------------------------------------------

template <int S, typename P> struct set_flip_t { };
template <int S, typename P> struct set_bi_t   { };
template <int S, typename P> struct set_fin_t  { };

template <int SET, int R, int B, int F>
struct set_flip_t <SET, path_traits <R, B, F> > :
	id_t <path_traits <SET, B, F> > { };

template <int SET, int R, int B, int F>
struct set_bi_t <SET, path_traits <R, B, F> > :
	id_t <path_traits <R, SET, F> > { };

template <int SET, int R, int B, int F>
struct set_fin_t <SET, path_traits <R, B, F> > :
	id_t <path_traits <R, B, SET> > { };

//-----------------------------------------------------------------------------

template <int S, typename P>
using set_flip = type_of <details::set_flip_t <S, P> >;

template <int S, typename P>
using set_bi = type_of <details::set_bi_t <S, P> >;

template <int S, typename P>
using set_fin = type_of <details::set_fin_t <S, P> >;

//-----------------------------------------------------------------------------

template <typename P> using flip_on = set_flip <1, P>;
template <typename P> using bi_on  = set_bi  <1, P>;
template <typename P> using fin_on = set_fin <1, P>;

template <typename P> using flip_off = set_flip <0, P>;
template <typename P> using bi_off  = set_bi  <0, P>;
template <typename P> using fin_off = set_fin <0, P>;

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_TYPE_PATH_HPP
