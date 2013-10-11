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

#ifndef IVL_DETAILS_CORE_TYPE_NAT_HPP
#define IVL_DETAILS_CORE_TYPE_NAT_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

namespace logic {

//-----------------------------------------------------------------------------

// not a type
using nat = id_t <>;

template <typename T> using is_nat = eq <nat, T>;

//-----------------------------------------------------------------------------

template <typename T, typename E, typename D = T>
using if_nat_t = _if_t <is_nat <T>{}, E, D>;

template <typename T, typename E, typename D = T>
using if_nat = type_of <if_nat_t <T, E, D> >;

//-----------------------------------------------------------------------------

template <bool C, typename T = int>
using enable_if_t = _if <C, id_t <T>, nat>;

template <bool C, typename T = int>
using enable_if = type_of <enable_if_t <C, T> >;

//-----------------------------------------------------------------------------

template <typename T> using check_t = enable_if_t <!is_nat <T>(), T>;
template <typename T> using check   = type_of <check_t <T> >;

//-----------------------------------------------------------------------------

}  // namespace logic

using namespace logic;

//-----------------------------------------------------------------------------

}  // namespace types

using types::enable_if;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_TYPE_NAT_HPP
