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

#ifndef IVL_CORE_TUPLE_FUN_META_HPP
#define IVL_CORE_TUPLE_FUN_META_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace afun {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename F, typename... E>
struct bind_fun
{
	template <typename... A>
	INLINE constexpr auto operator()(A&&... a) const
	-> decltype(F()(E()..., fwd <A>(a)...))
		{ return F()(E()..., fwd <A>(a)...); }
};

//-----------------------------------------------------------------------------

template <typename F>
struct try_fun_p
{
	template <typename... A>
	INLINE constexpr auto operator()(A&&... a) const
	-> decltype(call_first <F(A...)>()(fwd <A>(a)...))
		{ return call_first <F(A...)>()(fwd <A>(a)...); }
};

template <typename... F>
using try_fun = try_fun_p <pack <F...> >;

//-----------------------------------------------------------------------------

template <typename F, size_t I = 0>
struct mut_fun
{
	template <
		typename... A,
		only_if <!is_const <remove_ref <pick <I, A...> > >()>
	= 0>
	INLINE constexpr ret <F(A...)>
	operator()(A&&... a) const { return F()(fwd <A>(a)...); }
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

using details::bind_fun;
using details::try_fun;

//-----------------------------------------------------------------------------

}  // namespace afun

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_TUPLE_FUN_META_HPP
