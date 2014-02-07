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

#ifndef IVL_CORE_AFUN_CONSTRUCT_HPP
#define IVL_CORE_AFUN_CONSTRUCT_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace afun {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename T>
struct obj_construct
{
	T& obj;

	template <typename... A>
	INLINE void operator()(A&&... a) const { new (&obj) T(fwd <A>(a)...); }
};

template <typename...> struct arg_construct;

// TODO: remove
template <>
struct arg_construct <>
{
	template <typename T>
	INLINE void operator()(T& o) const { obj_construct <T>{o}(); }
};

template <typename... E>
struct arg_construct <tuple <E...> > : private tuple <E...>
{
	using tuple <E...>::tuple;

	template <typename T>
	INLINE void operator()(T& o) const { this->call(obj_construct <T>{o}); }
};

// TODO: remove
template <typename... E>
struct arg_construct <pre_tuple <E...> > : private tuple <E...>
{
	using tuple <E...>::tuple;

	template <typename T>
	INLINE void operator()(T& o) const { this->call(obj_construct <T>{o}); }
};

//-----------------------------------------------------------------------------

struct constructor
{
	INLINE constexpr arg_construct <>
	operator()() const { return arg_construct <>(); }

	template <typename A>
	INLINE constexpr arg_construct <map <reuse, tuple_of <A> > >
	operator()(A&& a) const
	{
		return arg_construct <map <reuse, tuple_of <A> > >(fwd <A>(a));
	}
};

//-----------------------------------------------------------------------------

struct construct
{
	template <typename T, typename A>
	INLINE void operator()(T& o, A&& a) const { constructor()(fwd <A>(a))(o); }
};

//-----------------------------------------------------------------------------

struct destruct
{
	template <typename T>
	INLINE void operator()(T& o) const { o.~T(); }
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

using details::constructor;
using details::construct;
using details::destruct;

//-----------------------------------------------------------------------------

}  // namespace afun

//-----------------------------------------------------------------------------

static __attribute__ ((unused)) afun::constructor  constructor;
static __attribute__ ((unused)) afun::construct    construct;
static __attribute__ ((unused)) afun::destruct     destruct;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_AFUN_CONSTRUCT_HPP
