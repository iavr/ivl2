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

#ifndef IVL_CORE_TYPE_CORE_COND_HPP
#define IVL_CORE_TYPE_CORE_COND_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

namespace logic {

//-----------------------------------------------------------------------------

template <typename... T> struct cond_t;
template <typename... T> using  cond = type_of <cond_t <T...> >;

template <typename C, typename T, typename... E>
struct cond_t <C, T, E...> : _if <C{}, id_t <T>, cond_t <E...> > { };

template <typename E>
struct cond_t <E> : id_t <E> { };

//-----------------------------------------------------------------------------

template <bool C, typename T>
struct _case { };

template <typename T>
using _else = _case <true, T>;

template <typename... C> struct _switch_t;
template <typename... C> using  _switch = type_of <_switch_t <C...> >;

template <bool C, typename T, typename... E>
struct _switch_t <_case <C, T>, E...> :
	_if <C, id_t <T>, _switch_t <E...> > { };

template <bool C, typename T>
struct _switch_t <_case <C, T> > : _if <C, id_t <T>, nat> { };

template <typename E>
struct _switch_t <E> : id_t <E> { };

//-----------------------------------------------------------------------------

template <template <typename...> class C, typename T>
struct t_case { };

template <typename T>
using t_else = t_case <always, T>;

namespace details {

template <typename... A>
struct t_switch_
{
	template <typename... C> struct map_t;
	template <typename... C> using map = type_of <map_t <C...> >;

	template <template <typename...> class... C, typename... T>
	struct map_t <t_case <C, T>...> :
		_switch_t <_case <subs <C, A...>{}, T>...> { };
};

}  // namespace details

template <typename... C>
struct t_switch
{
	template <typename... A>
	using map = typename details::t_switch_<A...>::template map <C...>;
};

//-----------------------------------------------------------------------------

template <typename M>
struct cdr_switch
{
	template <typename A, typename... D>
	using map = subs <M::template map, D...>;
};

template <typename... C>
using fun_switch = cdr_switch <t_switch <C...> >;

//-----------------------------------------------------------------------------

}  // namespace logic

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_TYPE_CORE_COND_HPP
