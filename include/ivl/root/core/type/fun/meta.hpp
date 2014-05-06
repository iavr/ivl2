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

#ifndef IVL_CORE_TYPE_FUN_META_HPP
#define IVL_CORE_TYPE_FUN_META_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace afun {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

struct nop_fun
{
	template <typename... A>
	INLINE void operator()(A&&... a) const { }
};

//-----------------------------------------------------------------------------

struct id_fun
{
	template <typename A>
	INLINE constexpr A&&
	operator()(A&& a) const { return fwd <A>(a); }
};

//-----------------------------------------------------------------------------

template <template <typename...> class C>
struct switch_fun
{
	template <typename... A>
	INLINE constexpr auto operator()(A&&... a) const
	-> decltype(subs <C, A...>()(fwd <A>(a)...))
		{ return subs <C, A...>()(fwd <A>(a)...); }
};

template <typename C>
using switch_fun_of = switch_fun <C::template map>;

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

using details::nop_fun;
using details::id_fun;
using details::switch_fun;
using details::switch_fun_of;

//-----------------------------------------------------------------------------

}  // namespace afun

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_TYPE_FUN_META_HPP
