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

#ifndef IVL_CORE_ARRAY_FUN_MORE_HPP
#define IVL_CORE_ARRAY_FUN_MORE_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace afun {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

using  all_size = val_min;
struct all_more : _and { using size_fun = all_size; };

//-----------------------------------------------------------------------------

struct prim_size
{
	template <typename... A>
	using size_type = typename pick <prim_seq <A...>{}, A...>::size_type;

	template <typename... A>
	INLINE constexpr size_type <A...> operator()(A&&... a) const
		{ return get <prim_seq <A...>{}>()(fwd <A>(a)...).size(); }
};

struct prim_more
{
	using size_fun = prim_size;

	template <typename... T>
	INLINE constexpr bool operator()(T&&... t) const
		{ return get <prim_trav <T...>{}>()(fwd <T>(t)...); }
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace afun

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_FUN_MORE_HPP