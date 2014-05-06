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

#ifndef IVL_CORE_TYPE_CONST_CONST_HPP
#define IVL_CORE_TYPE_CONST_CONST_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

template <typename T>
struct value { using value_type = T; };

template <typename T>
using value_type_of = typename T::value_type;

//-----------------------------------------------------------------------------

namespace constants {

//-----------------------------------------------------------------------------

template <typename T, T... V>
struct non_type;

template <typename C, typename... A>
struct constant;

//-----------------------------------------------------------------------------

template <typename T, T V>
using c_integral = constant <tag::_int, non_type <T, V> >;

template <typename T, typename M, typename E>
using c_floating = constant <tag::_float, T, M, E>;

template <typename T, typename M, typename E>
using c_norm = constant <tag::norm, T, M, E>;

//-----------------------------------------------------------------------------

template <typename C, typename... A>
using c_cons = constant <tag::cons, C, A...>;

template <typename C, typename... A>
using c_cons_list = constant <tag::cons_list, C, A...>;

template <typename T, T... N>
using c_int_array = constant <tag::int_array, non_type <T, N...> >;

template <typename T, typename... A>
using c_array = constant <tag::array, T, A...>;

template <typename T, typename... A>
using c_array_list = constant <tag::array_list, T, A...>;

//-----------------------------------------------------------------------------

}  // namespace constants

//-----------------------------------------------------------------------------

using namespace constants;

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_TYPE_CONST_CONST_HPP
