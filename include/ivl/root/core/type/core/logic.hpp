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

#ifndef IVL_CORE_TYPE_CORE_LOGIC_HPP
#define IVL_CORE_TYPE_CORE_LOGIC_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

namespace logic {

//-----------------------------------------------------------------------------

template <bool B> using boolean = c_boolean <B>;
template <bool B> using expr    = boolean <B>;

using _false = c_false;
using _true  = c_true;

static __attribute__ ((unused)) _false no;
static __attribute__ ((unused)) _true  yes;

//-----------------------------------------------------------------------------

template <bool B> using _not = expr <!B>;

//-----------------------------------------------------------------------------

// TODO: alias not working for report()'s static_assert in gcc
template <typename... T> struct always : _true { };
template <typename... T> struct never  : _false { };

//-----------------------------------------------------------------------------

template <typename A, typename B>
struct eq : _false { };

template <typename A>
struct eq <A, A> : _true { };

template <typename A, typename B> using neq = expr <!eq <A, B>()>;

//-----------------------------------------------------------------------------

template <bool C, typename T, typename E>
struct _if_t : id_t <E> { };

template <typename T, typename E>
struct _if_t <true, T, E> : id_t <T> { };

template <bool C, typename T, typename E>
using _if = type_of <_if_t <C, T, E> >;

//-----------------------------------------------------------------------------

template <bool C, typename T, typename E>
using unless_t = _if_t <!C, T, E>;

template <bool C, typename T, typename E>
using unless = type_of <unless_t <C, T, E> >;

//-----------------------------------------------------------------------------

template <template <typename...> class C, typename T, typename E>
struct map_if
{
	template <typename... A>
	using map = _if <subs <C, A...>{}, T, E>;
};

//-----------------------------------------------------------------------------

}  // namespace logic

using namespace logic;

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_TYPE_CORE_LOGIC_HPP
