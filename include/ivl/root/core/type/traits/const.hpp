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

#ifndef IVL_CORE_TYPE_TRAITS_CONST_HPP
#define IVL_CORE_TYPE_TRAITS_CONST_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

namespace traits {

//-----------------------------------------------------------------------------

template <typename T>
struct is_constant : _false { };

template <typename C, typename... A>
struct is_constant <constant <C, A...> > : _true { };

// extended elsewhere
template <typename T>
struct as_constant : is_constant <T> { };

//-----------------------------------------------------------------------------

namespace details {

template <typename T, bool = is_constant <T>()>
struct const_value_ : id_t <T> { };

template <typename T>
struct const_value_<T, true> : id_t <value_type_of <T> > { };

}  // namespace details

template <typename T> using const_value_t = details::const_value_<T>;
template <typename T> using const_value   = type_of <const_value_t <T> >;

//-----------------------------------------------------------------------------

namespace details {

template <
	template <typename...> class F, typename P,
	bool = all_p <as_constant, P>()
>
struct const_map_ : embed_t <F, P> { };

template <template <typename...> class F, typename P>
struct const_map_<F, P, false> : id_t <none> { };

}  //namespace details

template <template <typename...> class F, typename... T>
using const_map_t = details::const_map_<F, pack <T...> >;

template <template <typename...> class F, typename... T>
using const_map = type_of <const_map_t <F, T...> >;

//-----------------------------------------------------------------------------

}  // namespace traits

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_TYPE_TRAITS_CONST_HPP
