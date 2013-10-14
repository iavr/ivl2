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

#ifndef IVL_DETAILS_CORE_AFUN_CONSTRUCT_HPP
#define IVL_DETAILS_CORE_AFUN_CONSTRUCT_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace afun_details {

//-----------------------------------------------------------------------------

template <typename T>
struct obj_construct
{
	T& obj;

	template <typename... A>
	inline void operator()(A&&... a) const { new (&obj) T(fwd <A>(a)...); }
};

template <typename T = tuple <> >
struct arg_construct;

template <typename... E>
struct arg_construct <tuple <E...> > : private tuple <E...>
{
	using tuple <E...>::tuple;

	template <typename T>
	inline void operator()(T& o) const { this->call(obj_construct <T>{o}); }
};

//-----------------------------------------------------------------------------

struct construct_
{
	inline constexpr arg_construct <>
	operator()() const { return arg_construct <>(); }

	template <typename A>
	inline constexpr arg_construct <map <keep, tuple_of <A> > >
	operator()(A&& a) const
	{
		return arg_construct <map <keep, tuple_of <A> > >(fwd <A>(a));
	}

	template <typename T, typename A>
	inline void operator()(T& o, A&& a) const { (*this)(fwd <A>(a))(o); }
};

//-----------------------------------------------------------------------------

struct destruct_
{
	template <typename T>
	void operator()(T& o) const { o.~T(); }
};

//-----------------------------------------------------------------------------

}  // namespace afun_details

//-----------------------------------------------------------------------------

namespace afun {

using construct = afun_details::construct_;
using destruct  = afun_details::destruct_;

}  // namespace afun

//-----------------------------------------------------------------------------

static __attribute__ ((unused)) afun::construct    construct;
static __attribute__ ((unused)) afun::destruct     destruct;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_AFUN_CONSTRUCT_HPP