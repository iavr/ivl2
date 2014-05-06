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

#ifndef IVL_CORE_TYPE_CONST_CLASS_HPP
#define IVL_CORE_TYPE_CONST_CLASS_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

namespace constants {

//-----------------------------------------------------------------------------

template <typename C, typename... A>
struct constant <tag::cons, C, A...> : c_cons <C(A...)> { };

template <typename C, typename... A>
struct constant <tag::cons, C(A...)> :
	details::const_base <raw_type <C>, c_cons <C(A...)> >
{
	INLINE constexpr
	operator raw_type <C>() const { return raw_type <C>(A()()...); }
};

//-----------------------------------------------------------------------------

template <typename C, typename... A>
struct constant <tag::cons_list, C, A...> : c_cons_list <C(A...)> { };

template <typename C, typename... A>
struct constant <tag::cons_list, C(A...)> :
	details::const_base <raw_type <C>, c_cons_list <C(A...)> >
{
	INLINE constexpr
	operator raw_type <C>() const { return raw_type <C>{A()()...}; }
};

//-----------------------------------------------------------------------------

using c_null = c_cons_list <nullptr_t>;

//-----------------------------------------------------------------------------

}  // namespace constants

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_TYPE_CONST_CLASS_HPP
