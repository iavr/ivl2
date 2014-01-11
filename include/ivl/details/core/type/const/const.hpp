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

#ifndef IVL_DETAILS_CORE_TYPE_CONST_CONST_HPP
#define IVL_DETAILS_CORE_TYPE_CONST_CONST_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

namespace constants {

//-----------------------------------------------------------------------------

template <typename T>
struct value { using value_type = T; };

template <typename T>
using value_type_of = typename T::value_type;

//-----------------------------------------------------------------------------

template <typename T, typename D>
struct constant : value <T>, id_t <D>, derived <D>
{
	INLINE constexpr T operator()() const { return this->der(); }
};

template <typename D>
struct constant <void, D> : value <void>, id_t <D>, derived <D>
{
	INLINE void operator()() const { this->der()(); }
};

template <typename D>
struct constant <const void, D> : constant <void, D> { };

template <typename D>
struct constant <const volatile void, D> : constant <void, D> { };

//-----------------------------------------------------------------------------

template <typename T, typename F>
struct fun_constant : constant <T, F> { };

template <typename S, typename T, typename D>
INLINE S& operator<<(S& s, const constant <T, D>& c) { return s << c(); }

//-----------------------------------------------------------------------------

}  // namespace constants

using namespace constants;

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_TYPE_CONST_CONST_HPP
