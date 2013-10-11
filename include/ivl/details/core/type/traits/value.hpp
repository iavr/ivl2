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

#ifndef IVL_DETAILS_CORE_TYPE_TRAITS_MOVE_HPP
#define IVL_DETAILS_CORE_TYPE_TRAITS_MOVE_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

namespace traits {

//-----------------------------------------------------------------------------

template <typename T> inline add_rref <T> generate();

template <typename T>
struct convertible { inline operator add_rref <T>() &&; };

template <typename T>
inline convertible <T> convert() { return convertible <T>(); }

template <typename T> inline bool convert(T);

struct flexi { flexi(...); };

struct thru { template <typename... T> thru(T&&...) { } };

//-----------------------------------------------------------------------------

template <typename T>
inline remove_ref <T>&&
move(T&& a) { return static_cast <remove_ref <T>&&>(a); }

template <typename T>
inline constexpr T&&
fwd(remove_ref <T>& a) { return static_cast <T&&>(a); }

template <typename T, enable_if <!is_lref <T>()> = 0>
inline constexpr T&&
fwd(remove_ref <T>&& a) { return static_cast <T&&>(a); }

//-----------------------------------------------------------------------------

}  // namespace traits

//-----------------------------------------------------------------------------

}  // namespace types

using types::traits::move;
using types::traits::fwd;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_TYPE_TRAITS_MOVE_HPP
