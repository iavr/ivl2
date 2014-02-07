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

struct id_fun
{
	template <typename A>
	INLINE constexpr A&&
	operator()(A&& a) const { return fwd <A>(a); }
};

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

template <template <typename...> class C>
struct choose_fun
{
	template <typename... A>
	INLINE constexpr auto operator()(A&&... a) const
	-> decltype(subs <C, A...>()(fwd <A>(a)...))
		{ return subs <C, A...>()(fwd <A>(a)...); }
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

}  // namespace details

//-----------------------------------------------------------------------------

using details::id_fun;
using details::bind_fun;
using details::choose_fun;
using details::try_fun;


//-----------------------------------------------------------------------------

}  // namespace afun

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_TUPLE_FUN_META_HPP
