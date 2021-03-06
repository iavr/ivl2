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

#ifndef IVL_CORE_TYPE_TRAITS_ARRAY_HPP
#define IVL_CORE_TYPE_TRAITS_ARRAY_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

namespace traits {

//-----------------------------------------------------------------------------

template <typename T>           struct is_arr        : _false { };
template <typename T>           struct is_arr <T[]>  : _true  { };
template <typename T, size_t N> struct is_arr <T[N]> : _true  { };

//-----------------------------------------------------------------------------

template <typename T> struct rank_t       : size <0> { };
template <typename T> struct rank_t <T[]> : size <rank_t <T>() + 1> { };

template <typename T, size_t N>
struct rank_t <T[N]> : size <rank_t <T>() + 1> { };

template <typename T> using rank = type_of <rank_t <T> >;

//-----------------------------------------------------------------------------

template <typename T, size_t I = 0>
struct extent_t : size <0> { };

template <typename T>
struct extent_t <T[], 0> : size <0> { };

template <typename T, size_t I>
struct extent_t <T[], I> : size <extent_t <T, I - 1>{}> { };

template <typename T, size_t N>
struct extent_t <T[N], 0> : size <N> { };

template <typename T, size_t N, size_t I>
struct extent_t <T[N], I> : size <extent_t <T, I - 1>{}> { };

template <typename T> using extent = type_of <extent_t <T> >;

//-----------------------------------------------------------------------------

template <typename T>           struct remove_ext_t        : id_t <T> { };
template <typename T>           struct remove_ext_t <T[]>  : id_t <T> { };
template <typename T, size_t N> struct remove_ext_t <T[N]> : id_t <T> { };

template <typename T>
struct remove_all_ext_t : id_t <T> { };

template <typename T>
struct remove_all_ext_t <T[]> : remove_all_ext_t <T> { };

template <typename T, size_t N>
struct remove_all_ext_t <T[N]> : remove_all_ext_t <T> { };

template <typename T> using remove_ext = type_of <remove_ext_t <T> >;

template <typename T>
using remove_all_ext = type_of <remove_all_ext_t <T> >;

//-----------------------------------------------------------------------------

}  // namespace traits

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_TYPE_TRAITS_ARRAY_HPP
